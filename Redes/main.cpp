#include <iostream>
#include <string>
#include <map>              //mapas                            //
#include <stdlib.h>        //new and delete                   //
#include <fstream>        //manipulacion de archivos         //
#include <sstream>       //                                 //
#include "red.h"        //clase llamada red                //
#include <vector>      //Vectores                         //
#include <algorithm>  //erase()                          //


using namespace std;


//Funciones//
void datos(int);
void mostrar(int **,int,int,int);
char *text(char n[]);
static void Floyd_Warshall(int **,int);
void agregar_(int tamao);
void eliminar(int);


//variables//
int **puntero_matriz=NULL,filas=0,colum=0;
char* apunt_archi=NULL;
char abrir_archi[250];
int g=0,a=0;
vector<char> vect;
static int inf = 65535;   //representacion de infinito




int main(){
    int opcion=1;
    int tamao=0;


    cout<<"Ingrese 0 terminar la ejecuacion: "<<endl;
    cout<<"Ingrese 1 para abrir un archivo: "<<endl;
    cout<<"Ingrese 2 actualizar la tabla de enrutamiento con las rutas mas directas: "<<endl;
    cout<<"Ingrese 3 para agregar una enrutador "<<endl;
    cout<<"Ingrese 4 para Eliminar una enrutador "<<endl;
    cout<<"Elija una opcion: ";

    while(opcion!=0){

    cin>>opcion;

    //OPCION ABRIR UN ARCHIVO
    if(opcion==1){



    apunt_archi = text(abrir_archi);  //le pide al usuario el nombre del archivo de inicio
    Red ob;
    ob.abrir_tabla(apunt_archi);       //trae la funcion de Red que abre el archivo inical

    cout<<endl;

    vect = ob.lectura(apunt_archi);
    cout<<"Cuanto tiene el vector: "<<vect.size()<<endl;
    tamao=vect.size();



      datos(tamao);
      mostrar(puntero_matriz, filas,colum, tamao);

    }          //fin de opcion 1//

    cout<<endl;

       //Tabla de menor recorrido
       if(opcion==2){

       Floyd_Warshall(puntero_matriz,tamao);
       mostrar(puntero_matriz, filas,colum, tamao);

        } //fin de opcion 2//

    cout<<endl;

        //Agregar una ruta
        if(opcion==3){
      agregar_(tamao);

      char letra;cout<<"Ingrese una letra (MAYUSCULA), para nombrar al enrutador: ";cin>>letra;

      vect.push_back(letra);
      tamao+=1;
      filas+=1;colum+=1;

      mostrar(puntero_matriz, filas,colum, tamao);

      }  //fin de opcion 3//

    //Eliminar una ruta
    if(opcion==4){

        if(tamao==0){
            cout<<"No hay mas rutas para eliminar ";break;
        }

        eliminar(tamao);
        tamao-=1;
        filas-=1;colum-=1;



        mostrar(puntero_matriz, filas,colum, tamao);




    }


    if(opcion==0){

    for(int i=0;i<filas;i++){
        delete[]puntero_matriz[i];
    }
    delete[]puntero_matriz;

    break;
    }
    cout<<"Esperando accion...";




    }







    return 0;
}
//Abrir el archivo
char *text(char abrir_archi[250]){

    cout<<"Ingrese el nombre del archivo de entrada con la extension: ";cin>>abrir_archi;



    return abrir_archi;
}

//Leer lo que hay en el archivo
void datos(int tamao){

    int fil=0,col=0;
    string line;
    filas=tamao;colum=tamao;

    puntero_matriz = new int*[255]; //reservando memoria para las filas
    for(int i=0;i<255;i++){
        puntero_matriz[i]=new int[255]; //reservando memoria para las columnas

    }

    char temp='a';


    ifstream archi(apunt_archi);
        if (!archi.is_open()) {
            cerr << "Could not open the file - '"
                 << apunt_archi << "'" << endl;
                exit(1);
    }


        int pe=0;

    while(getline(archi,line)){

        int com=line.size();


        for(int k=0;k < com; ++k){

                temp=line[k];

                if(temp=='*'){

                    puntero_matriz[fil][col]=inf;
                   // cout<<puntero_matriz[fil][col];

                    col++;


                }


            if(isdigit(temp)){


                    int comoEntero = temp - '0';  //pasando ascii a entero


                    puntero_matriz[fil][col]=comoEntero;
                   // cout<<puntero_matriz[fil][col];

                    col++;




                    }

        }

        if(pe==1){

       // cout<<endl;
        fil++;
        col=0;
        }

       pe=1;

        }




    archi.close();


}
//Imprime la tabla de enrutamiento
void mostrar(int **puntero_matriz,int filas,int colum,int tamao){
    cout<<"\n Tabla de enrutamiento: \n";
    cout<<"  ";
    for(int i=0;i<tamao;i++){
        cout<<vect[i]<<"-";

        }
    cout<<endl;

    for(int i=0;i<filas;i++){
        cout<<vect[i]<<"-";
        for(int j=0;j<colum;j++){
            cout<<puntero_matriz[i][j]<<"-";
        }
        cout<<endl;
    }
}



static void Floyd_Warshall(int **puntero_matriz,int tamao){
    int inicio=0;
    int destino=0;
    int intermedio=0;


    for(intermedio=0;intermedio<tamao;intermedio++)
    {
        for(inicio=0;inicio<tamao;inicio++)
        {
            for(destino=0;destino<tamao;destino++)
            {
                if(puntero_matriz[inicio][destino]>puntero_matriz[inicio][intermedio]+puntero_matriz[intermedio][destino]){

                    puntero_matriz[inicio][destino]=puntero_matriz[inicio][intermedio]+puntero_matriz[intermedio][destino];

                }
            }
        }
    }

}


void agregar_(int tamao){



    for(int i=0;i<tamao;i++){

        int poner=0;
        cout<<"Ingrese un valor para el enrutador creado  con respecto a "<<vect[i]<<". Si no quieres que esten conectados pon 0: ";
        cin>>poner;

        if(poner==0){
            puntero_matriz[tamao][i]=inf;
            puntero_matriz[i][tamao]=inf;
        }

        if(poner!=0){

        puntero_matriz[tamao][i]=poner;
        puntero_matriz[i][tamao]=poner;
        }

    }

    puntero_matriz[tamao][tamao]=0;

}


void eliminar( int tamao){
    cout<<"RUTAS EXISTENTES: [";

    for(int i=0;i<tamao;i++ ){
        cout<<vect[i];
    }
    cout<<"]"<<endl;
    for(int i=0;i<tamao;i++ ){
        cout<<i;
    }
    cout<<endl;
    int num=0;

    cout<<"Digite el numero respectivo a la letra que desea eliminar: ";cin>>num;

    char a=vect[num];

    vect.erase(std::remove(vect.begin(), vect.end(), a), vect.end());



     //Crea una matriz copia
    int matriz[tamao][tamao];

    for(int i=0;i<tamao;i++){
        for(int j=0;j<tamao;j++){

            matriz[i][j]=puntero_matriz[i][j];
            cout<<matriz[i][j]<<endl;

        }

    }
    //Utiliza la matriz copia para cambiar el valor que esta en la siguiente fila y columna

    for(int i=0;i<tamao;i++){
        for(int j=0;j<tamao;j++){

            if(i==num){
                puntero_matriz[i][j]=matriz[i][j+1];
                puntero_matriz[i][j]=matriz[i+1][j];

                puntero_matriz[j][i]=matriz[i][j+1];
                puntero_matriz[j][i]=matriz[i+1][j];

            }
        }
        puntero_matriz[num][num]=0;

        }

      delete[]puntero_matriz[num+1];














}














