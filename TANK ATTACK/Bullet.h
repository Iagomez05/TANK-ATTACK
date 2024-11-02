#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Tank.h"
#include "Map.h"

class Bullet {
public:
    Bullet(float startX, float startY, float dirX, float dirY, Tank* shooter);

    void move(float deltaTime, const Map& map);
    bool checkCollision(Tank& target) const;
    void draw(sf::RenderWindow& window) const;
    void drawPath(sf::RenderWindow& window) const;  // Dibuja el recorrido de la bala
    bool isActive() const;
    void deactivate();
    sf::Color getTeamColor() const;
    void clearPath();  // Limpia el recorrido de la bala

private:
    sf::Vector2f position;
    sf::Vector2f direction;
    float speed;
    bool active;
    int bounceCount;  // Contador de rebotes
    Tank* shooter;
    sf::CircleShape shape;
    std::vector<sf::Vector2f> path;  // Almacena el recorrido de la bala
};

#endif // BULLET_H
