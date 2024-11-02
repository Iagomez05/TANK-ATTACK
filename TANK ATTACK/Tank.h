#ifndef TANK_H
#define TANK_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Map.h"

class Tank {
public:
    Tank(int row, int col, sf::Color color, int cellSize);

    void draw(sf::RenderWindow& window) const;
    void drawPath(sf::RenderWindow& window) const;
    void drawHealth(sf::RenderWindow& window) const;  // Dibuja la vida del tanque en pantalla
    void setTarget(int targetRow, int targetCol, const Map& map);
    void moveTowardsTarget(const Map& map, float deltaTime);
    bool isAtTarget() const;
    bool contains(int x, int y) const;
    void takeDamage(int damage);  // Reduce la vida del tanque
    bool isAlive() const;  // Verifica si el tanque sigue vivo
    sf::Vector2f getPosition() const;  // Devuelve la posición del tanque
    sf::FloatRect getBounds() const;   // Devuelve los límites del tanque para detección de colisiones
    sf::Color getColor() const;        // Devuelve el color del tanque (para identificar el equipo)

private:
    int row, col;
    int targetRow, targetCol;
    int cellSize;
    float moveSpeed;
    int health;  // Vida del tanque
    std::vector<sf::Vector2i> path;
    int pathIndex;

    sf::RectangleShape shape;
    sf::Color tankColor;

    void calculatePath(const Map& map);
};

#endif // TANK_H
