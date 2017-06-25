
/* Universidad de Santiago
 * Facultad de Ciencia
 * Departamento de Matemática y Ciencia de la Computación
 * Licenciatura en Ciencia de la Computación
 *
 * Nombre: Nicolas Perez Poblete.
 * Proposito:
 * Fecha:
 *
 * IDE: Code::Blocks 12.05
 * Compilador: GNU GCC Compiler

*/


#include <iostream>
#include <string.h>
#include <windows.h>
#include <fstream>
#include <stdlib.h>
#define MAX 5000
#include <stdlib.h>
#include <cstring>

using namespace std;



int convertir_char_to_int(char caracter)
{
 int auxiliar =0;
 auxiliar = caracter-48;
 return auxiliar;
}  

string itoa(int n)
{
	string rtn;
	for(rtn="";n>0;rtn.insert(rtn.begin(),n%10+'0'),n/=10);
	return rtn;
}

int potencia(int b,int e){
    int i;
    int pot=1;
    for(i=1;i<=e;i++){
          pot=pot*b;
    }
    return pot;
}

int main()
{
    int i, j, limite, numero;
    char A[100];
    
    cout<<"Ingrese el numero de elementos del conjunto"<<endl;
    cin>>limite;
    
    for(i=0;i<limite;i++)
	{
    	if(i == 0)
    	{
    		A[i]= '0';	
    	}
    	else
    	{
			char *B = new char[itoa(i).length() + 1]; 
			std::strcpy(B, itoa(i).c_str());  
        	A[i]= B[0];  		
    	}
		

    }
    for(i=0;i<potencia(2,limite);i++)
	{
        for(j=0;j<limite;j++)
		{
        	if(i & (1<<j))
				cout<<A[j];
				numero = convertir_char_to_int(A[j]);
				cout<<numero;
        }
        cout<<endl;
    }
    system("pause");
    return 0;
 
}
