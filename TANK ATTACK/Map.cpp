#include "Map.h"
#include <iostream>

// Constructor para cargar el mapa de fondo y los muros
Map::Map(const std::string& mapImageFile, const std::string& wallImageFile) {
    // Cargar la textura del mapa de fondo desde un archivo
    if (!mapTexture.loadFromFile(mapImageFile)) {
        std::cerr << "Error al cargar la imagen del mapa" << std::endl;
    }
    mapSprite.setTexture(mapTexture);

    // Cargar la textura de los muros desde un archivo
    if (!wallTexture.loadFromFile(wallImageFile)) {
        std::cerr << "Error al cargar la textura de los muros" << std::endl;
    }

    // Crear los muros en posiciones específicas
    createFixedWalls();
}

// Crear muros en posiciones fijas
void Map::createFixedWalls() {
    const int wallSize = 51;  // Tamaño del muro (51x51 según tu imagen)
    const int offsetX = -70;  // Ajuste adicional para mover los muros más a la izquierda

    // Muro vertical en el lado izquierdo
    for (int i = 0; i < 5; ++i) {  // Crear una columna de 5 muros
        sf::Sprite wall;
        wall.setTexture(wallTexture);
        wall.setPosition(150 + offsetX, 150 + i * wallSize);  // Mover más a la izquierda
        walls.push_back(wall);
    }

    // Muro horizontal en la parte superior central
    for (int i = 0; i < 6; ++i) {  // Crear una fila de 6 muros
        sf::Sprite wall;
        wall.setTexture(wallTexture);
        wall.setPosition(300 + i * wallSize + offsetX, 100);  // Mover más a la izquierda
        walls.push_back(wall);
    }

    // Muro horizontal en la parte inferior central
    for (int i = 0; i < 6; ++i) {
        sf::Sprite wall;
        wall.setTexture(wallTexture);
        wall.setPosition(300 + i * wallSize + offsetX, 500);  // Mover más a la izquierda
        walls.push_back(wall);
    }

    // Muro vertical en el lado derecho
    for (int i = 0; i < 5; ++i) {
        sf::Sprite wall;
        wall.setTexture(wallTexture);
        wall.setPosition(750 + offsetX, 150 + i * wallSize);  // Mover más a la izquierda
        walls.push_back(wall);
    }
}

// Función para dibujar el mapa y los muros en la ventana
void Map::draw(sf::RenderWindow &window) {
    // Dibujar el mapa de fondo
    window.draw(mapSprite);

    // Dibujar cada uno de los muros
    for (const auto& wall : walls) {
        window.draw(wall);
    }
}

// Verificar si hay un muro en la posición (x, y)
bool Map::isObstacle(float x, float y) const {
    for (const auto& wall : walls) {
        if (wall.getGlobalBounds().contains(x, y)) {
            return true;  // Si la posición está dentro de un muro, retornar true
        }
    }
    return false;  // Si no hay muro en la posición, retornar false
}
