#include "Bullet.h"
#include <cmath>

Bullet::Bullet(float startX, float startY, float dirX, float dirY, Tank* shooter)
    : position(startX, startY), direction(dirX, dirY), speed(300.0f), active(true), bounceCount(0), shooter(shooter) {
    shape.setRadius(3.0f);  // Radio original de la bala
    shape.setFillColor(shooter->getColor());  // Color de la bala basado en el tanque
    shape.setPosition(position);
    path.push_back(position);  // Almacenar la posición inicial en el recorrido
}

void Bullet::move(float deltaTime, const Map& map) {
    if (!active) return;

    position += direction * speed * deltaTime;
    shape.setPosition(position);
    path.push_back(position);  // Almacenar la posición en el recorrido

    int currentRow = static_cast<int>(position.y / map.getCellSize());
    int currentCol = static_cast<int>(position.x / map.getCellSize());
    int nextRow = static_cast<int>((position.y + direction.y * speed * deltaTime) / map.getCellSize());
    int nextCol = static_cast<int>((position.x + direction.x * speed * deltaTime) / map.getCellSize());

    // Verificar colisiones y rebotes en el mapa
    if (map.isObstacle(currentRow, nextCol)) {
        direction.x = -direction.x;  // Rebote en el eje X
        bounceCount++;
    }
    if (map.isObstacle(nextRow, currentCol)) {
        direction.y = -direction.y;  // Rebote en el eje Y
        bounceCount++;
    }

    if (bounceCount >= 2) {  // Desactivar después de dos rebotes
        deactivate();
    }
}

bool Bullet::checkCollision(Tank& target) const {
    if (active && shape.getGlobalBounds().intersects(target.getBounds()) && target.getColor() != shooter->getColor()) {
        target.takeDamage(25);  // Daño estándar de la bala
        return true;
    }
    return false;
}

void Bullet::draw(sf::RenderWindow& window) const {
    if (active) {
        window.draw(shape);
    }
}

void Bullet::drawPath(sf::RenderWindow& window) const {
    for (const auto& point : path) {
        sf::RectangleShape pathSegment(sf::Vector2f(2.0f, 2.0f));
        pathSegment.setFillColor(sf::Color::Green);  // Color verde del trazo
        pathSegment.setPosition(point);
        window.draw(pathSegment);
    }
}

void Bullet::deactivate() {
    active = false;
}

bool Bullet::isActive() const {
    return active;
}

sf::Color Bullet::getTeamColor() const {
    return shooter->getColor();
}

void Bullet::clearPath() {
    path.clear();
}
