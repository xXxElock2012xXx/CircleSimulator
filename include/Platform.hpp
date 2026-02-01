#ifndef PLATFORFM_HPP_
#define PLATFORFM_HPP_

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include "box2d/box2d.h"
#include "box2d/collision.h"
#include "box2d/id.h"
#include "box2d/math_functions.h"
#include "box2d/types.h"

class Platform {
 public:
  Platform() = default;

  Platform(const b2WorldId world_id, const sf::RenderWindow &window) {
    bounds_ = b2DefaultBodyDef();

    b2Vec2 position{static_cast<float>(window.getSize().x) / 2.F,
                    (static_cast<float>(window.getSize().y) / 2.F) + 200};
    bounds_.position = position;

    body_id_ = b2CreateBody(world_id, &bounds_);
    dynamic_box_ = b2MakeBox(50.0F, 10.0F);
    ground_shape_ = b2DefaultShapeDef();
    b2CreatePolygonShape(body_id_, &ground_shape_, &dynamic_box_);

    rectangle_.setSize(sf::Vector2f(100, 20));
    rectangle_.setFillColor(sf::Color::Black);
  };

  void Update(const float /*elapsed_time*/) {
    b2Vec2 position = b2Body_GetPosition(body_id_);
    rectangle_.setPosition(sf::Vector2f(position.x, position.y));
  }

  void Draw(sf::RenderWindow &window) const {
    window.draw(rectangle_);
  }

  b2BodyId body_id_;

 private:
  b2BodyDef bounds_;
  b2Polygon dynamic_box_;
  b2ShapeDef ground_shape_;
  sf::RectangleShape rectangle_;
};

#endif  //  PLATFORFM_HPP_
