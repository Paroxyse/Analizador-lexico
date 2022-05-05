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
string output;
std::vector<std::vector<int>> FT{};
int status = 0;

string LeerArc(string filetl) {
    ifstream file;
    file.open(filetl, ios::in);

    if (file.fail()) {
        cout << "El archivo "<<filetl<<" no existe" << endl;
        return "";
    }

   
   // cout << "Archivo cargado correctamente" << endl;
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
   
    mayus = LeerArc("Mayus.txt");
    minun = LeerArc("Minus.txt");
    input = LeerArc("Entrada.txt");
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
int isSomethingelse(char c, string str) {
    string s=LeerArc(str);//sus
    for (int i = 0; i < s.size(); i++) {
        if (c == s.at(i)) 
        {
            return i+5;
        }
    }
    return -1;
}
int dataType(char c, string s) 
{
    if (c >= '0' && c <= '9') 
    {
        return 0;
    }
    //remember to bodge in some way for e to work lmao prob check whenever datatype returns 1 or 2 just to be safe idk

    int aux = isLetter(c);
    if (aux >=1 && aux<=2) 
    {
        cout << aux;
        return aux;
    }
    if (c == '\n')
    {
        return 3;
    }
    if (c == '\t' || c == ' ') 
    {
        return 4;
    }
   
    aux = isSomethingelse(c,s);
    if (aux != 0) 
    {
        return aux;
    }

    
}
void cargarFT(string s) 
{
    //Gracias a la maravillosa persona de SO que hizo esto posible
    //Esta funcion llena un vector de enteros bidimensional con la información contenida en un archivo
   
    std::ifstream sourceFileStream{ s };

    
    if (sourceFileStream) {

        


        
        std::string line{};
        while (std::getline(sourceFileStream, line)) {

           
            FT.push_back(std::vector<int>{});

           
            int c{};
            for (std::istringstream iss(line); iss >> c; FT.back().push_back(c))
                ;
        }
      
        for (const auto& row : FT) {
            for (const auto& col : row) std::cout << col << ' ';
            std::cout << '\n';
        }
    }
    else std::cerr << "\nError: No se encontró el archivo\n\n";
}
vector<int> cargarVint(string s) 
{
    vector<int> aux{};
    ifstream input(s);
    if (input) 
    {
        int valor;
        while (input >> valor) 
        {
            aux.push_back(valor);
        }
        return aux;
    }
     
    
        cout << "Archivo conteniendo una lista de enteros no encontrado";
     return aux;
}
vector<string> cargarVstring(string s) 
{
    vector<string> aux{};
    ifstream input;
    input.open(s);
    if (input)
    {
        string cadena;
        while (input >> cadena)
        {
            aux.push_back(cadena);
        }
    }
    else
    {
        cout << "Archivo conteniendo una lista de strings no encontrado";
    }
    return aux;
}
int getItemIndex(int code, vector<int> v) 
{
    if (v.size() == 0) 
    {
        return -1;
    }
    for (int i = 0; i < v.size(); i++)
    {
        if (code == v[i]) 
        {
            return i;
        }
    }
    
}
void analizar(string inputString, string charset, string TFunc, string CodeList, string MessageList, bool InputMode) 
{
    //bugfix this shit
    cargarFT(TFunc);
    int state=0;
    int symb;
    int i = 0;
    string inString;
    output = "";
    inString = LeerArc(inputString);
    while (i < inString.size()) 
    {
        cout << "\n";
        if (state < TFunc.size()) 
        {

            symb = dataType(inString.at(i),charset);
            state = FT[state][symb];

            
            cout << i << " "<<symb<<" "<<state<<" "<<inString.at(i);
           
           //Si este es el último caracter o si el siguiente estado desde el actual explota, corta el token aquí y salta a un estado
            //de final1
            if (i == inString.size() - 1) 
            {
                state = FT[state][FT[state].size() - 1];
            }
            else if(FT[state][dataType(inString.at(i+1), charset)]>TFunc.size())
            {
                //cout << "pain" << endl;
                state = FT[state][FT[state].size() - 1];
            }
            
        }
        
        if (state > TFunc.size()) 
        {
            //load code list
            vector<int> cList = cargarVint(CodeList);
            //load message list
            vector<string> mList = cargarVstring(MessageList);
            //Get index on the message list from the code list
            int ItemIndex = getItemIndex(state, cList);
            if (ItemIndex == -1)
            {
                ItemIndex = getItemIndex(600, cList);
            }
            output.append(mList.at(ItemIndex));
            output.append("\n");

            state = 0;
        }
            
        
        
   
        
        i++;
    }
    cout << "\n"<<output;

}
int main()
{
    loadSets();
    analizar("Entrada.txt",
        "symbnum.txt",
        "TablaT0.txt",
        "ListaCodigos0.txt",
        "ListaMensajes0.txt",
        false);
  /*  cargarFT("TablaT0.txt");
    cout << FT[0][2]<<endl;
    cout << FT.size();*/
    
    cout << isLetter('E');
}


// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
