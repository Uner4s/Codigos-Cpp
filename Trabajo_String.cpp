/* Universidad de Santiago
 * Facultad de Ciencia
 * Departamento de Matemática y Ciencia de la Computación
 * Licenciatura en Ciencia de la Computación
 *
 * Nombre: Nicolas Perez Poblete.
 * Proposito: Desde un archivo lee palabras. Cuando tengan mas de 4 caracteres compara cuanto se repiten, luego dice cuales son las qu mas se repiten.


 * Fecha: 13 de junio del 2012
 *
 * IDE: Code::Blocks 10.05
 * Compilador: GNU GCC Compiler

*/
#include<iostream>
#include<fstream>
#include<conio.h>
#include<windows.h>
#include<string.h>

using namespace std;

void Comparar ( char nombre1[20] );

// Programa Principal

int main() // funcion principal
{
  int numero, a=0;
  char nombre1[20],nombre2[20],b[20],c[20],nombre;

  ifstream archivo;
  ofstream palabras;
  palabras.open("caracteres4.txt");

  system("cls");

  cout << "Ingrese Nombre de Archivo donde estan las palabras:  ";
  cin>>nombre1;

  archivo.open(nombre1);  // abre el archivo para extraer datos

  if (archivo.fail())     //Chequea que el archivo exista
     {  cout<<"\n\n\n              Archivo no existe, ";
	    system("PAUSE");
     }
  else{


     while(archivo>>b)
    {



        a=strlen(b);//cuenta los caracteres de las palabras.
            if(a>=4){
                palabras<< b <<endl; // guarda las palabras con 4 o mas caracteres.
            }


    }
    Comparar ( nombre1 ); // llama la funcion de comparacion.
    system("PAUSE");
    archivo.close();
    palabras.close();
    return 0;
  }

}


void Comparar ( char nombre1[20] ){ // funcion que muestra la cantidad de veces de repeticion en un archivo de las palabras.
int Compara = 0, Contador = 0, ValorMasGrande = 0,a=0,b=0;


 char Palabra1[20],Palabra2[20],q[20] ;
  ifstream archivo ;
  ifstream palabras ;
  ofstream ArchivoRepite ;
  palabras.open ( "caracteres4.txt" );
  ArchivoRepite.open ( "Repite.txt" );


    while ( !palabras.eof() )    {  // mientras el archivo palabras manda datos.

            archivo.open( nombre1 );
            palabras >> Palabra1;
            while ( !archivo.eof() )   {
                    archivo >> Palabra2;
                    Compara = strcmp( Palabra1 , Palabra2 );
                    if ( Compara == 0 )
                            Contador++;
            }
             archivo.close();
             if (ValorMasGrande < Contador )
                    ValorMasGrande = Contador;
                    a=Contador;
                    if(a>b){
                        b=a;
                        strcpy(q,Palabra1);
                    ArchivoRepite <<  Contador  <<   Palabra1   << endl;

                    }
                    Contador = 0;
    }
            palabras.close();
            ArchivoRepite.close();


   cout<<" La que mas se repite es " << Palabra1 << " con "<< b <<" repeticiones."<<endl;




}
