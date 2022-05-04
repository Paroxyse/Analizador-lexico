// Analizador léxico.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;


string mayus;
string minun;
string input;
std::vector<std::vector<int>> FT{};

string LeerArchivo(string filetl) {
    ifstream file;
    file.open(filetl, ios::in);

    if (file.fail()) {
        cout << "El archivo no existe" << endl;
        exit(1);
    }

   
    cout << "Archivo identificado" << endl;
    string str;
    char c;

    while (file.get(c)) {
       // cout << c;
        str.push_back(c);
    }
    cout << endl;

    file.close();

    return str;
}
void loadSets() {
   
    mayus = LeerArchivo("Mayus.txt");
    minun = LeerArchivo("Minus.txt");
    input = LeerArchivo("Entrada.txt");
   // cout << mayus <<"\n";
    //cout << minun << "\n";


}
int isLetter(char c) 
{
    for (int i = 0; i < mayus.size(); i++) 
    {
        if (c == mayus.at(i)) 
        {
            return 1;
        }
        if (c == minun.at(i))
        {
            return 2;
        }
       
    }
    return 0;
}
int isSomethingelse(char c) {
    string s=LeerArchivo("symb.txt");
    for (int i = 0; i < s.size(); i++) {
        if (c == s.at(i)) 
        {
            return i + 3;
        }
    }
    return 0;
}
int dataType(char c) 
{
    if (c >= '0' && c <= '9') 
    {
        return 0;
    }
    //remember to bodge in some way for e to work lmao prob check whenever datatype returns 1 or 2 just to be safe idk

    int aux = isLetter(c);
    if (aux >=1 && aux<=2) 
    {
        return aux;
    }
    if (c == '\n' || c == '\t' || c == ' ') 
    {
        return 3;
    }
    aux = isSomethingelse(c);
    if (aux != 0) 
    {
        return aux;
    }

    
}
void cargarFT() 
{
    //Gracias a la maravillosa persona de SO que hizo esto posible
   
    std::ifstream sourceFileStream{ "TablaT.txt" };

    
    if (sourceFileStream) {

        // Define 2D array to hold all data and initialize it with all 0


        // Read the rows and columns from the source file
        std::string line{};
        while (std::getline(sourceFileStream, line)) {

            // Add a new row to our matrix
            FT.push_back(std::vector<int>{});

            // Read all column data
            int c{};
            for (std::istringstream iss(line); iss >> c; FT.back().push_back(c))
                ;
        }
        // Debug output
        for (const auto& row : FT) {
            for (const auto& col : row) std::cout << col << ' ';
            std::cout << '\n';
        }
    }
    else std::cerr << "\nError: Could not open source file\n\n";
}
int main()
{
    loadSets();
    cargarFT();
    
    
}


// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
