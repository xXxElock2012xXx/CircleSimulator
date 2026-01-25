#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Engine.hpp"
#include "box2d/box2d.h"
#include "box2d/math_functions.h"
#include "box2d/types.h"

int main() {
  // Engine simulation;
  // simulation.Setup();
  // simulation.Run();

  b2WorldDef world_def = b2DefaultWorldDef();
  const b2Vec2 gravity = {0.0F, -10.0F};
  world_def.gravity = gravity;
  b2WorldId world_id = b2CreateWorld(&world_def);

  b2BodyDef ground_body_def = b2DefaultBodyDef();
  ground_body_def.position = gravity;
  b2BodyId ground_id = b2CreateBody(world_id, &ground_body_def);
  b2Polygon ground_box = b2MakeBox(50.0F, 10.0F);

  b2ShapeDef ground_shape_def = b2DefaultShapeDef();
  b2CreatePolygonShape(ground_id, &ground_shape_def, &ground_box);

  b2BodyDef body_def = b2DefaultBodyDef();
  body_def.type = b2_dynamicBody;
  const b2Vec2 position = {0.0F, 4.0F};
  body_def.position = position;
  b2BodyId body_id = b2CreateBody(world_id, &body_def);

  b2Polygon dynamic_box = b2MakeBox(1.0F, 1.0F);

  b2ShapeDef shape_def = b2DefaultShapeDef();
  shape_def.density = 1.0F;
  shape_def.material.friction = 0.3F;

  b2CreatePolygonShape(body_id, &shape_def, &dynamic_box);

  const float timeStep = 1.0F / 60.0F;
  const int subStepCount = 4;

  for (int i = 0; i < 90; ++i) {
    b2World_Step(world_id, timeStep, subStepCount);
    b2Vec2 position = b2Body_GetPosition(body_id);
    b2Rot rotation = b2Body_GetRotation(body_id);
    printf("%4.2f %4.2f %4.2f\n", position.x, position.y, b2Rot_GetAngle(rotation));
  }

  b2DestroyWorld(world_id);

  return -1;
}
