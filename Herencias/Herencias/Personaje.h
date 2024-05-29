#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <string>
using namespace std;

class Personaje {
private:
    string nombre;
    int vida;
    int ataque;
    int posicionX;
    int posicionY;

public:
    Personaje();
    Personaje(string nombre, int vida, int ataque, int posicionX, int posicionY);

    string getNombre();
    int getVida();
    int getAtaque();
    int getPosicionX();
    int getPosicionY();

    void setPosicion(int x, int y);
    void recibirDaño(int cantidad);
    bool estaVivo();
};

#endif
