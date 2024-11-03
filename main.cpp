#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <cstdio>

using namespace std;

const char CUBO = 219; // Carácter que representa un cubo en la consola
const int COLOR_FONDO = 8; // Color de fondo de la consola (gris)
const int COLOR_COCHE = 10; // Color del cubo (verde)
const int ANCHO = 80; // Ancho de la consola
const int ALTO = 25; // Alto de la consola

void ocultarCursor() // Funcion para ocultar el cursor de la consola
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void color(int color) // Función para cambiar el color de la letra
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(consoleHandle, color);
}

void esperarTecla() // Funcion para esperar a que se presione una tecla
{
    cout << endl << "Presione <ESCAPE> para volver al menu principal" << endl;
    char tecla;
    do
    {
        tecla = _getch();
    }
    while (tecla != 27); // 27 es el codigo ASCII del ESCAPE
}

void gotoxy(int x, int y) // Funcion para mover el cursor a una posicion especifica de la consola (x, y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void dibujarEscenario() // Funcion para dibujar el escenario del juego
{
    ocultarCursor();
    color(COLOR_FONDO);

    for (int i = 0; i < ALTO; i++)
    {
        cout << string(ANCHO, CUBO) << endl;
    }
}

void dibujarCoche(int x, int y, int colorCubo) // Funcion para dibujar el coche en la posicion (x, y)
{
    color(colorCubo);

    gotoxy(x + 2, y);
    cout << CUBO;
    gotoxy(x + 3, y);
    cout << CUBO;
    gotoxy(x, y + 1);
    cout << CUBO;
    gotoxy(x + 1, y + 1);
    cout << CUBO;
    gotoxy(x + 2, y + 1);
    cout << CUBO;
    gotoxy(x + 3, y + 1);
    cout << CUBO;
    gotoxy(x + 4, y + 1);
    cout << CUBO;
    gotoxy(x + 5, y + 1);
    cout << CUBO;
    gotoxy(x + 2, y + 2);
    cout << CUBO;
    gotoxy(x + 3, y + 2);
    cout << CUBO;
    gotoxy(x, y + 3);
    cout << CUBO;
    gotoxy(x + 1, y + 3);
    cout << CUBO;
    gotoxy(x + 2, y + 3);
    cout << CUBO;
    gotoxy(x + 3, y + 3);
    cout << CUBO;
    gotoxy(x + 4, y + 3);
    cout << CUBO;
    gotoxy(x + 5, y + 3);
    cout << CUBO;
}

void borrarCoche(int x, int y)
{
    dibujarCoche(x, y, COLOR_FONDO);
}

void moverCoche(int &x, int &y, int &dx, int &dy, int velocidad)
{
    if (_kbhit())
    {
        char tecla = _getch();

        if (tecla == 27) exit(0); // Salir si se presiona ESC

        else if (tecla == 72) // Arriba
        {
            dx = 0;
            dy = -1;
        }
        else if (tecla == 80) // Abajo
        {
            dx = 0;
            dy = 1;
        }
        else if (tecla == 77) // Derecha
        {
            dx = 1;
            dy = 0;
        }
        else if (tecla == 75) // Izquierda
        {
            dx = -1;
            dy = 0;
        }
    }

    borrarCoche(x, y);

    x += dx * velocidad;
    y += dy * velocidad;

    // Mantener el coche dentro de los límites
    if (x < 0) x = 0;
    if (x >= ANCHO - 6) x = ANCHO - 6;
    if (y < 0) y = 0;
    if (y >= ALTO - 4) y = ALTO - 4;

    dibujarCoche(x, y, COLOR_COCHE);
}

void instrucciones() // Funcion para mostrar las instrucciones
{
    system("cls");

    cout << "-------------------";
    cout << "Instrucciones";
    cout << "-------------------" << endl;
    cout << "\"Aqui van las instrucciones\"" << endl;

    esperarTecla();
}

void creditos()
{
    system("cls");

    cout << "-------------------";
    cout << "Creditos";
    cout << "-------------------" << endl;
    cout << "\"Aqui van las instrucciones\"" << endl;

    esperarTecla();
}

void salir()
{
    system("cls");

    cout << "Gracias por jugar!" << endl;
}

void juego()
{
    system("cls");

    int x = 0, y = 0;
    int dx = 0, dy = 0;
    int velocidad = 1; // Velocidad del coche

    ocultarCursor();
    dibujarEscenario();
    dibujarCoche(x, y, COLOR_COCHE);

    while (true)
    {
        moverCoche(x, y, dx, dy, velocidad);
        Sleep(30);
    }
}

int main() // FUNCION PRINCIPAL
{
    ocultarCursor();

    while (true)
    {
        system("cls");

        cout << "-------------------";
        cout << "Between Lines";
        cout << "-------------------" << endl;
        cout << "[1] Jugar" << endl;
        cout << "[2] Instrucciones" << endl;
        cout << "[3] Creditos" << endl;
        cout << "[4] Salir" << endl;

        char tecla = _getch(); // Espera a que se presione una tecla

        switch (tecla)
        {
        case '1':
            juego();
            break;
        case '2':
            instrucciones();
            break;
        case '3':
            creditos();
            break;
        case '4':
            salir();
            return 0; /// Termina el programa
        }
    }
}
