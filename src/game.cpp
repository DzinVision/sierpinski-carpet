#include "game.hpp"

Game::Game() {

    window.create(sf::VideoMode(window_resolution, window_resolution), "Sierpinski Carpet", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
}

void Game::run() {
    double size = window_resolution * zoom_level;
    shapes_for_level(0, 0, size);

    double ups = 1000./60;
    double time_delta = 0;
    auto previous_time = std::chrono::duration_cast<std::chrono::milliseconds>(
                            std::chrono::system_clock::now().time_since_epoch());

    while(window.isOpen()){
        auto now = std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::system_clock::now().time_since_epoch());
        time_delta += now.count() - previous_time.count();
        previous_time = now;

        while (time_delta > ups) {
            update();

            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            time_delta -= ups;
        }

        render();
    }
}

void Game::update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();
    }


    bool offset_changed = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        offset.x -= move_speed;

        offset_changed = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        offset.x += move_speed;

        offset_changed = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        offset.y -= move_speed;

        offset_changed = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        offset.y += move_speed;

        offset_changed = true;
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        zoom_level += zoom_speed * zoom_level;
        if (zoom_level > max_zoom_level) {
            zoom_level = max_zoom_level;
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        zoom_level -= zoom_speed * zoom_level;
        if (zoom_level < min_zoom_level) {
            zoom_level = min_zoom_level;
        }
    }


    double diff = zoom_level * window_resolution -  window_resolution;

    if (offset.x < 0) {
        offset.x = 0;
    } else if (offset.x > diff) {
        offset.x = diff;
    }

    if (offset.y < 0) {
        offset.y = 0;
    } else if (offset.y > diff) {
        offset.y = diff;
    }


    if (previous_zoom_level == zoom_level && !offset_changed) {
        return;
    }

    previous_zoom_level = zoom_level;

    double size = window_resolution * zoom_level;
    shapes = std::vector<sf::RectangleShape>();
    shapes_for_level(0., 0., size);
}

void Game::render() {
    window.clear(sf::Color::White);

    for (sf::RectangleShape rectangle : shapes) {
        window.draw(rectangle);
    }

    window.display();
}

void Game::shapes_for_level(double x, double y, double size) {
    const double sub_size = size / 3.0;

    if (sub_size < 5 || x - offset.x > window_resolution || y - offset.y > window_resolution || x + size < offset.x || y + size < offset.y) {
        return;
    }

    double rectangle_x = x + sub_size - offset.x;
    double rectangle_y = y + sub_size - offset.y;

    sf::RectangleShape rectangle(sf::Vector2f(sub_size, sub_size));
    rectangle.setPosition(sf::Vector2f(rectangle_x, rectangle_y));
    rectangle.setFillColor(sf::Color::Black);

    shapes.push_back(rectangle);

    for (int i = 0; i < 9; ++i) {
        if (i == 4) {
            continue;
        }

        int x_mult = i % 3;
        int y_mult = i / 3;

        double sub_x = sub_size * x_mult + x;
        double sub_y = sub_size * y_mult + y;

        shapes_for_level(sub_x, sub_y, sub_size);
    }
}
