#include <iostream>
#include <windows.h>
#include <fstream>
#include <string.h>


using namespace std;




struct arbol
{
    char Palabra[30];
    int freq;
    arbol *izq;
    arbol *der;
};

arbol *ing_arbol(arbol* A,char Palabra1[30]);
void inorden(arbol *A);
void esta(arbol *A, char Palabra1[30]);
void Mayor(arbol *A, int &var);
void Frecuencias(arbol *A, int &var);

arbol* ing_arbol(arbol *A, char Palabra1[30])
{
    if(A==NULL)
    {
        A= new arbol;
        if(!A)
        {
            cout << "NO HAY SUFICIENTE MEMORIA ";
            return A;
        }
        strcpy(A->Palabra,Palabra1);
        A->izq=NULL;
        A->der=NULL;
        A->freq=1;
    }
    else
    {
        if(strcmp(A->Palabra, Palabra1)<0)
        {
            A->der=ing_arbol(A->der,Palabra1);
        }

        else
        {
            if (strcmp(A->Palabra, Palabra1)> 0)
                A->izq=ing_arbol(A->izq,Palabra1);
            else
            {
                if(strcmp(A->Palabra, Palabra1)==0)
                    A->freq++;
            }
        }

    }
    return A;
}



void inorden(arbol *A)
{
    if(A)
    {

        inorden(A->izq);
        cout << A->Palabra<<" ";
        cout << A->freq<<endl;
        inorden(A->der);
    }
}

void Frecuencias(arbol *A, int &var)
{
    if(A)
    {

        Frecuencias(A->izq,var);
        if(var==A->freq){
            cout<< A->Palabra<<endl;
        }
        Frecuencias(A->der,var);
    }
}

void Mayor(arbol *A, int &var)
{

    if(A)
    {

        if(var<A->freq){
            var=A->freq;
        }
        Mayor(A->der,var);
        Mayor (A->izq, var);
    }

}

void esta(arbol *A, char Palabra1[30])
{
    if (!A)
        cout<<" La lista esta vacia "<<endl;
    if(strcmp(A->Palabra,Palabra1)==0)
        A->freq++;
    if(strcmp(A->Palabra,Palabra1)==1)
        esta(A->der,Palabra1);
    else
        esta(A->izq,Palabra1);
}

// programa principal
int main()
{
    ifstream Archivo;
    arbol *a;
    char NombA[20], Palabra1[30];
    int n,x,i=0,var=0;
    a = NULL;

    do
    {
        cout<<" Ingrese el nombre del archivo "<<endl;
        cin>>NombA;
        Archivo.open(NombA);

        if(Archivo.fail())
        {
            cout<<" El nombre del archivo no existe "<<endl;
            i=0;
        }
        else
        {
            while(!Archivo.eof())
            {
                Archivo>>Palabra1;
                a=ing_arbol(a,Palabra1);
            }
            i++;
        }


    }
    while(i!=1);
    cout<<endl;
    cout<< " Las palabras en inorden y su frecuencia son: "<<endl;
    cout<<endl;
    inorden(a);

    Mayor(a,var);
    cout<<endl;
    cout<<" La o las palabras con mayor frecuencia es/son: "<<endl;
    cout<<endl;
    Frecuencias(a,var);
    cout<<"con "<<var <<" de frecuencia en el arbol."<<endl;




    return 0;
}
