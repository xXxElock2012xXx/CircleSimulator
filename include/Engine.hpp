#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/WindowBase.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <chrono>

#include "Platform.hpp"
#include "ShapeDrawable.hpp"
#include "box2d/id.h"
#include "box2d/types.h"

constexpr double kFrameTime = 1.F / 60.F;
constexpr int kEntityCount = 1;
constexpr int kSubStepCount = 4;

class Engine {
 public:
  explicit Engine();
  ~Engine();
  Engine(const Engine &) = delete;
  Engine &operator=(const Engine &) = delete;
  Engine(Engine &&) = delete;
  Engine &operator=(Engine &&) = delete;

  void Setup();
  void Run();

 private:
  void HandleInput();

  bool LoadResource(const std::string &path);

  void Update(float elapsed_time);

  void Render();

  b2WorldDef world_def_;
  b2WorldId world_id_;
  Platform platform_;
  ShapeDrawable shape_;

  sf::RenderWindow window_;
  sf::Texture texture_;

  std::chrono::steady_clock::time_point time_;
};

#endif  //  ENGINE_HPP_
