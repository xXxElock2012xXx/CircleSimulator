#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

class Entity {
 public:
  explicit Entity(sf::Vector2f position, const sf::Texture &texture) : texture_(texture) {
    circle_.setPosition(position);
    circle_.setPointCount(100);
    circle_.setRadius(50);
  }

  void SetTexture(const sf::Texture &texture) {

    circle_.setTexture(&texture, true);
  }

  void Update(const float elapsed_time, const int type) {
    if (type == 1) {
      circle_.setPosition(circle_.getPosition() + sf::Vector2f(1, 0) * velocity_ * elapsed_time);
      const float acceleration = kForce / kMass;
      velocity_ = velocity_ + acceleration * elapsed_time;
    } else {
      const float acceleration = kForce / kMass;
      velocity_ = velocity_ + acceleration * elapsed_time;
      circle_.setPosition(circle_.getPosition() + sf::Vector2f(1, 0) * velocity_ * elapsed_time);
    }
  }

  void Draw(sf::RenderWindow &window) const {
    sf::Sprite sprite(texture_);
    sprite.setPosition(circle_.getPosition());
    window.draw(sprite);
  }

  sf::CircleShape circle_;
  const sf::Texture &texture_;

 private:
  float velocity_ = 0;
  static constexpr float kForce = 3;
  static constexpr float kMass = 1;
};

#endif  //  ENTITY_HPP_
