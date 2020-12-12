#include <iostream>
#include <stdexcept>
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
#include <AVLTreeMayor.h>
#include <limits>

using namespace std;

void buscarPrefijo(){

}

int main(){
    setlocale(LC_ALL, "");
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);

    AVLTreeDictionary<int,string> *diccionarioLineasAVL = new AVLTreeDictionary<int,string>();
    AVLTreeDictionary<string, DLinkedList<int>*> *diccionarioPalabrasListas = new AVLTreeDictionary<string, DLinkedList<int>*>();
    Trie *triePalabras = new Trie();
    bool salir = false;
    int opcion1 = 0;
    int opcion2 = 0;

    cout << "Bienvenido!" << endl;
    cout << "Este programa usa la estructura de datos AVL para analizar datos sobre un archivo" << endl;

    // Read from the text file

    string nombreArchivo = "";

    cout << "Ingrese el nombre del archivo que va a utilizar" << endl;
    getline(cin,nombreArchivo);

    ifstream MyReadFile(nombreArchivo + ".txt");
    if(MyReadFile.fail()){
        throw runtime_error("No es posible abrir el archivo");
    }else {
        int numeroLinea = 1;

        string linea;


        while (getline (MyReadFile, linea)) {
            diccionarioLineasAVL->insert(numeroLinea, linea);

            string palabra = "";
            string signos = ", . ; : ¿ ? ! ¡ ( ) [ ] { } - / * $ « »";

            for(unsigned int i = 0; i < linea.size(); i++){

                if(linea[i] != ' '){

                    for(unsigned int j = 0; j < signos.size(); j++){
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
                        DLinkedList<int> *lista = diccionarioPalabrasListas->getValue(palabra);
                        lista->insert(numeroLinea);
                        diccionarioPalabrasListas->setValue(palabra, lista);
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
        while(!salir){
        cout<<"Menu: "<<endl;
        cout<<"1- Consultar prefijo."<<endl;
        cout<<"2- Buscar palabra."<<endl;
        cout<<"3- Buscar por cantidad de letras."<<endl;
        cout<<"4- Palabras mas utilizadas."<<endl;
        cout<<"5- Salir del programa."<<endl;

        while(!(cin>>opcion1) || opcion1< 1){
            cout<<"La opcion ingresada no es valida"<<endl;
            cout<<"Escoja una opcion valida: "<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        }

        if(opcion1 == 1){

            //-------------------------------------------------
        //---------------- Consulta prefijo ---------------

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


        }
        else if(opcion1 == 2){

              //-------------------------------------------------
        //---------------- Buscar palabra ---------------
        cout << "Ingrese la palabra que quiere buscar" << endl;
        string palabra = "";
        cin >> palabra;

        if(triePalabras->containsWord(palabra)){
            DLinkedList<int> *listaLineas = diccionarioPalabrasListas->getValue(palabra);

            cout << "La palabra "<<palabra<< " se encuentra en las siguientes lineas: " << endl;
            for(listaLineas->goToStart(); !listaLineas->atEnd(); listaLineas->next()){
                int lineaNumero = listaLineas->getElement();
                 cout <<"Linea numero "<< lineaNumero<<": ";
                cout << diccionarioLineasAVL->getValue(lineaNumero) <<"\n"<< endl;
            }
        }

        }
        else if(opcion1 == 3){

               //--------------------------------------------------------
        //---------------- Buscar por cantidad de letras ---------
        cout << "Ingrese la cantidad de letras por palabra que quiere buscar" << endl;
        int cantidadLetras = 0;

        while(!(cin>>cantidadLetras) || cantidadLetras< 1){
            cout<<"La cantidad ingresada no es valida"<<endl;
            cout<<"Escoja una cantidad valida: "<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        SortedArrayList<string> *listaOrdenada = new SortedArrayList<string>(10000);

        List<string> *listaKeys = diccionarioPalabrasListas->getKeys();

        for(listaKeys->goToStart(); !listaKeys->atEnd(); listaKeys->next()){
            string palabra = listaKeys->getElement();

            if(palabra.size() == cantidadLetras){
                listaOrdenada->insert(palabra);
            }
        }

        for(listaOrdenada->goToStart(); !listaOrdenada->atEnd(); listaOrdenada->next()){
            string palabra = listaOrdenada->getElement();
            cout << palabra << "\t";
        }
        cout<<endl;


        }
        else if(opcion1 == 4){


        Trie *triePalabrasIgnorar = new Trie();

        ifstream archivoIgnorar("ignorar.txt");
        if(archivoIgnorar.fail()){
            cout << "No se pudo abrir el archivo" << endl;
        } else {
            while (getline (archivoIgnorar, linea)) {
                if(!triePalabrasIgnorar->containsWord(linea)){
                    triePalabrasIgnorar->insert(linea);
                }

            }
        }



        SortedArrayList<KVPair<int,string>* > *listaPalabrasMasUsadas = new SortedArrayList<KVPair<int,string>*>(10000);
        List<string> *listaPalabras = diccionarioPalabrasListas->getKeys();


        for(listaPalabras->goToStart(); !listaPalabras->atEnd(); listaPalabras->next()){
            string palabra = listaPalabras->getElement();

            DLinkedList<int> *temp = diccionarioPalabrasListas->getValue(palabra);

            if(!triePalabrasIgnorar->containsWord(palabra)){
                listaPalabrasMasUsadas->insert(new KVPair<int,string>(temp->getSize(), palabra ) );
            }

        }


        cout<<"1- Ver top."<<endl;
        cout<<"2- Ver palabras menos utilizadas."<<endl;
        cout<<"3- Regresar."<<endl;

        while(!(cin>>opcion2) || opcion2< 1){
            cout<<"La opcion ingresada no es valida"<<endl;
            cout<<"Escoja una opcion valida: "<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }


        if(opcion2 == 1){
        //--------------------------------------------------------
        //---------------- Palabras mas utilizadas ---------------
        cout<<"Ingrese la cantidad de palabras que desea mostrar: "<<endl;
        int cantidadpalabras;


        while(!(cin>>cantidadpalabras) || cantidadpalabras< 1){
            cout<<"La cantidad ingresada no es valida"<<endl;
            cout<<"Escoja una cantidad valida: "<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        listaPalabrasMasUsadas->goToStart();
        for(int i = 0; i < cantidadpalabras; i++){

            KVPair<int,string> *temp = listaPalabrasMasUsadas->getElement();
            cout<<"La palabra "<<temp->getValue()<<" se repite un total de: "<<temp->getKey()<<" veces."<<endl;
            listaPalabrasMasUsadas->next();
        }

        }
        else if(opcion2 == 2){

        //----------------------------------------------------------------------
        //--------------------Palabras menos utilizadas-------------
        cout<<"Ingrese la cantidad de palabras que desea mostrar: "<<endl;
        int cantidadpalabras;

        while(!(cin>>cantidadpalabras) || cantidadpalabras< 1){
            cout<<"La cantidad ingresada no es valida"<<endl;
            cout<<"Escoja una cantidad valida: "<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        listaPalabrasMasUsadas->goToEnd();
        listaPalabrasMasUsadas->previous();
         for(int i = 0; i < cantidadpalabras; i++){

            KVPair<int,string> *temp = listaPalabrasMasUsadas->getElement();
            cout<<"La palabra "<<temp->getValue()<<" se repite un total de: "<<temp->getKey()<<" veces."<<endl;
            listaPalabrasMasUsadas->previous();
        }

        }
        else if(opcion2 == 3){
            continue;
        }
        else{

            cout<<"Opcion no valida."<<endl;

        }
        }

        else if(opcion1 == 5){
            salir = true;
        }
        else{
            cout<<"Digite una opcion valida."<<endl;
        }
        }

        // Close the file
        MyReadFile.close();
    }

    return 0;
}
