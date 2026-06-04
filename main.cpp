#include <iostream>
#include <array>
#include <limits>
#include <memory>

#define FILAS 6
#define COLUMNAS 7

using namespace std;

struct Jugadores {
    string nombre1;
    string nombre2;
    char ficha1=' ';
    char ficha2=' ';
    int turno=0;
};

struct Ficha{
    char ficha=' ';
    int id=0;
};

//Solicitar datos
void inicializarJuego(Jugadores& jugadores) {
    cout << "Introduzca el nombre del jugador1" << endl;
    getline(cin, jugadores.nombre1);
    do {
        cout << "Introduzca la ficha que desea usar el jugador 1 (X-O)" << endl;
        cin >> jugadores.ficha1;
        cin.clear();
        cin.ignore(numeric_limits<streamsize> :: max(), '\n');
        if (jugadores.ficha1!='X' && jugadores.ficha1!='O') {
            cout << "Error, ficha no reconocida" << endl;
        }
    }while (jugadores.ficha1!='X' && jugadores.ficha1!='O');

    (jugadores.ficha1=='X')? jugadores.ficha2='O' : jugadores.ficha2='X';
    cout << "Introduzca el nombre del jugador2" << endl;
    getline(cin, jugadores.nombre2);
    cout << "Ficha de jugador2 (" << jugadores.ficha2 << ")" << endl;
}

//Mostrar tablero
void mostrarTablero(const array<array<Ficha, FILAS>, COLUMNAS>& tablero) {
    cout << "\n====TABLERO====" << endl;
    for (int i=0; i<FILAS; i++) {
        for (int j=0; j<COLUMNAS; j++) {
            cout << "|" << tablero.at(j).at(i).ficha;
        }
        cout << "|\n";
    }

    cout << "===============\n|0|1|2|3|4|5|6|\n" << endl;
}

//Comprobar si una columna seleccionada esta dentro del rango y hay espacio
bool comprobarPos(const array<array<Ficha, FILAS>, COLUMNAS>& tablero, const int& pos) {
    if (pos<0 || pos>6) {
        return false;
    }
    for (int i=0; i<FILAS; i++) {
        if (tablero.at(pos).at(i).ficha == ' ') {
             return true;
        }
    }
    return false;
}

//Metodo para insertar fichas si esta vacia
void insertarFicha(array<array<Ficha, FILAS>, COLUMNAS>& tablero, const char& ficha, const int& pos, const int& turno) {
    for (int i=FILAS-1; i>=0; i--) {
        if (tablero.at(pos).at(i).ficha == ' ') {
            tablero.at(pos).at(i).ficha = ficha;
            tablero.at(pos).at(i).id = turno;
            return;
        }
    }
}

//Metodos aux para la comprobacion de la victoria
bool buscarHorizontal(const array<array<Ficha, FILAS>, COLUMNAS> tablero, const char& ficha, const int& C, const int& F) {
    if (C>3) {
        return false;
    }
    if (tablero.at(C).at(F).ficha==ficha && tablero.at(C+1).at(F).ficha==ficha && tablero.at(C+2).at(F).ficha==ficha && tablero.at(C+3).at(F).ficha==ficha) {
        return true;
    }
    return false;
}

bool buscarVertical(const array<array<Ficha, FILAS>, COLUMNAS> tablero, const char& ficha, const int& C, const int& F) {
    if (F>2) {
        return false;
    }
    if (tablero.at(C).at(F).ficha==ficha && tablero.at(C).at(F+1).ficha==ficha && tablero.at(C).at(F+2).ficha==ficha && tablero.at(C).at(F+3).ficha==ficha) {
        return true;
    }
    return false;
}

bool buscarDiagonalDerInf(const array<array<Ficha, FILAS>, COLUMNAS> tablero, const char& ficha, const int& C, const int& F) {
    if (F>2 || C>3) {
        return false;
    }
    if (tablero.at(C).at(F).ficha==ficha && tablero.at(C+1).at(F+1).ficha==ficha && tablero.at(C+2).at(F+2).ficha==ficha && tablero.at(C+3).at(F+3).ficha==ficha) {
        return true;
    }
    return false;
}

bool buscarDiagonalIzqInf(const array<array<Ficha, FILAS>, COLUMNAS> tablero, const char& ficha, const int& C, const int& F) {
    if (F>2 || C<3) {
        return false;
    }
    if (tablero.at(C).at(F).ficha==ficha && tablero.at(C-1).at(F+1).ficha==ficha && tablero.at(C-2).at(F+2).ficha==ficha && tablero.at(C-3).at(F+3).ficha==ficha) {
        return true;
    }
    return false;
}

//Comprobacion victoria
bool comprobarVictoria(const array<array<Ficha, FILAS>, COLUMNAS> tablero, const char& ficha) {
    for (int i=0; i<FILAS; i++) {
        for (int j=0; j<COLUMNAS; j++) {
            if (buscarHorizontal(tablero, ficha, j, i)) {
                return true;
            }
            if (buscarVertical(tablero, ficha, j, i)) {
                return true;
            }
            if (buscarDiagonalDerInf(tablero, ficha, j, i)) {
                return true;
            }
            if (buscarDiagonalIzqInf(tablero, ficha, j, i)) {
                return true;
            }

        }
    }
    return false;
}

//Comprobacion derrota
bool comprobarDerrota(const array<array<Ficha, FILAS>, COLUMNAS>& tablero) {
    for (int j=0; j<COLUMNAS; j++) {
        if (comprobarPos(tablero, j)==true){
            return false;
        }
    }
    return true;
}

//Metodo principal para jugar
bool turno(array<array<Ficha, FILAS>, COLUMNAS>& tablero, Jugadores& jugadores) {
    int pos=0;
    bool flag = true;
    do{
        cout <<  jugadores.nombre1<<" (" << jugadores.ficha1<<") En que columna desea colocar su ficha? [0-6]" << endl;
        cin >> pos;
        cin.clear();
        cin.ignore(numeric_limits<streamsize> :: max(), '\n');
        flag=comprobarPos(tablero, pos);

        if (!flag) {
            cout << "Posicion erronea" << endl;
        }
    }while (!flag);
    insertarFicha(tablero, jugadores.ficha1, pos, ++jugadores.turno);
    mostrarTablero(tablero);
    if (comprobarVictoria(tablero, jugadores.ficha1)) {
        cout << "VICTORIA DE "<<jugadores.nombre1 << ", (Turno: "<<jugadores.turno<<")"<< endl;
        return true;
    }
    if (comprobarDerrota(tablero)) {
        cout << "DERRORTA DE AMBOS JUGADORES" << endl;
        return true;
    }

    do{
        cout <<  jugadores.nombre2<<" (" << jugadores.ficha2<<") En que columna desea colocar su ficha? [0-6]" << endl;
        cin >> pos;
        cin.clear();
        cin.ignore(numeric_limits<streamsize> :: max(), '\n');
        flag=comprobarPos(tablero, pos);

        if (!flag) {
            cout << "Posicion erronea" << endl;
        }
    }while (!flag);
    insertarFicha(tablero, jugadores.ficha2, pos, ++jugadores.turno);
    mostrarTablero(tablero);

    if (comprobarVictoria(tablero, jugadores.ficha2)) {
        cout << "VICTORIA DE "<<jugadores.nombre2 << ", (Turno: "<<jugadores.turno<<")"<< endl;
        return true;
    }
    if (comprobarDerrota(tablero)) {
        cout << "DERRORTA DE AMBOS JUGADORES" << endl;
        return true;
    }
    return false;
}

int main() {
    int repetir=0;
    do {
        Jugadores jugadores;
        array<array<Ficha, FILAS>, COLUMNAS> tablero;
        inicializarJuego(jugadores);
        mostrarTablero(tablero);
        bool flag=true;
        do {
            flag = turno(tablero, jugadores);
        }while (!flag);

        cout << "Si desea finalizar el programa presione 0" << endl;
        cin >> repetir;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (repetir!=0) {
            cout << "Juego reiniciado" << endl;
        }
    }while (repetir!=0);
    cout << "Juego finalizado con exito" << endl;
    return 0;
}
