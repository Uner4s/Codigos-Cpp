
//Definicin de librerias.

#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

struct persona // estructura persona.
{
    char nombre [50];
    int mes;
    persona *prox;
};

class lista
{
private:
    persona* p;
public:
    lista();
    ~lista();
    void ingresar(char nombre[50], int mes); // funcion donde se ingresan los datos.
    void eliminar(char nombre[50]);// funcion para eliminar los nombres de las listas.
    void mostrar();
};


//Funcion principal main.
int main()
{
    lista a;
    char nombre[50];//variable tipo caracter.
    nombre[0]=1;//asignacion.
    int mes;// mes de cuando estan de cumpleaños.
    int comprobar=1;

    cout<<"Ingrese nombres y meses. (PARA SALIR INGRESE UN PUNTO)"<<endl; // se pide nombre y meses para ingresarlos a las listas.

    do// ciclo.
    {
        cout<<"Nombre:"<<endl;// pide nombre.
        cin>>nombre;// se lee el nombre ingresado.
        if (nombre[0]!='.')// mientras el nombree sea distinto de un punto.
        {
            cout<<"Mes:"<<endl;// pide el mes de cumpelaños.
            cin>>mes;// se lee el mes.
            a.ingresar(nombre,mes); // funcion que ingresa los datos a una lista.
        }
    }
    while(nombre[0]!='.');


    a.mostrar();// muestra todos los datos de la listas sin eliminar ninguno aun.

    do// ciclo para eliminar los nombres.
    {
        cout<<"¿Que nombre desea eliminar de la lista? (PARA TERMINAR INGRESE UN PUNTO)"<<endl;
        cin>>nombre;
        if (nombre[0]!='.')//mientras el nombre sea distinto de un punto.
            a.eliminar(nombre);//llama a la funcion eliminar.
    }
    while(nombre[0]!='.');//mientras sea distinto de un punto para salirse del ciclo.

    a.mostrar();// muestra la nueva lista con los datos ya eliminados.


    return 0;

}

void lista::ingresar(char nombre[50], int mes) // funcion que ingresa los datos.
{
    persona *q, *r; // q y r variables de direccion de memoria.
    q = new persona; // se crea un nuevo campo.
    strcpy(q->nombre,nombre); // copia el string en

    q -> mes = mes;
    q -> prox = NULL;
    if ( !p)
        p = q;
    else
    {
        r = p;
        while(r->prox)
        {
            r=r->prox;
        }
        r->prox=q;
    }
}

void lista::eliminar(char nombre[50]) // funcion que elimina las palabras que escoja el usuario.
{
    persona *r, *q;
    if ( p == NULL )
        cout<<endl<<"LISTA VACIA"<<endl;
    else
    {
        q = p;
        if ( strcmp(p -> nombre,nombre)== 0 )
        {
            p = p -> prox;
            delete q ;
        }
        else
        {
            do
            {
                r = q;
                q = q -> prox;
            }
            while ( q && strcmp(q->nombre,nombre));
            if ( q )
            {
                r -> prox = q -> prox;
                delete q;
            }
            else
                cout<<endl<<" La persona  "<<nombre
                    <<"  no se encuentra en la lista"<<endl;
        }
    }
}

void lista::mostrar() // muestra la lista con nombres y meses.
{
    persona *q;
    q=p;
    while(q)
    {
        cout<<q->nombre<<"\t"<<q->mes<<"\n";
        q=q->prox;
    }
}


lista::lista()
{
    p= NULL; // p nulo
}
lista::~lista()
{
    persona *q;
    while (p)
    {
        q=p;
        p = p->prox;
        delete q;
    }
}








