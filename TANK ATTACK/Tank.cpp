#include "Tank.h"
#include <iostream>
#include <cmath>
#include "Map.h"

// Constructor que carga la textura del tanque y establece su posición
Tank::Tank(float x, float y, const std::string& textureFile) : speed(100.0f) {  // Velocidad del tanque (100 px/s)
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "No se pudo cargar la textura del tanque" << std::endl;
    }

    sprite.setTexture(texture);           // Asignar la textura al sprite
    sprite.setPosition(x, y);             // Establecer la posición inicial del tanque
    targetPosition = sprite.getPosition();  // Iniciar el objetivo en la posición actual
}

// Dibuja el tanque en la ventana
void Tank::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

// Actualiza la posición del tanque moviéndolo hacia la meta
void Tank::update(float deltaTime, const Map& map) {
    // Obtener la posición actual del tanque
    sf::Vector2f currentPosition = sprite.getPosition();

    // Calcular la dirección hacia la meta
    sf::Vector2f direction = targetPosition - currentPosition;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    // Si el tanque no está en la posición objetivo, sigue moviéndolo
    if (distance > 1.0f) {  // Umbral para evitar movimientos muy pequeños
        // Normalizar el vector de dirección
        direction /= distance;

        // Calcular el desplazamiento basado en la velocidad y el deltaTime
        sf::Vector2f movement = direction * speed * deltaTime;
        sf::Vector2f newPosition = currentPosition + movement;

        // Obtener los límites del tanque
        sf::FloatRect bounds = sprite.getGlobalBounds();

        // Verificar si alguna esquina del tanque colisiona con un muro
        if (!map.isObstacle(newPosition.x, newPosition.y) && // Esquina superior izquierda
            !map.isObstacle(newPosition.x + bounds.width, newPosition.y) && // Esquina superior derecha
            !map.isObstacle(newPosition.x, newPosition.y + bounds.height) && // Esquina inferior izquierda
            !map.isObstacle(newPosition.x + bounds.width, newPosition.y + bounds.height)) { // Esquina inferior derecha
            // Si no hay colisión, mover el tanque
            sprite.move(movement);
        }
    }
}

// Establecer la posición objetivo (meta) del tanque
void Tank::setTargetPosition(float x, float y) {
    targetPosition = sf::Vector2f(x, y);
}

// Devuelve el sprite del tanque (usado para detección de clics)
const sf::Sprite& Tank::getSprite() const {
    return sprite;
}
