#ifndef POWERUP_H
#define POWERUP_H

#include <string>

enum class PowerUpType {
    DoubleTurn,
    MovementPrecision,
    AttackPrecision,
    AttackPower
};

class PowerUp {
public:
    PowerUp();  // Constructor predeterminado (asigna un power-up fijo)

    PowerUpType getType() const;  // Obtener el tipo de power-up
    std::string toString() const; // Obtener el nombre del power-up como cadena

private:
    PowerUpType type;  // Tipo de power-up
};

#endif // POWERUP_H
