#include "Juego.h"
#include <iostream>
#include <cstdlib> // Para usar system()
#include <ctime>

using namespace std;

void mostrarPantallaInicio() {
    // Muestra la pantalla de inicio del juego
    cout << "******************************************" << endl;
    cout << "*            BIENVENIDO AL JUEGO!         *" << endl;
    cout << "* Sal con vida derrotando a los enemigos!*" << endl;
    cout << "******************************************" << endl;
    cout << "Presiona Enter para comenzar..." << endl;
    cin.ignore();
}

int main() {
    mostrarPantallaInicio();

    Juego juego;
    juego.jugar();

    return 0;
}
