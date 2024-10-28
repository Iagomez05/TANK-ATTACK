#include "Tank.h"
#include <cmath>
#include <iostream>

Tank::Tank(int row, int col, sf::Color color, int cellSize)
    : row(row), col(col), targetRow(row), targetCol(col), cellSize(cellSize), moveSpeed(1.0f), pathIndex(0) {
    shape.setSize(sf::Vector2f(cellSize - 1, cellSize - 1));
    shape.setFillColor(color);
    shape.setPosition(col * cellSize, row * cellSize);
}

void Tank::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

void Tank::drawPath(sf::RenderWindow& window) const {
    for (size_t i = pathIndex; i < path.size(); ++i) {
        sf::RectangleShape pathCell(sf::Vector2f(cellSize - 1, cellSize - 1));
        pathCell.setFillColor(sf::Color(128, 128, 255, 150)); // Color semitransparente para la ruta
        pathCell.setPosition(path[i].x * cellSize, path[i].y * cellSize);
        window.draw(pathCell);
    }
}

void Tank::setTarget(int targetRow, int targetCol, const Map& map) {
    this->targetRow = targetRow;
    this->targetCol = targetCol;
    calculatePath(map);
}

void Tank::calculatePath(const Map& map) {
    path = map.findPathBFS(row, col, targetRow, targetCol);
    pathIndex = 0;
    std::cout << "Ruta calculada (BFS): " << path.size() << " pasos.\n";
}

void Tank::moveTowardsTarget(const Map& map, float deltaTime) {
    if (isAtTarget() || pathIndex >= path.size()) return;

    int nextRow = path[pathIndex].y;
    int nextCol = path[pathIndex].x;

    if (deltaTime > 0) {
        row = nextRow;
        col = nextCol;
        shape.setPosition(col * cellSize, row * cellSize);
        pathIndex++;
    }
}

bool Tank::isAtTarget() const {
    return row == targetRow && col == targetCol;
}

bool Tank::contains(int x, int y) const {
    return shape.getGlobalBounds().contains(x, y);
}