#include <SFML/Graphics.hpp>
#include <array>
#include <cstdint>
#include <iostream>

const int level_size = 32;

class Tile : public sf::Drawable {
public:
protected:
    void draw(sf::RenderTarget & target, sf::RenderStates states) const override {
        sf::RectangleShape rect;
        rect.setPosition(static_cast<sf::Vector2f>(position*32));
        rect.setSize({32, 32});
        switch (type) {
            case POP:
                rect.setFillColor(sf::Color{0xa04030});
                break;
            case PUSH:
                rect.setFillColor(sf::Color{0x6030a0});
                break;
                break;
            case WALL:
                rect.setFillColor(sf::Color{0x506080});
                break;
            case EMPTY:
                rect.setFillColor(sf::Color{0x102030});
                break;
        }
        target.draw(rect, states);
    }
private:
    sf::Vector2i position;
    enum {
        POP,
        PUSH,
        WALL,
        EMPTY
    } type;

    struct Push {
        int value;
    };

    union {
        Push push;
    };
};

class Level : public sf::Drawable {
public:
    void tick(sf::Vector2i player_movement) {
        player += player_movement;
    }
private:
    void draw(sf::RenderTarget & target, sf::RenderStates states) const override {
        for (const auto & tile : tiles)
            target.draw(tile, states);
        sf::RectangleShape r;
        r.setPosition(static_cast<sf::Vector2f>(player*32+sf::Vector2i{8,8}));
        r.setFillColor(sf::Color{0xf0f0f0});
        r.setSize({24, 24});
    }
    std::array<Tile, level_size*level_size> tiles;
    sf::Vector2i player;
};

int main() {
    sf::RenderWindow window{{1280, 720}, "pile automata"};

    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    sf::Vector2i player_pos{0,0};

    Level level;

    while (window.isOpen()) {

        sf::Vector2i move;
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up)
                    move = {0, -1};
                if (event.key.code == sf::Keyboard::Down)
                    move = {0, 1};
                if (event.key.code == sf::Keyboard::Left)
                    move = {0, -1};
                if (event.key.code == sf::Keyboard::Right)
                    move = {0, 1};
            }
        }

        if (move.x || move.y)
            level.tick(move);

        window.clear();
        window.draw(level);
        window.display();

    }
  
    return 0;
}