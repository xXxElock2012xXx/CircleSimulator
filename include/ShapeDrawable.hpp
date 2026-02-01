#ifndef SHAPE_DRAWABLE_HPP_
#define SHAPE_DRAWABLE_HPP_

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include "box2d/box2d.h"
#include "box2d/collision.h"
#include "box2d/id.h"
#include "box2d/math_functions.h"
#include "box2d/types.h"

namespace {
sf::CircleShape debug_circle_;
}

class ShapeDrawable {
 public:
  ShapeDrawable() = default;

  ShapeDrawable(const b2WorldId world_id, const sf::RenderWindow &window) {
    bounds_ = b2DefaultBodyDef();
    bounds_.type = b2_dynamicBody;

    b2Vec2 position_base{static_cast<float>(window.getSize().x) / 2U,
                         static_cast<float>(window.getSize().y) / 2U};

    const b2Vec2 position = {0.0F, 10.0F};
    bounds_.position = position + position_base;

    body_id_ = b2CreateBody(world_id, &bounds_);
    b2Polygon ground_box = b2MakeBox(1.0F, 1.0F);
    b2ShapeDef ground_shape = b2DefaultShapeDef();
    b2CreatePolygonShape(body_id_, &ground_shape, &ground_box);
    rectangle_.setSize(sf::Vector2f(30, 30));
    rectangle_.setFillColor(sf::Color::Green);

    debug_circle_.setPointCount(100);
    debug_circle_.setRadius(25);
    debug_circle_.setFillColor(sf::Color::Transparent);
    debug_circle_.setOutlineColor(sf::Color::Magenta);
    debug_circle_.setOutlineThickness(5);
  };

  void Update(const float /*elapsed_time*/) {
    b2Vec2 position = b2Body_GetPosition(body_id_);
    rectangle_.setPosition(sf::Vector2f(position.x, position.y));
  }

  void Draw(sf::RenderWindow &window) const {
    debug_circle_.setPosition(rectangle_.getPosition() + rectangle_.getOrigin());
    window.draw(rectangle_);
    window.draw(debug_circle_);
  }

  b2BodyId body_id_;

  sf::RectangleShape rectangle_;

 private:
  b2BodyDef bounds_;
};

#endif  //  SHAPE_DRAWABLE_HPP_
