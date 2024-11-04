#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <cstdio>

using namespace std;

const char CUBO = 219; // Carácter que representa un cubo en la consola
const int COLOR_FONDO = 8; // Color de fondo de la consola (gris)
const int COLOR_COCHE = 10; // Color del cubo (verde)
const int COLOR_COCHE_ROJO = 12; // Color del coche rojo
const int ANCHO = 100; // Ancho de la consola
const int ALTO = 40; // Alto de la consola

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

    // Dibujar el primer bloque (0 a 25 horizontal, 0 a 40 vertical, color gris)
    color(COLOR_FONDO);
    for (int i = 0; i < ALTO; i++)
    {
        gotoxy(0, i);
        for (int j = 0; j < 25; j++)
        {
            cout << CUBO;
        }
    }

    // Dibujar el segundo bloque (25 a 75 horizontal, 0 a 40 vertical, color negro)
    color(0); // Color negro
    for (int i = 0; i < ALTO; i++)
    {
        gotoxy(25, i);
        for (int j = 0; j < 50; j++)
        {
            cout << CUBO;
        }
    }

    // Dibujar líneas blancas para simular una carretera de 3 carriles
    color(15); // Color blanco
    for (int i = 0; i < ALTO; i += 4) // Espaciado entre líneas
    {
        gotoxy(41, i); // Línea central
        cout << CUBO;
        gotoxy(58, i); // Línea derecha
        cout << CUBO;
    }

    // Dibujar el tercer bloque (75 a 100 horizontal, 0 a 40 vertical, color gris)
    color(COLOR_FONDO);
    for (int i = 0; i < ALTO; i++)
    {
        gotoxy(75, i);
        for (int j = 0; j < 25; j++)
        {
            cout << CUBO;
        }
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
    dibujarCoche(x, y, 0); // Dibujar el coche con color negro para borrar
}

void redibujarLineas()
{
    color(15); // Color blanco
    for (int i = 0; i < ALTO; i += 4) // Espaciado entre líneas
    {
        gotoxy(41, i); // Línea central
        cout << CUBO;
        gotoxy(58, i); // Línea derecha
        cout << CUBO;
    }
}

void moverCoche(int& x, int& y, int& dx, int& dy, int velocidad)
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

    // Mantener el coche dentro de los límites horizontales de 25 a 75
    if (x < 25) x = 25;
    if (x >= 75 - 6) x = 75 - 6; // 6 es el ancho del coche

    // Mantener el coche dentro de los límites verticales
    if (y < 0) y = 0;
    if (y >= ALTO - 4) y = ALTO - 4; // 4 es la altura del coche

    redibujarLineas(); // Redibujar las líneas blancas
    dibujarCoche(x, y, COLOR_COCHE);
}

void moverCocheRojo(int& x, int& y, int velocidad)
{
    borrarCoche(x, y);

    y += velocidad;

    // Mantener el coche dentro de los límites verticales
    if (y >= ALTO - 4) y = 0; // Reiniciar la posición vertical cuando llegue al final

    dibujarCoche(x, y, COLOR_COCHE_ROJO);
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

    // Calcular las coordenadas iniciales para centrar el coche verde
    int xVerde = 25 + (75 - 25) / 2 - 3; // 3 es la mitad del ancho del coche
    int yVerde = ALTO / 2 - 2; // 2 es la mitad de la altura del coche
    int dxVerde = 0, dyVerde = 0;
    int velocidadVerde = 1; // Velocidad del coche verde

    // Coordenadas iniciales para el coche rojo
    int xRojo = 50; // Posición horizontal del coche rojo
    int yRojo = 0; // Posición vertical inicial del coche rojo
    int velocidadRojo = 1; // Velocidad del coche rojo

    ocultarCursor();
    dibujarEscenario();
    dibujarCoche(xVerde, yVerde, COLOR_COCHE);
    dibujarCoche(xRojo, yRojo, COLOR_COCHE_ROJO);

    while (true)
    {
        if (_kbhit())
        {
            char tecla = _getch();
            if (tecla == 27) exit(0); // Salir si se presiona ESC
            else if (tecla == 72) { dxVerde = 0; dyVerde = -1; } // Arriba
            else if (tecla == 80) { dxVerde = 0; dyVerde = 1; } // Abajo
            else if (tecla == 77) { dxVerde = 1; dyVerde = 0; } // Derecha
            else if (tecla == 75) { dxVerde = -1; dyVerde = 0; } // Izquierda
        }

        borrarCoche(xVerde, yVerde);
        xVerde += dxVerde * velocidadVerde;
        yVerde += dyVerde * velocidadVerde;
        if (xVerde < 25) xVerde = 25;
        if (xVerde >= 75 - 6) xVerde = 75 - 6; // 6 es el ancho del coche
        if (yVerde < 0) yVerde = 0;
        if (yVerde >= ALTO - 4) yVerde = ALTO - 4; // 4 es la altura del coche

        borrarCoche(xRojo, yRojo);
        yRojo += velocidadRojo;
        if (yRojo >= ALTO - 4) yRojo = 0; // Reiniciar la posición vertical cuando llegue al final

        redibujarLineas(); // Redibujar las líneas blancas
        dibujarCoche(xVerde, yVerde, COLOR_COCHE);
        dibujarCoche(xRojo, yRojo, COLOR_COCHE_ROJO);

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
