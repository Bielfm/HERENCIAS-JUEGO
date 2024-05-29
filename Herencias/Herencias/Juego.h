#ifndef JUEGO_H
#define JUEGO_H

#include "Personaje.h"
#include "EnemigoFinal.h"

class Juego {
private:
    static const int FILAS = 5;
    static const int COLUMNAS = 5;
    static const int NUM_ENEMIGOS = 4;
    char tablero[FILAS][COLUMNAS];
    Personaje heroe;
    Personaje enemigos[NUM_ENEMIGOS];
    EnemigoFinal enemigoFinal;
    void inicializarTablero();
    void mostrarTablero();
    void mostrarBarraVida(Personaje& personaje);
    void moverHeroe(char direccion);
    void encuentro(Personaje& enemigo);
    void batalla(Personaje& enemigo);
    void batallaFinal();
    bool intentarHuir();

public:
    Juego();
    void jugar();
};

#endif
