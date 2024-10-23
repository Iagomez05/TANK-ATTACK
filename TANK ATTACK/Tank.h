#ifndef TANK_H
#define TANK_H

#include <SFML/Graphics.hpp>
#include "Map.h"

class Tank {
public:
    // Constructor para cargar la textura del tanque y establecer su posición inicial
    Tank(float x, float y, const std::string& textureFile);

    // Dibuja el tanque en la ventana
    void draw(sf::RenderWindow &window);

    // Mueve el tanque hacia la posición objetivo (destino)
    void update(float deltaTime, const Map& map);  // Agregamos el parámetro Map aquí

    // Establecer el destino al que debe moverse el tanque
    void setTargetPosition(float x, float y);

    // Devuelve el sprite del tanque para la detección de clics
    const sf::Sprite& getSprite() const;

private:
    sf::Sprite sprite;  // Sprite para el tanque
    sf::Texture texture;  // Textura del tanque

    sf::Vector2f targetPosition;  // Posición objetivo hacia la que se moverá el tanque
    float speed;  // Velocidad de movimiento del tanque
};

#endif // TANK_H
