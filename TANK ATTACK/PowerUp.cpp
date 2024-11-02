#include "PowerUp.h"

// Constructor que asigna un power-up fijo
PowerUp::PowerUp() : type(PowerUpType::DoubleTurn) {}

// Método para obtener el tipo de power-up
PowerUpType PowerUp::getType() const {
    return type;
}

// Método para obtener el nombre del power-up como cadena
std::string PowerUp::toString() const {
    switch (type) {
        case PowerUpType::DoubleTurn: return "Doble Turno";
        case PowerUpType::MovementPrecision: return "Precisión de Movimiento";
        case PowerUpType::AttackPrecision: return "Precisión de Ataque";
        case PowerUpType::AttackPower: return "Poder de Ataque";
        default: return "Desconocido";
    }
}
