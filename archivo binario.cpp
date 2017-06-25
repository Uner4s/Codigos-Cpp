/*
*Universidad Santiago de Chile.
*Facultad de Ciencias.
*Departamento de Matemática y Ciencia de la Computación.
*Licenciatura en Ciencia de la Computación.


*Autor: Nicolas Perez Poblete.
*Proposito: Ingresar informacion al programa mediante un archivo binario y trabajar con los datos.
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

struct nodo // estructura nodo.
{
    char nombres[30];
    int horas;
    float rendimiento;
    nodo *sig;
};

struct aux
{
    char nombres[30];
    int horas;
    float rendimiento;

};

class lista
{
private:
    nodo* p;
public:
    lista();
    ~lista();
    void ingresar(aux z); // funcion donde se ingresan los datos.
    void eliminar(char nombre[50]);// funcion para eliminar los nombres de las listas.
    void mostrar();
    void menu();
};


//Funcion principal main.
int main()
{
    ifstream Archivo;
    lista a;
    aux z;
    char nombre[50];//variable tipo caracter.
    nombre[0]=1;//asignacion.
    int op=0;
    int comprobar=1;

    a.menu();
    do
    {
        system("cls");
        a.menu();
        cin>>op;
        if(op==1)
        {
            system("cls");
            Archivo.open("datos.txt", ios::binary | ios::app);

            if (Archivo.fail())
            {
                cout<<" El nombre del archivo no existe "<<endl;
            }
            else
            {
                while(!Archivo.eof())
                {
                    Archivo.read((char *)(&z),sizeof(aux));
                    a.ingresar(z);

                }

            }
            cout<<" Los datos del archivo son: "<<endl;
            a.mostrar();// muestra todos los datos de la listas sin eliminar ninguno aun.
            system("pause");



        }
        if(op==2)
        {
            Archivo.open("datos.txt", ios::binary | ios::app);
            if (Archivo.fail())
            {
                cout<<" El nombre del archivo no existe "<<endl;
            }
            else
            {
                while(!Archivo.eof())
                {
                    Archivo.read((char *)(&z),sizeof(aux));
                    a.ingresar(z);

                }

            }

            system("cls");
            do// ciclo para eliminar los nombres.
            {
                cout<<"¿Que nombre desea eliminar de la lista? (PARA TERMINAR INGRESE UN PUNTO)"<<endl;
                cin>>nombre;
                if (nombre[0]!='.')//mientras el nombre sea distinto de un punto.
                    a.eliminar(nombre);//llama a la funcion eliminar.
            }
            while(nombre[0]!='.');//mientras sea distinto de un punto para salirse del ciclo.

            cout<<" Esta es la lista con los datos ya eliminados "<<endl;
            a.mostrar();// muestra la nueva lista con los datos ya eliminados.
            system("pause");

        }
        if(op==3)
        {
            return 0;
        }
        if(op>3)
        {
            system("cls");
            cout<<endl;
            cout<<"**** INGRESE UN NUMERO ADECUADO AL MENU.**** "<<endl;
            cout<<endl;
            system("pause");
        }


    }
    while(op!=3);



    return 0;

}

void lista::ingresar(aux z) // funcion que ingresa los datos.
{
    nodo *q, *r;
    q = new nodo;
    strcpy(q -> nombres,z.nombres);
    q->horas=z.horas;
    q->rendimiento=z.rendimiento;
    q -> sig = p;    // se supone menor
    if ( !p || strcmp(q -> nombres, p -> nombres )<=0)
        p = q; // Si resulta ser el menor, p cambia a q, es decir nueva cabeza
    else
    {
        r = p -> sig;
        while ( r && strcmp(r -> nombres, q -> nombres )< 0) //
        {
            q -> sig = r;
            r = r -> sig;
        }
        q -> sig -> sig = q; //
        q -> sig = r;
    }
}

void lista::eliminar(char nombre[50]) // funcion que elimina las palabras que escoja el usuario.
{
    nodo *r, *q;

    if ( p == NULL )
        cout<<endl<<"lista vacia "<<endl;
    else
    {
        q = p;   // copia puntero a cabeza de lista
        if(strcmp(p->nombres,nombre)==0)
        {
            p=p->sig;
            delete q ;
        }
        else
        {
            do  //ciclo que deja posicionado al puntero q en el nodo a eliminar
            {
                r=q;
                q=q->sig;
            }
            while (q&&strcmp(q->nombres,nombre)!= 0);
            if(q)
            {
                r->sig=q->sig;
                delete q;
            }
            else
                cout<<endl<<"El nombre "<<nombre<<"  No esta en la Lista"<<endl;
        }
    }
}

void lista::mostrar() // muestra la lista con nombres, edad y altura.
{



    nodo *q;
    q=p;
    while(q)
    {
        cout<<endl;
        cout<<"Nombre:  "  <<q->nombres<<endl;

        cout<<"Horas de estudio:" <<q->horas<<endl;

        cout<<"Rendimiento    " <<q->rendimiento<<endl;
        cout<<endl;
        q = q->sig;
    }
}


lista::lista()
{
    p= NULL; // p nulo
}

lista::~lista()
{
    nodo *q;
    while (p)
    {
        q=p;
        p = p->sig;
        delete q;
    }

}

void lista::menu()
{
    cout<<"           xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"<<endl;
    cout<<"           x*************************************************x"<<endl;
    cout<<"           x*                    Menu                       *x"<<endl;
    cout<<"           x*                                               *x"<<endl;
    cout<<"           x*                                               *x"<<endl;
    cout<<"           x*  1.- Mostrar datos del archivo binario.       *x"<<endl;
    cout<<"           x*  2.- Eliminar datos.                          *x"<<endl;
    cout<<"           x*  3.- Salir del programa                       *x"<<endl;
    cout<<"           x*                                               *x"<<endl;
    cout<<"           x*                                               *x"<<endl;
    cout<<"           x*                                               *x"<<endl;
    cout<<"           x*************************************************x"<<endl;
    cout<<"           xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"<<endl;
}






