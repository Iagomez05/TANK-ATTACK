#include "Map.h"
#include <queue>

Map::Map(int rows, int cols, int cellSize)
    : rows(rows), cols(cols), cellSize(cellSize), grid(rows, std::vector<bool>(cols, false)) {
    // Configuración de bordes
    for (int i = 0; i < rows; ++i) {
        grid[i][0] = grid[i][cols - 1] = true;
    }
    for (int j = 0; j < cols; ++j) {
        grid[0][j] = grid[rows - 1][j] = true;
    }

    // Obstáculos internos distribuidos
    for (int i = 5; i < rows - 5; i += 4) {
        for (int j = 3; j < cols - 3; j += 5) {
            grid[i][j] = grid[i + 1][j] = true;
            grid[i][j + 1] = grid[i + 1][j + 1] = true;
        }
    }
}

void Map::draw(sf::RenderWindow& window) const {
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
            cell.setPosition(col * cellSize, row * cellSize);
            cell.setFillColor(grid[row][col] ? sf::Color(64, 64, 64) : sf::Color(211, 211, 211));
            window.draw(cell);
        }
    }
}

bool Map::isObstacle(int row, int col) const {
    return grid[row][col];
}

int Map::getRows() const {
    return rows;
}

int Map::getCols() const {
    return cols;
}

std::vector<sf::Vector2i> Map::findPathBFS(int startRow, int startCol, int targetRow, int targetCol) const {
    std::vector<sf::Vector2i> path;
    if (isObstacle(targetRow, targetCol)) return path;

    std::queue<sf::Vector2i> queue;
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    std::vector<std::vector<sf::Vector2i>> parent(rows, std::vector<sf::Vector2i>(cols, {-1, -1}));

    queue.push({startCol, startRow});
    visited[startRow][startCol] = true;

    const sf::Vector2i directions[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    while (!queue.empty()) {
        sf::Vector2i current = queue.front();
        queue.pop();

        if (current.y == targetRow && current.x == targetCol) {
            for (sf::Vector2i at = {targetCol, targetRow}; at.x != -1; at = parent[at.y][at.x]) {
                path.push_back(at);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (const sf::Vector2i& dir : directions) {
            int newRow = current.y + dir.y;
            int newCol = current.x + dir.x;

            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
                !visited[newRow][newCol] && !isObstacle(newRow, newCol)) {
                queue.push({newCol, newRow});
                visited[newRow][newCol] = true;
                parent[newRow][newCol] = current;
            }
        }
    }
    return path;
}
