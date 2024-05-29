#include "Juego.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <stdlib.h>
using namespace std;


Juego::Juego()
    : heroe("Heroe", 100, 20, 0, 0),
    enemigoFinal("Enemigo Final", 150, 15, FILAS - 1, rand() % COLUMNAS, 35, 40) {
    srand(static_cast<unsigned>(time(0)));
    // INICIA A LOS ENEMIGOS EN POSICIONES ALEATORIAS
    for (int i = 0; i < NUM_ENEMIGOS; ++i) {
        int x = rand() % FILAS;
        int y = rand() % COLUMNAS;
        enemigos[i] = Personaje("Enemigo", 50, 10, x, y);
    }
    inicializarTablero();
}

void Juego::inicializarTablero() {
    // INICIA Y PONE LOS PUNTOS Y LOS ENEMIGOS EN EL TABLERO
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            tablero[i][j] = '.';
        }
    }
    tablero[heroe.getPosicionX()][heroe.getPosicionY()] = 'H';
    for (int i = 0; i < NUM_ENEMIGOS; ++i) {
        tablero[enemigos[i].getPosicionX()][enemigos[i].getPosicionY()] = 'E';
    }
    tablero[enemigoFinal.getPosicionX()][enemigoFinal.getPosicionY()] = 'F';
}

void Juego::mostrarTablero() {
    // ESTO PARA QUE EN EL TERMINAL NO APAREZCA UNO ABAJO DE OTRO Y SE BORRE CADA VEZ QUE HACES UN COMANDO
    system("CLS");
    // MUESTRA EL ESTADO ACTUAL DEL TABLERO
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            cout << tablero[i][j] << ' ';
        }
        cout << endl;
    }
}

void Juego::mostrarBarraVida( Personaje& personaje) {
    // BARRA DE VIDA GRÁFICA PERSONAJE
    int vida = personaje.getVida();
    cout << personaje.getNombre() << " [";
    for (int i = 0; i < 20; ++i) {
        if (i < vida / 5) {
            cout << "#";
        }
        else {
            cout << " ";
        }
    }
    cout << "] " << vida << "/100" << endl;
}

void Juego::moverHeroe(char direccion) {
    // MOVIMIENTO DEL HEROE CON WASD
    int nuevaX = heroe.getPosicionX();
    int nuevaY = heroe.getPosicionY();

    switch (direccion) {
    case 'w': if (nuevaX > 0) nuevaX--; break;
    case 's': if (nuevaX < FILAS - 1) nuevaX++; break;
    case 'a': if (nuevaY > 0) nuevaY--; break;
    case 'd': if (nuevaY < COLUMNAS - 1) nuevaY++; break;
    default: break;
    }
    // SI EL TABLERO MUESTRA UNA E ES UN ENEMIGO, Y SI ES EL F ES LA BATALLA FINAL
    if (tablero[nuevaX][nuevaY] == 'E') {
        for (int i = 0; i < NUM_ENEMIGOS; ++i) {
            if (enemigos[i].getPosicionX() == nuevaX && enemigos[i].getPosicionY() == nuevaY) {
                encuentro(enemigos[i]);
                break;
            }
        }
    }
    else if (tablero[nuevaX][nuevaY] == 'F') {
        batallaFinal();
    }
    else {
        tablero[heroe.getPosicionX()][heroe.getPosicionY()] = '.';
        heroe.setPosicion(nuevaX, nuevaY);
        tablero[nuevaX][nuevaY] = 'H';
    }
}

void Juego::encuentro(Personaje& enemigo) {
    // INTERACCIÓN CON LOS ENEMIGOS
    cout << "Te has encontrado con un enemigo!" << endl;
    cout << "Elige tu acción (c: combatir, h: huir): ";
    char accion;
    cin >> accion;

    if (accion == 'h') {
        if (intentarHuir()) {
            cout << "Has logrado huir!" << endl;
            return;
        }
        else {
            cout << "No has podido huir, debes combatir!" << endl;
        }
    }

    batalla(enemigo);
}

bool Juego::intentarHuir() {
    // 50% DE QUE HUYAS DEL COMBATE
    return rand() % 2 == 0;
}

void Juego::batalla(Personaje& enemigo) {
    // COMBATE ENEMIGOS
    cout << "Batalla contra " << enemigo.getNombre() << "!" << endl;
    while (heroe.estaVivo() && enemigo.estaVivo()) {
        cout << "Elige tu acción (a: atacar, d: defender): ";
        char accion;
        cin >> accion;

        if (accion == 'a') {
            enemigo.recibirDaño(heroe.getAtaque());
        }
        else if (accion == 'd') {
            cout << "Gracias a la defensa recibes menos daño!" << endl;
        }

        if (enemigo.estaVivo()) {
            int dañoEnemigo = enemigo.getAtaque();
            if (accion == 'd') {
                dañoEnemigo /= 2;
            }
            heroe.recibirDaño(dañoEnemigo);
        }

        cout << "Estado de la batalla:" << endl;
        mostrarBarraVida(heroe);
        mostrarBarraVida(enemigo);
    }

    if (heroe.estaVivo()) {
        cout << "Has derrotado al enemigo!" << endl;
        tablero[enemigo.getPosicionX()][enemigo.getPosicionY()] = 'H';
        heroe.setPosicion(enemigo.getPosicionX(), enemigo.getPosicionY());
    }
    else {
        cout << "Has sido derrotado!" << endl;
    }
}

void Juego::batallaFinal() {
    // BATALLA FINAL 
    cout << "Batalla final contra " << enemigoFinal.getNombre() << "!" << endl;
    while (heroe.estaVivo() && enemigoFinal.estaVivo()) {
        cout << "Elige tu acción (a: atacar, d: defender): ";
        char accion;
        cin >> accion;

        if (accion == 'a') {
            enemigoFinal.recibirDaño(heroe.getAtaque());
        }
        else if (accion == 'd') {
            cout << "Gracias a la defensa recibes menos daño! " << endl;
        }

        if (enemigoFinal.estaVivo()) {
            int dañoEnemigo = (rand() % 3 == 0) ? enemigoFinal.ejecutarSuperAtaque() : enemigoFinal.getAtaque();
            if (accion == 'd') {
                dañoEnemigo /= 2;
            }
            heroe.recibirDaño(dañoEnemigo);
        }

        cout << "Estado de la batalla:" << endl;
        mostrarBarraVida(heroe);
        mostrarBarraVida(enemigoFinal);
    }

    if (heroe.estaVivo()) {
        cout << "Has derrotado al enemigo final!" << endl;
    }
    else {
        cout << "Has sido derrotado!" << endl;
    }
}

void Juego::jugar() {
    // BUCLE DEL HEROE Y JUEGO
    while (heroe.estaVivo() && enemigoFinal.estaVivo()) {
        mostrarTablero();
        char movimiento;
        cout << "Mueve al heroe (w: arriba, s: abajo, a: izquierda, d: derecha): ";
        cin >> movimiento;
        moverHeroe(movimiento);
    }

    if (heroe.estaVivo()) {
        cout << "******************************************" << endl;
        cout << "*           HAS GANAD0!                  *" << endl;
        cout << "*     ME TOCARÁ DARTE UN JAMON NAVIDUL   *" << endl;        
        cout << "******************************************" << endl;
    }
    else {
        cout << "******************************************" << endl;
        cout << "*            GAME OVER!                  *" << endl;
        cout << "*         ME DEBES UN BIZUM DE 5E        *" << endl;
        cout << "******************************************" << endl;
    }
}
