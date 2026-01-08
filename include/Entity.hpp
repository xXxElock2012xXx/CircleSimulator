#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

class Entity {
 public:
  explicit Entity(sf::Vector2f position) {
    circle_.setPosition(position);
    circle_.setPointCount(100);
    circle_.setRadius(20);
  }

  void Update(const float elapsed_time) {
    circle_.setPosition(circle_.getPosition() + sf::Vector2f(1, 0) * velocity_ * elapsed_time);
    const float acceleration = kForce / kMass;
    velocity_ = velocity_ + acceleration * elapsed_time;
  }

  void Draw(sf::RenderWindow &window) const {
    window.draw(circle_);
  }

  sf::CircleShape circle_;

 private:
  float velocity_ = 0;
  static constexpr float kForce = 3;
  static constexpr float kMass = 1;
};

#endif  //  ENTITY_HPP_
