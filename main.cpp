#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <cstdio>

using namespace std;

void ocultarCursor() // Funcion para ocultar el cursor de la consola
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void esperarTecla() // Funcion para esperar a que se presione una tecla
{
    cout << endl << "Presione <ESCAPE> para volver al menu principal" << endl;

    while (true)
    {
        if (_kbhit())
        {
            char tecla = _getch();
            if (tecla == 27) // 27 es el codigo ASCII del ESCAPE
            {
                break;
            }
        }
    }
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

    cout << "-------------------";
    cout << "Juego";
    cout << "-------------------" << endl;
    cout << "\"Aqui va el juego\"" << endl;

    esperarTecla();
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
