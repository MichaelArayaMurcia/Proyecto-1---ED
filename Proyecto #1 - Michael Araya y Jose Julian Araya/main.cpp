#include <iostream>
#include "Trie.h"
#include <fstream>
#include <Windows.h>
#include <string>
#include <AVLTreeDictionary.h>


using namespace std;

int main()
{
    setlocale(LC_ALL, "spanish");
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);

    AVLTreeDictionary<int,string> *diccionarioLineasAVL = new AVLTreeDictionary<int,string>();
    AVLTreeDictionary<string, DLinkedList<int>> *diccionarioPalabrasListas = new AVLTreeDictionary<string, DLinkedList<int>>();
    Trie *triePalabras = new Trie();

    cout << "Bienvenido!" << endl;
    cout << "Este programa usa la estructura de datos AVL para analizar datos sobre un archivo" << endl;

    // Read from the text file

    string nombreArchivo = "";

    cout << "Ingrese el nombre del archivo que va a utilizar" << endl;
    cin >> nombreArchivo;


    ifstream MyReadFile(nombreArchivo + ".txt");
    if(MyReadFile.fail()){
        cout << "No es posible abrir el archivo" << endl;
    }else {
        int numeroLinea = 1;
        int numeroPalabra = 1;

        string linea;


        while (getline (MyReadFile, linea)) {
            // cada línea del archivo
            //cout << linea << endl;
            diccionarioLineasAVL->insert(numeroLinea, linea);

            string palabra = "";
            string signos = ",.;:¿?!¡()[]{}'""-_/*$";

            for(int i = 0; i < linea.size(); i++){
                if(linea[i] != ' '){
                    char caracter = linea[i];

                    for(int j = 0; j < signos.size(); i++){
                        if(linea[i] == signos[j]){
                            linea[i] = ' ';
                        }
                    }

                    if(caracter != ' '){
                        caracter = tolower(caracter);
                        palabra += caracter;
                    }

                }
                else {
                    triePalabras->insert(palabra);

                    if(!diccionarioPalabrasListas->contains(palabra)){
                        DLinkedList<int> lista;
                        diccionarioPalabrasListas->insert(palabra, lista);
                    }
                    else {
                        List<int> *lista = diccionarioPalabrasListas->getValue(palabra);
                        lista->insert(numeroLinea);
                        diccionarioPalabrasListas->setValue(palabra, lista);
                    }


                    palabra = "";
                }
            }
            numeroLinea += 1;
        }

        cout << numeroLinea;

        // Close the file
        MyReadFile.close();
    }
    cout << "Hola :3" << endl;
    return 0;
}
