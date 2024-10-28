#include <SFML/Graphics.hpp>
#include <memory>
#include "Tank.h"
#include "Map.h"

int main() {
    const int cellSize = 30;  // Tamaño de cada celda en píxeles
    const int rows = 20;      // Disminuye el número de filas
    const int cols = 30;      // Disminuye el número de columnas

    sf::RenderWindow window(sf::VideoMode(cols * cellSize, rows * cellSize), "Tank Attack!");
    window.setFramerateLimit(60);

    Map map(rows, cols, cellSize);

    std::vector<std::unique_ptr<Tank>> tanks;
    tanks.push_back(std::make_unique<Tank>(1, 1, sf::Color::Blue, cellSize));
    tanks.push_back(std::make_unique<Tank>(rows - 2, cols - 2, sf::Color::Red, cellSize));

    Tank* selectedTank = nullptr;
    bool routeCalculated = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                int targetCol = mousePos.x / cellSize;
                int targetRow = mousePos.y / cellSize;

                // Selección del tanque
                if (selectedTank == nullptr) {
                    for (auto& tank : tanks) {
                        if (tank->contains(mousePos.x, mousePos.y)) {
                            selectedTank = tank.get();
                            routeCalculated = false;
                            break;
                        }
                    }
                }
                // Establece la ruta si hay un tanque seleccionado
                else if (!routeCalculated) {
                    selectedTank->setTarget(targetRow, targetCol, map);
                    routeCalculated = true;
                }
            }
        }

        // Actualiza y mueve el tanque seleccionado
        if (selectedTank != nullptr && routeCalculated) {
            selectedTank->moveTowardsTarget(map, 1.0f / 60.0f);
            if (selectedTank->isAtTarget()) {
                selectedTank = nullptr;
                routeCalculated = false;
            }
        }

        // Renderizado
        window.clear();
        map.draw(window);

        // Dibuja la ruta del tanque seleccionado
        if (selectedTank != nullptr) {
            selectedTank->drawPath(window);
        }

        // Dibuja todos los tanques
        for (auto& tank : tanks) {
            tank->draw(window);
        }
        window.display();
    }

    return 0;
}