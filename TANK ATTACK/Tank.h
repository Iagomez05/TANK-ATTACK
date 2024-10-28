#ifndef TANK_H
#define TANK_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Map.h"

class Tank {
public:
    Tank(int row, int col, sf::Color color, int cellSize);

    void draw(sf::RenderWindow& window) const;
    void drawPath(sf::RenderWindow& window) const;  // Dibuja la ruta
    void setTarget(int targetRow, int targetCol, const Map& map);
    void moveTowardsTarget(const Map& map, float deltaTime);
    bool isAtTarget() const;
    bool contains(int x, int y) const;

private:
    int row, col;
    int targetRow, targetCol;
    int cellSize;
    float moveSpeed;
    std::vector<sf::Vector2i> path;
    int pathIndex;

    sf::RectangleShape shape;

    void calculatePath(const Map& map);
};

#endif // TANK_H