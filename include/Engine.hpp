#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <chrono>
#include <iostream>
#include <ratio>

#include "Entity.hpp"

constexpr double kFrameTime = 1.F / 60.F;

class Engine {
 public:
  explicit Engine()
      : window_(sf::VideoMode::getDesktopMode(), "Physics simulation", sf::Style::Default),
        circle_(sf::Vector2f(window_.getSize() / 2U)) {
    window_.setFramerateLimit(60);
    time_ = std::chrono::steady_clock::now();
  }

  void Setup() {}

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
      }
    }
  }

  void Update(const double elapsed_time) {
    circle_.Update(static_cast<float>(elapsed_time));

    std::cout << "position:" << circle_.circle_.getPosition().x << " "
              << circle_.circle_.getPosition().y << "\n";
  }

  void Render() {
    window_.clear(sf::Color(0x93a832));

    circle_.Draw(window_);

    window_.display();
  }

  sf::RenderWindow window_;
  Entity circle_;

  std::chrono::steady_clock::time_point time_;
};

#endif  //  ENGINE_HPP_
