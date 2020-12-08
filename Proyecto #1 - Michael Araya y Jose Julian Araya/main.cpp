#include <iostream>
#include "Trie.h"
#include <fstream>
#include <Windows.h>

using namespace std;

int main()
{
    setlocale(LC_ALL, "spanish");
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);

    cout << "Bienvenido!" << endl;
    cout << "Este programa usa la estructura de datos AVL para analizar datos sobre un archivo" << endl;

    string myText;
    // Read from the text file

    string nombreArchivo = "";

    cout << "Ingrese el nombre del archivo que va a utilizar" << endl;
    cin >> nombreArchivo;


        ifstream MyReadFile(nombreArchivo + ".txt");
    if(MyReadFile.fail()){
        cout << "No es posible abrir el archivo" << endl;
    }else {
        int i = 1;

        while (getline (MyReadFile, myText)) {
            // Output the text from the file
            cout << myText << endl;
            i += 1;
        }

        cout << i;

        // Close the file
        MyReadFile.close();
    }
    cout << "Hola :3" << endl;
    return 0;
}
