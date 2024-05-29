#include "Personaje.h"

Personaje::Personaje() : nombre(""), vida(0), ataque(0), posicionX(0), posicionY(0) {}

Personaje::Personaje(string nombre, int vida, int ataque, int posicionX, int posicionY)
    : nombre(nombre), vida(vida), ataque(ataque), posicionX(posicionX), posicionY(posicionY) {}

string Personaje::getNombre() {
    return nombre;
}

int Personaje::getVida() {
    return vida;
}

int Personaje::getAtaque() {
    return ataque;
}

int Personaje::getPosicionX() {
    return posicionX;
}

int Personaje::getPosicionY() {
    return posicionY;
}

void Personaje::setPosicion(int x, int y) {
    posicionX = x;
    posicionY = y;
}

void Personaje::recibirDaño(int cantidad) {
    vida -= cantidad;
}

bool Personaje::estaVivo() {
    return vida > 0;
}
