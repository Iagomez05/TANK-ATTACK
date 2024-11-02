#include "Map.h"
#include <queue>

Map::Map(int rows, int cols, int cellSize)
    : rows(rows), cols(cols), cellSize(cellSize), grid(rows, std::vector<bool>(cols, false)) {
    // Configuración de obstáculos y bordes
    for (int i = 0; i < rows; ++i) {
        grid[i][0] = grid[i][cols - 1] = true;
    }
    for (int j = 0; j < cols; ++j) {
        grid[0][j] = grid[rows - 1][j] = true;
    }

    // Obstáculos internos (ajustados para cubrir más espacios en el mapa)
    grid[4][4] = grid[5][5] = grid[6][6] = true;
    grid[7][8] = grid[8][8] = grid[9][8] = true;
    grid[10][10] = grid[11][10] = grid[12][10] = true;
    grid[4][15] = grid[5][15] = grid[6][15] = true;
    grid[7][20] = grid[8][20] = grid[9][20] = true;
    grid[6][12] = grid[7][12] = grid[8][12] = true;
    grid[10][15] = grid[11][15] = grid[12][15] = true;
    grid[14][4] = grid[15][5] = grid[16][6] = true;
    grid[14][18] = grid[15][18] = grid[16][18] = true;
    grid[10][22] = grid[11][22] = grid[12][22] = true;
    grid[15][10] = grid[16][11] = grid[17][12] = true;
    grid[3][18] = grid[4][18] = grid[5][18] = true;
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

int Map::getCellSize() const {
    return cellSize;
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
