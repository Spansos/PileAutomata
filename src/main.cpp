#include <SFML/Graphics.hpp>
#include <array>
#include <cstdint>

const int level_size = 32;

class Tile {
public:
private:
    enum {
        POP,
        PUSH,
        WALL
    } type;

    struct Push {
        int value;
    };

    union {
        Push push;
    };
};

class Level {
public:
    void tick(sf::Vector2i player_movement) {
        player += player_movement;
    }
private:
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

    }
  
    return 0;
}