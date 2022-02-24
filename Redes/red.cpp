#include "red.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

int Red::abrir_tabla(char *apunt_archi)
{



        int n=0;
        char temp='a';



        ifstream p;
        p.open(apunt_archi,ios::in);    //abrir el archivo en modo lectura

        if(p.fail()){
            cout<< "No se pudo abrir el archivo"<<endl;
            exit(1);
        }


        while(p.good()){     //mientras no se llegue al final del archivo
           temp=p.get();
            n+=1;
            cout<<temp;

    }



        p.close();
        n--;

        return n;



}





vector<char> Red::lectura(char *apunt_archi)
{

    ifstream archi;
    char temp;
    vector<char> mult;
    int cont=0;



    archi.open(apunt_archi,ios::in);    //abrir el archivo en modo lectura

    if(archi.fail()){
        cout<< "No se pudo abrir el archivo";
        exit(1);
    }


    while(archi.good()){     //mientras no se llegue al final del archivo

        temp=archi.get();

        if(temp=='\n'){


            archi.close();
            return mult;
        }

        if(temp!='-' and temp!=' '){


            mult.push_back(temp);     //agregra a un arreglo lo que encuentra en en el archivo
            cont++;


        }




    }
    return mult;
    archi.close();
}


