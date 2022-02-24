#ifndef RED_H
#define RED_H
#include <string>
#include <vector>

using namespace std;


class Red
{
    char*apunt_archi=NULL;
public:
    int abrir_tabla(char *apunt_archi);   //muestra la tabla inicial
    vector<char> lectura(char *apunt_archi);      //extrae los nombres de los nodos



};

#endif // RED_H
