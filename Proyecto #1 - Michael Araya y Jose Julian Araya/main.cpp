#include <iostream>
#include "Trie.h"
#include <fstream>
#include <windows.h>
#include <string>
#include <AVLTreeDictionary.h>
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <SortedArrayDictionary.h>

using namespace std;

void buscarPrefijo(){

}

int main()
{
    setlocale(LC_ALL, "");
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);

    AVLTreeDictionary<int,string> *diccionarioLineasAVL = new AVLTreeDictionary<int,string>();
    AVLTreeDictionary<string, DLinkedList<int>*> *diccionarioPalabrasListas = new AVLTreeDictionary<string, DLinkedList<int>*>();
    Trie *triePalabras = new Trie();

    cout << "Bienvenido!" << endl;
    cout << "Este programa usa la estructura de datos AVL para analizar datos sobre un archivo" << endl;

    // Read from the text file

    string nombreArchivo = "";

    cout << "Ingrese el nombre del archivo que va a utilizar" << endl;
    getline(cin,nombreArchivo);

    ifstream MyReadFile(nombreArchivo + ".txt");
    if(MyReadFile.fail()){
        cout << "No es posible abrir el archivo" << endl;
    }else {
        int numeroLinea = 1;
        int numeroPalabra = 1;

        string linea;


        while (getline (MyReadFile, linea)) {
            diccionarioLineasAVL->insert(numeroLinea, linea);

            string palabra = "";
            string signos = ", . ; : ¿ ? ! ¡ ( ) [ ] { } - / * $ ";

            for(int i = 0; i < linea.size(); i++){

                if(linea[i] != ' '){

                    for(int j = 0; j < signos.size(); j++){
                        if(linea[i] == signos[j]){
                            linea[i] = ' ';
                        }
                    }

                    char caracter = linea[i];


                    if(caracter != ' '){
                        caracter = tolower(caracter);
                        palabra += caracter;
                    }

                }

                else {

                    if(!triePalabras->containsWord(palabra)){
                      triePalabras->insert(palabra);
                    }


                    if(!diccionarioPalabrasListas->contains(palabra)){
                        diccionarioPalabrasListas->insert(palabra, new DLinkedList<int>());
                    }

                    else {
                        DLinkedList<int> *lista = diccionarioPalabrasListas->getValue(palabra);
                        lista->insert(numeroLinea);
                        diccionarioPalabrasListas->setValue(palabra, lista);
                    }

                    palabra = "";
                }
            }
            numeroLinea += 1;
        }

        cout << numeroLinea;

        //-------------------------------------------------
        //---------------- Consulta prefijo ---------------
        cout << "Se va a hacer la consulta";

        string prefijo = "";

        cout << "Inserte el prefijo que quiere buscar" << endl;
        cin >> prefijo;

        if(!triePalabras->containsPrefix(prefijo)){
            cout << "No se encuentra el prefijo" << endl;
        } else {
            List<string> *lista = triePalabras->getMatches(prefijo);

            for(lista->goToStart(); !lista->atEnd(); lista->next()){
                string palabra = lista->getElement();

                DLinkedList<int> *lista = diccionarioPalabrasListas->getValue(palabra);
                int veces = lista->getSize();

                cout << "La palabra: " << palabra << " sale: " << veces << endl;


            }
        }

        //-------------------------------------------------
        //---------------- Buscar palabra ---------------
        cout << "Ingrese la palabra que quiere buscar" << endl;
        string palabra = "";
        cin >> palabra;

        if(triePalabras->containsWord(palabra)){
            DLinkedList<int> *listaLineas = diccionarioPalabrasListas->getValue(palabra);

            cout << "Palabra esta en las lineas: " << endl;
            for(listaLineas->goToStart(); !listaLineas->atEnd(); listaLineas->next()){
                int lineaNumero = listaLineas->getElement();
                 cout << lineaNumero << endl;
                cout << diccionarioLineasAVL->getValue(lineaNumero) << endl;
            }
        }

        //--------------------------------------------------------
        //---------------- Buscar por cantidad de letras ---------
        cout << "Ingrese la cantidad de letras por palabra que quiere buscar" << endl;
        int cantidadLetras = 0;
        cin >> cantidadLetras;

        SortedArrayList<string> *listaOrdenada = new SortedArrayList<string>();

        List<string> *listaKeys = diccionarioPalabrasListas->getKeys();

        for(listaKeys->goToStart(); !listaKeys->atEnd(); listaKeys->next()){
            string palabra = listaKeys->getElement();

            if(palabra.size() == cantidadLetras){
                listaOrdenada->insert(palabra);
            }
        }

        for(listaOrdenada->goToStart(); !listaOrdenada->atEnd(); listaOrdenada->next()){
            string palabra = listaOrdenada->getElement();
            cout << palabra << endl;
        }

        //--------------------------------------------------------
        //---------------- Palabras mas utilizadas ---------


        // Close the file
        MyReadFile.close();
    }

    return 0;
}
