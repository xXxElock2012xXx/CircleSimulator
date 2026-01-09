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
#include <SFML/Window/WindowEnums.hpp>
#include <chrono>
#include <exception>
#include <iostream>
#include <vector>

#include "Entity.hpp"

constexpr double kFrameTime = 1.F / 60.F;
constexpr int kEntityCount = 1;

class Engine {
 public:
  explicit Engine()
      : window_(sf::VideoMode::getDesktopMode(), "Physics simulation", sf::Style::Default) {
    window_.setFramerateLimit(60);
    time_ = std::chrono::steady_clock::now();

    entities_.reserve(kEntityCount);
    for (int i = 0; i < kEntityCount; i++) {
      entities_.emplace_back(sf::Vector2f(window_.getSize() / 2U), texture_);
    }
  }

  void Setup() {
    LoadResource("/home/teapa/data/CircleSimulator/Sheep.png");
  }

  void Run() {
    while (window_.isOpen()) {
      std::chrono::steady_clock::time_point delta_time = std::chrono::steady_clock::now();

      const double elapsed_time = std::chrono::duration<double>(delta_time - time_).count();

      if (elapsed_time > kFrameTime) {
        time_ = delta_time;
        HandleInput();
        Update(elapsed_time);
        Render();
      }
    }
  }

 private:
  void HandleInput() {
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

  bool LoadResource(const std::string &path) {
    if (!texture_.loadFromFile(path, false, sf::IntRect{{0, 0}, {96, 96}})) {
      std::cout << "could not find resource at path" << path;
      std::terminate();
    } else {
      return true;
    }
  }

  void Update(const double elapsed_time) {
    for (Entity &ent : entities_) {
      ent.Update(static_cast<float>(elapsed_time));
      ent.CheckBorderCollision(window_);
    }
  }

  void Render() {
    window_.clear(sf::Color(0x93a832));

    for (Entity &ent : entities_) {
      ent.Draw(window_);
    }

    window_.display();
  }

  sf::RenderWindow window_;
  sf::Texture texture_;

  std::vector<Entity> entities_;

  std::chrono::steady_clock::time_point time_;
};

#endif  //  ENGINE_HPP_
