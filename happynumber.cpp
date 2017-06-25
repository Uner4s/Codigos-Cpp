/* Universidad de Santiago
 * Facultad de Ciencia
 * Departamento de Matemática y Ciencia de la Computación
 * Licenciatura en Ciencia de la Computación
 *
 * Nombre: Nicolas Perez Poblete.
 * Proposito: el programa muestra el mayor número feliz que se encuentra en el archivo.
 *  SI el numero no tiene digito(s) cero, muestra su inverso
 * Fecha: 30 de Mayo, 2012
 *
 * IDE: Code::Blocks 10.05
 * Compilador: GNU GCC Compiler

*/
#include<iostream>
#include<fstream>
#include<conio.h>
#include<windows.h>

using namespace std;

int es_feliz(int numero); // funcion Numero feliz.
int inverso(int numero); // funcion numero inverso.
int digito(int numero);  // digitos ceros.
// Programa Principal

int main()
{
  int numero, a=0,b=0;
  char nombre[20]; // guarda el nombre del archivo
  ifstream f;    //variable tipo archivo
  system("cls");
  cout << "Ingrese Nombre de Archivo donde estan los datos:  ";
  cin>>nombre;
  f.open(nombre);     // abre el archivo para extraer datos
  if (f.fail())     //Chequea que el archivo exista
     {  cout<<"\n\n\n              Archivo no existe";
	    system("PAUSE");
     }
  else{
     cout<<"Los numeros inversos son "<<endl;
     while(f>>b)
    {

        if(digito(b)){
            cout<<inverso(b)<<endl; // Muestra los inversos.
        }

        if(a<b){
            if ( es_feliz(b)){
            a=b;
           }

        }


    }

    cout<<" El mayor numero feliz es "<<a<<endl; // Su inverso si no tiene ceros entre medio se muestra en la lista de numeros inversos.


       	system("PAUSE");
 }
    f.close();
    return 0;
}


int es_feliz(int numero) // Funcion que determina si es feliz o no.
{
  int aux, sd; // variables

  aux=numero; // auxiliar igual al numero.
  do{
        sd=0;
        while(aux)
        {
            sd=sd+(aux%10)*(aux%10);
            aux=aux/10;
        }
        aux=sd;
  }while (aux>=10);

    if (sd==1) //si es igual a 1 es feliz.
        return 1;
    else
        return 0;// si es Infeliz.

}


int inverso(int numero) // Funcion que determina el inverso del numero.
{
    int  nI=0;

    while(numero!=0){
        nI=nI*10+(numero%10);
        numero=numero/10;

    }

    return nI;
}

int digito (int numero) // Ve si un digito es cero.
{
    int cont=0;

    while(numero!=0){
        if(numero%10==0){
            cont++;
        }
        numero=numero/10;
    }

   if(cont!=0)
    return 0; // retorna 0 si el numero contiene un cero entre sus digitos.
   else
    return 1; // Retorna un 1 si no tiene ceros en sus digitos centrales.

}


