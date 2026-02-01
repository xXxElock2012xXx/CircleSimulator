#include "Engine.hpp"
#include <exception>
#include <iostream>
#include "box2d/box2d.h"
#include "box2d/math_functions.h"

Engine::Engine()
    : window_(sf::VideoMode::getDesktopMode(), "Physics simulation", sf::Style::Default) {
  window_.setFramerateLimit(60);
  time_ = std::chrono::steady_clock::now();

  world_def_ = b2DefaultWorldDef();
  const b2Vec2 gravity{0.0F, 10.0F};
  world_def_.gravity = gravity;
  world_id_ = b2CreateWorld(&world_def_);
  platform_ = Platform(world_id_, window_);
  shape_ = ShapeDrawable(world_id_, window_);
}

Engine::~Engine() {
  b2DestroyWorld(world_id_);
}

  void Engine::Setup() {
  }


void Engine::Run() {
  while (window_.isOpen()) {
    std::chrono::steady_clock::time_point delta_time = std::chrono::steady_clock::now();

    const float elapsed_time = std::chrono::duration<float>(delta_time - time_).count();

    if (elapsed_time > kFrameTime) {
      time_ = delta_time;
      HandleInput();
      Update(elapsed_time);
      Render();
    }
  }
}

void Engine::HandleInput() {
  while (const std::optional event = window_.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window_.close();

    } else {
      if (const auto* key_pressed = event->getIf<sf::Event::KeyPressed>()) {
        if (key_pressed->scancode == sf::Keyboard::Scancode::Escape) {
          window_.close();
        }
      }
    }
  }
}

void Engine::Update(const float elapsed_time) {
  b2World_Step(world_id_, elapsed_time, kSubStepCount);
  platform_.Update(elapsed_time);
  shape_.Update(elapsed_time);
  b2Vec2 position = b2Body_GetPosition(shape_.body_id_);
  b2Rot rotation = b2Body_GetRotation(shape_.body_id_);

  std::cout << "x " << position.x << " y " << position.y << " rot " << b2Rot_GetAngle(rotation)
            << std::endl;
  std::cout << "x " << shape_.rectangle_.getPosition().x << " y "
            << shape_.rectangle_.getPosition().y << std::endl;
}



  void Engine::Render() {
    window_.clear(sf::Color(0x93a832));

    platform_.Draw(window_);
    shape_.Draw(window_);

    window_.display();
  }


bool Engine::LoadResource(const std::string &path) {
  if (!texture_.loadFromFile(path, false, sf::IntRect{{0, 0}, {96, 96}})) {
    std::cout << "could not find resource at path" << path;
    std::terminate();
  } else {
    return true;
  }
}
