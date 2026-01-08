#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <chrono>
#include <exception>
#include <iostream>

#include "Entity.hpp"

constexpr double kFrameTime = 1.F / 60.F;

class Engine {
 public:
  explicit Engine()
      : window_(sf::VideoMode::getDesktopMode(), "Physics simulation", sf::Style::Default),
        circle_(sf::Vector2f(window_.getSize() / 2U), texture_),
        circle2_(sf::Vector2f(window_.getSize() / 2U + sf::Vector2u(0, 100)), texture_) {
    window_.setFramerateLimit(60);
    time_ = std::chrono::steady_clock::now();
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
      }
    }
  }

  bool LoadResource(const std::string &path) {
    if (!texture_.loadFromFile(path, false, sf::IntRect{{0, 0}, {96, 96}})) {
      std::cout << "fuck";
      std::terminate();
    } else {
      return true;
    }
  }

  void Update(const double elapsed_time) {
    circle_.Update(static_cast<float>(elapsed_time), 1);
    circle2_.Update(static_cast<float>(elapsed_time), 2);

    // std::cout << "position:" << circle_.circle_.getPosition().x << " "
    //           << circle_.circle_.getPosition().y << "\n";
  }

  void Render() {
    window_.clear(sf::Color(0x93a832));

    circle_.Draw(window_);
    circle2_.Draw(window_);

    window_.display();
  }

  sf::RenderWindow window_;
  sf::Texture texture_;
  Entity circle_;
  Entity circle2_;

  std::chrono::steady_clock::time_point time_;
};

#endif  //  ENGINE_HPP_
