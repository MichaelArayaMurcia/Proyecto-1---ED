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

    string myText;
    // Read from the text file
    ifstream MyReadFile("ignorar.txt");

    // Use a while loop together with the getline() function to read the file line by line
    while (getline (MyReadFile, myText)) {
        // Output the text from the file
        cout << myText;
    }

    // Close the file
    MyReadFile.close();
    cout << "Hola :3" << endl;
    return 0;
}
