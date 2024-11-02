#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <iostream>
#include <cmath>
#include "Tank.h"
#include "Map.h"
#include "Bullet.h"
#include "PowerUp.h"

enum class Turn { Blue, Red };

bool isTeamDefeated(const std::vector<std::unique_ptr<Tank>>& tanks) {
    for (const auto& tank : tanks) {
        if (tank->isAlive()) {
            return false;
        }
    }
    return true;
}

int countAliveTanks(const std::vector<std::unique_ptr<Tank>>& tanks) {
    int count = 0;
    for (const auto& tank : tanks) {
        if (tank->isAlive()) {
            count++;
        }
    }
    return count;
}

int main() {
    std::cout << "Iniciando el juego" << std::endl;

    const int cellSize = 30;
    const int rows = 20;
    const int cols = 30;
    const sf::Time timeLimit = sf::seconds(300); // Límite de tiempo de 5 minutos

    sf::RenderWindow window(sf::VideoMode(cols * cellSize, rows * cellSize), "Tank Attack!");
    window.setFramerateLimit(60);

    Map map(rows, cols, cellSize);
    std::cout << "Mapa creado" << std::endl;

    std::vector<std::unique_ptr<Tank>> blueTanks;
    std::vector<std::unique_ptr<Tank>> redTanks;

    // Añadir tanques azules
    blueTanks.push_back(std::make_unique<Tank>(1, 1, sf::Color::Blue, cellSize));
    blueTanks.push_back(std::make_unique<Tank>(2, 1, sf::Color::Blue, cellSize));
    blueTanks.push_back(std::make_unique<Tank>(1, 2, sf::Color::Blue, cellSize));
    blueTanks.push_back(std::make_unique<Tank>(2, 2, sf::Color::Blue, cellSize));
    std::cout << "Tanques azules creados" << std::endl;

    // Añadir tanques rojos
    redTanks.push_back(std::make_unique<Tank>(rows - 2, cols - 2, sf::Color::Red, cellSize));
    redTanks.push_back(std::make_unique<Tank>(rows - 3, cols - 2, sf::Color::Red, cellSize));
    redTanks.push_back(std::make_unique<Tank>(rows - 2, cols - 3, sf::Color::Red, cellSize));
    redTanks.push_back(std::make_unique<Tank>(rows - 3, cols - 3, sf::Color::Red, cellSize));
    std::cout << "Tanques rojos creados" << std::endl;

    Turn turn = Turn::Blue;
    Tank* selectedTank = nullptr;
    bool routeCalculated = false;

    // Asignación de power-ups
    PowerUp bluePowerUp;
    PowerUp redPowerUp;
    bool bluePowerUpUsed = false;
    bool redPowerUpUsed = false;

    std::cout << "Power-ups asignados: " << std::endl;
    std::cout << "Equipo Azul: " << bluePowerUp.toString() << std::endl;
    std::cout << "Equipo Rojo: " << redPowerUp.toString() << std::endl;

    // Vector para almacenar las balas activas
    std::vector<std::unique_ptr<Bullet>> bullets;

    // Temporizador para contar el tiempo transcurrido
    sf::Clock clock;

    std::cout << "Entrando en el bucle principal del juego" << std::endl;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Detección de teclas para tipo de movimiento o disparo
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::C) {
                    std::cout << "Ruta calculada (BFS)" << std::endl;
                }
                if (event.key.code == sf::Keyboard::V) {
                    std::cout << "Ruta calculada (Movimiento aleatorio)" << std::endl;
                }
                if (event.key.code == sf::Keyboard::B) {
                    std::cout << "Ruta calculada (Dijkstra)" << std::endl;
                }
                if (event.key.code == sf::Keyboard::N) {
                    std::cout << "Ruta calculada (Movimiento aleatorio)" << std::endl;
                }
            }

            // Manejo de clics del mouse
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                int targetCol = mousePos.x / cellSize;
                int targetRow = mousePos.y / cellSize;

                // Clic izquierdo para seleccionar tanque o establecer destino
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (selectedTank == nullptr) {
                        auto& tanks = (turn == Turn::Blue) ? blueTanks : redTanks;
                        for (auto& tank : tanks) {
                            if (tank->contains(mousePos.x, mousePos.y)) {
                                selectedTank = tank.get();
                                routeCalculated = false;
                                break;
                            }
                        }
                    } else if (!routeCalculated) {
                        selectedTank->setTarget(targetRow, targetCol, map);
                        routeCalculated = true;
                    }
                }

                // Clic derecho para disparar una bala
                if (event.mouseButton.button == sf::Mouse::Right && selectedTank != nullptr) {
                    float dirX = mousePos.x - selectedTank->getPosition().x;
                    float dirY = mousePos.y - selectedTank->getPosition().y;
                    float magnitude = std::sqrt(dirX * dirX + dirY * dirY);
                    dirX /= magnitude;
                    dirY /= magnitude;

                    // Limpiar el recorrido de todas las balas activas
                    for (auto& bullet : bullets) {
                        bullet->clearPath();
                    }

                    bullets.push_back(std::make_unique<Bullet>(
                        selectedTank->getPosition().x,
                        selectedTank->getPosition().y,
                        dirX, dirY,
                        selectedTank  // Pasa el tanque disparador para evitar colisión
                    ));
                }
            }

            // Activación de power-up al presionar Shift
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::LShift) {
                if (turn == Turn::Blue && !bluePowerUpUsed) {
                    std::cout << "Power-up activado para el equipo Azul: " << bluePowerUp.toString() << std::endl;
                    bluePowerUpUsed = true;
                } else if (turn == Turn::Red && !redPowerUpUsed) {
                    std::cout << "Power-up activado para el equipo Rojo: " << redPowerUp.toString() << std::endl;
                    redPowerUpUsed = true;
                }
            }
        }

        // Actualizar balas y verificar colisiones
        float deltaTime = 1.0f / 60.0f;
        for (auto& bullet : bullets) {
            bullet->move(deltaTime, map);

            // Verificar colisiones con tanques
            for (auto& tank : blueTanks) {
                if (bullet->checkCollision(*tank) && bullet->getTeamColor() != tank->getColor()) {
                    tank->takeDamage(25);  // Daño para tanques azules
                    bullet->deactivate();
                }
            }
            for (auto& tank : redTanks) {
                if (bullet->checkCollision(*tank) && bullet->getTeamColor() != tank->getColor()) {
                    tank->takeDamage(50);  // Daño para tanques rojos
                    bullet->deactivate();
                }
            }
        }

        // Mover el tanque seleccionado hacia su destino
        if (selectedTank != nullptr && routeCalculated) {
            selectedTank->moveTowardsTarget(map, deltaTime);
            if (selectedTank->isAtTarget()) {
                selectedTank = nullptr;
                routeCalculated = false;

                // Aplicar Doble Turno si el power-up está activado
                if (turn == Turn::Blue && bluePowerUp.getType() == PowerUpType::DoubleTurn && bluePowerUpUsed) {
                    std::cout << "Equipo Azul usa Doble Turno." << std::endl;
                    bluePowerUpUsed = false;
                } else if (turn == Turn::Red && redPowerUp.getType() == PowerUpType::DoubleTurn && redPowerUpUsed) {
                    std::cout << "Equipo Rojo usa Doble Turno." << std::endl;
                    redPowerUpUsed = false;
                } else {
                    turn = (turn == Turn::Blue) ? Turn::Red : Turn::Blue;
                }
            }
        }

        // Verificar si el juego ha terminado por equipo derrotado
        if (isTeamDefeated(blueTanks)) {
            std::cout << "Equipo Rojo ha ganado!" << std::endl;
            window.close();
        } else if (isTeamDefeated(redTanks)) {
            std::cout << "Equipo Azul ha ganado!" << std::endl;
            window.close();
        }

        // Verificar si el límite de tiempo ha sido alcanzado
        if (clock.getElapsedTime() >= timeLimit) {
            int blueAlive = countAliveTanks(blueTanks);
            int redAlive = countAliveTanks(redTanks);

            if (blueAlive > redAlive) {
                std::cout << "Tiempo agotado. Equipo Azul ha ganado con " << blueAlive << " tanques vivos!" << std::endl;
            } else if (redAlive > blueAlive) {
                std::cout << "Tiempo agotado. Equipo Rojo ha ganado con " << redAlive << " tanques vivos!" << std::endl;
            } else {
                std::cout << "Tiempo agotado. ¡Es un empate!" << std::endl;
            }
            window.close();
        }

        window.clear();
        map.draw(window);

        if (selectedTank != nullptr) {
            selectedTank->drawPath(window);
        }

        for (auto& tank : blueTanks) {
            if (tank->isAlive()) {
                tank->draw(window);
                tank->drawHealth(window);
            }
        }
        for (auto& tank : redTanks) {
            if (tank->isAlive()) {
                tank->draw(window);
                tank->drawHealth(window);
            }
        }

        for (const auto& bullet : bullets) {
            bullet->drawPath(window);
            bullet->draw(window);
        }

        window.display();
    }

    std::cout << "Fin del juego" << std::endl;

    return 0;
}
