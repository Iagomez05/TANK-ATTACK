#include <SFML/Graphics.hpp>
#include "Tank.h"
#include "Map.h"
#include <iostream>

enum class PlayerTurn { Player1, Player2 };

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tank Attack!");
    window.setFramerateLimit(60);

    sf::Clock clock;
    Map map("mapa.png", "muro (1).png");

    Tank player1Tank(100, 100, "blue tank (1).png");
    Tank player2Tank(200, 200, "red tank.png");

    PlayerTurn turn = PlayerTurn::Player1;
    bool tankSelected = false;
    Tank* selectedTank = nullptr;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                if (!tankSelected) {
                    if (turn == PlayerTurn::Player1 && player1Tank.getSprite().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        selectedTank = &player1Tank;
                        tankSelected = true;
                    } else if (turn == PlayerTurn::Player2 && player2Tank.getSprite().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        selectedTank = &player2Tank;
                        tankSelected = true;
                    }
                } else if (tankSelected && selectedTank != nullptr) {
                    selectedTank->setTargetPosition(mousePosition.x, mousePosition.y);
                    tankSelected = false;
                    selectedTank = nullptr;
                    turn = (turn == PlayerTurn::Player1) ? PlayerTurn::Player2 : PlayerTurn::Player1;
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();
        player1Tank.update(deltaTime, map);
        player2Tank.update(deltaTime, map);

        window.clear();
        map.draw(window);
        player1Tank.draw(window);
        player2Tank.draw(window);
        window.display();
    }

    return 0;
}