#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <limits>
#include <iostream>

class Game {
  private:
    sf::RenderWindow window;

    unsigned int window_resolution = 1200;

    double zoom_level = 1.0;
    double min_zoom_level = 1.0;
    double max_zoom_level = std::numeric_limits<double>::max() / window_resolution - 1.0;
    double previous_zoom_level = 1.0;
    const double zoom_speed = 0.02;

    sf::Vector2f offset;
    const double move_speed = 20.;

    std::vector<sf::RectangleShape> shapes;

    void shapes_for_level(double x, double y, double size);

    void update();
    void render();
  public:
    Game();
    void run();
};

#endif // GAME_HPP
