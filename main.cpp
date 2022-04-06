#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

int main() {
  int window_size_x = 1000;
  int window_size_y = 1200;
  int rect_size = 100;

  sf::RenderWindow window(sf::VideoMode(window_size_x, window_size_y), "DVD");
  sf::RectangleShape shape(sf::Vector2f(rect_size, rect_size));

  shape.setFillColor(sf::Color::Green);

  float x = 0;
  float y = 0;

  // random bit generator
  std::random_device rd;
  std::mt19937 gen(rd());  // Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> dis(1, 20);

  sf::Vector2f initialSpeed = sf::Vector2f(dis(gen), dis(gen));

  window.setFramerateLimit(40);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed ||
          (event.type == sf::Event::KeyPressed &&
           event.key.code == sf::Keyboard::Escape))
        window.close();
    }

    x += initialSpeed.x;
    y += initialSpeed.y;

    if (x >= (window_size_x - rect_size) || x <= 0 || y <= 0 ||
        y >= (window_size_y - rect_size)) {
      if (y <= 0 || y >= (window_size_y - rect_size)) {
        y -= initialSpeed.y;
        initialSpeed = sf::Vector2f(initialSpeed.x, initialSpeed.y * -1);
      } else if (x >= (window_size_x - rect_size) || x <= 0) {
        x -= initialSpeed.x;
        initialSpeed = sf::Vector2f(initialSpeed.x * -1, initialSpeed.y);
      }
      std::uniform_int_distribution<> col_dis(0, 255);
      sf::Color color = sf::Color(col_dis(gen), col_dis(gen), col_dis(gen));
      shape.setFillColor(color);
    }

    std::cout << x << ' ' << y << '\n';

    shape.setPosition(x, y);
    window.clear();
    window.draw(shape);
    window.display();
  }

  return 0;
}
