#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

class Entity {
 public:
  explicit Entity(sf::Vector2f position, const sf::Texture &texture) : texture_(texture) {
    circle_.setPosition(position);
    circle_.setPointCount(100);
    circle_.setRadius(50);
    debug_circle_.setPointCount(100);
    debug_circle_.setRadius(25);
    debug_circle_.setFillColor(sf::Color::Transparent);
    debug_circle_.setOutlineColor(sf::Color::Magenta);
    debug_circle_.setOutlineThickness(5);
    circle_.setOrigin({25, 25});
  }

  void SetTexture(const sf::Texture &texture) {
    circle_.setTexture(&texture, true);
  }

  void Update(const float elapsed_time) {
    velocity_ = velocity_ + acceleration_ * elapsed_time;
    circle_.setPosition(circle_.getPosition() + velocity_ * elapsed_time);
  }

  bool CheckCollision(const Entity &other) {
    return kDistance(other.circle_.getGeometricCenter(), this->circle_.getGeometricCenter()) >
           this->circle_.getRadius();
  }

  [[nodiscard]] static constexpr float kDistanceSquared(const sf::Vector2f start,
                                                        const sf::Vector2f end) {
    return kSqr(start.x - end.x) + kSqr(start.y - end.y);
  }

  void CheckBorderCollision(sf::RenderWindow &window) {
    const sf::Vector2f center = this->circle_.getPosition() + this->circle_.getOrigin();

    if (center.y > static_cast<float>(window.getSize().y)) {
      velocity_.y *= -1;
    }
    if (center.y < 0) {
      velocity_.y *= -1;
    }
    if (center.x > static_cast<float>(window.getSize().x)) {
      velocity_.x *= -1;
    }
    if (center.x < 0) {
      velocity_.x *= -1;
    }
  }

  [[nodiscard]] static constexpr float kDistance(const sf::Vector2f start, const sf::Vector2f end) {
    return std::sqrt(kDistanceSquared(start, end));
  }

  [[nodiscard]] static constexpr float kSqr(const float value) {
    return value * value;
  }

  void Draw(sf::RenderWindow &window) const {
    sf::Sprite sprite(texture_);
    sprite.setPosition(circle_.getPosition());
    debug_circle_.setPosition(circle_.getPosition() + circle_.getOrigin());
    window.draw(sprite);
    window.draw(debug_circle_);
  }

 private:
  sf::CircleShape circle_;
  const sf::Texture &texture_;
  sf::Vector2f velocity_ = {100, 0};
  sf::Vector2f acceleration_ = {0, 30};
  static sf::CircleShape debug_circle_;
};

#endif  //  ENTITY_HPP_
