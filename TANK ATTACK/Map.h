#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>

class Map {
public:
    Map(int rows, int cols, int cellSize);
    void draw(sf::RenderWindow& window) const;
    bool isObstacle(int row, int col) const;
    int getRows() const;
    int getCols() const;

    std::vector<sf::Vector2i> findPathBFS(int startRow, int startCol, int targetRow, int targetCol) const;

private:
    int rows, cols, cellSize;
    std::vector<std::vector<bool>> grid;
};

#endif // MAP_H
