/*
*Universidad Santiago de Chile.
*Facultad de Ciencias.
*Departamento de Matemática y Ciencia de la Computación.
*Licenciatura en Ciencia de la Computación.


*Autor: Nicolas Perez Poblete.
*Proposito: Ver si las llaves de un programa estan bien puestas o si sobran o estan mal puestas.
*Fecha: 5 de septiembre del 2012.
*Ide:Code Blocks 10.05.
*Compilador:GNU GCC Compiler.
*/

//Definicin de librerias.

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;

struct nodo // estructura para meter los datos tipo char.
{
    char info;
    nodo *sig;
};

class Pila // clase pila.
{
private:
    nodo *Top;
public:
    Pila();
    ~Pila();
    void push(char n); // funcion que es para ingresar las llaves abiertas.
    void pop();// funcion para eliminar datos de la pila si se ingresa una llave cerrada.
    bool comprobar(); // comprueba si la cabeza de la pila es nula o no.
};


int main()
{
    ifstream Archivo; // Para abrir un archivo.
    char NombreArchivo[30],n;
    int cont=0;
    Pila a; // se define una variable tipo pila.


    do
    {
        system("cls");
        cout<<" Ingrese el nombbre del Archivo. "<<endl;


        cin>>NombreArchivo;
        Archivo.open(NombreArchivo);

        if (Archivo.fail()) // si el archivo al abrirlo falla, avisa.
        {
            cout<<" El nombre del archivo no existe "<<endl;
            system("pause");
        }
        else
        {
            cont++;
            while(Archivo>>n) // mientras valla leyendo los datos del archivo.
            {

                if (n=='{') // si es una llave abierta.

                    a.push(n); // lo ingresa a la pila.

                if(n=='}') // si es una llave cerrada.
                {
                    if(a.comprobar()==true) // pregunta primero si la cabeza de la lista es nula o no.
                    {
                        cout<<" Llave o llaves de tipo '}' mal puesta "<<endl; // si es asi es porque hay una llave tipo } mal puesta.
                        return 0; // Finaliza el programa.
                    }
                    else
                        a.pop();// si la cabeza de la pila no es nula, elimina uno de sus datos.
                }
            }

            if(a.comprobar()==true) // cuando se salga del ciclo si kedan elementos en la pila, es por que sobran llaves abiertas o faltan llaves cerradas.
                cout<<" Todas las llaves que se encontraron estan correctas."<<endl;
            else
                cout<<" Sobran llaves de tipo'{' o faltan llaves de tipo '}'. "<<endl;
        }



        Archivo.close();

    }
    while(cont!=1);

    return 0; // Finaliza el Hermoso programa.
}

void Pila::push(char n) // en esta funcion solamente ingresa variables iguales a '{'
{
    nodo *q;
    q=new nodo;
    q->info=n;
    q->sig=Top;
    Top=q;
}

void Pila::pop() // Elimina un elemento cuando se ingresa al ciclo un char igual a '}'
{
    nodo *q;
    if(Top)
    {
        q=Top;
        Top=Top->sig;
        delete q;
    }
}

Pila::Pila() //constructor
{
    Top=NULL;
}


Pila::~Pila() // destructor
{
    nodo *q;
    while(Top)
    {
        q=Top;
        Top=Top->sig;
        delete q;
    }
}

bool Pila::comprobar() // comprueba si la cabeza es igual o no a null.
{
    if(Top==NULL)
        return true;
    else
        return false;
}
