#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>

class Map {
public:
    // Constructor que recibe las imágenes del mapa de fondo y de los muros
    Map(const std::string& mapImageFile, const std::string& wallImageFile);

    // Función para dibujar el mapa y los muros en la ventana
    void draw(sf::RenderWindow &window);

    // Función que verifica si una posición (x, y) tiene un muro
    bool isObstacle(float x, float y) const;  // Se mantiene la palabra clave const aquí

private:
    sf::Texture mapTexture;  // Textura del mapa de fondo
    sf::Sprite mapSprite;    // Sprite para el mapa de fondo

    sf::Texture wallTexture;  // Textura para los muros
    std::vector<sf::Sprite> walls;  // Vector que almacena los sprites de los muros

    // Función que crea los muros en posiciones fijas
    void createFixedWalls();
};

#endif // MAP_H
