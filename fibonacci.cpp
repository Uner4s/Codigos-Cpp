/*
	Nicolas Pérez Poblete.


*/

#include <cstdio>
#include <iostream>
#include <vector>
#include <sys/time.h>
#include <stdlib.h>

using namespace std;

struct timespec tiempo1, tiempo2, latencia;

int contador_1 = 0;
int contador_2 = 0;


void diff_time( timespec *t_fin, timespec *t_ini, timespec *delta )
{
    if( ( (*t_fin).tv_nsec - (*t_ini).tv_nsec ) < 0 )
    {
        if( (*t_fin).tv_sec == (*t_ini).tv_sec )
        {
            (*delta).tv_sec  = 0;
            (*delta).tv_nsec = 1000000000 + (*t_fin).tv_nsec - (*t_ini).tv_nsec;
        }
        else
        {
            (*delta).tv_sec  = (*t_fin).tv_sec - (*t_ini).tv_sec - 1;
            (*delta).tv_nsec = 1000000000 + (*t_fin).tv_nsec - (*t_ini).tv_nsec;
        }
    }
    else
    {
        if( (*t_fin).tv_sec == (*t_ini).tv_sec )
        {
            (*delta).tv_sec  = 0;
            (*delta).tv_nsec = (*t_fin).tv_nsec - (*t_ini).tv_nsec;
        }
        else
        {
            (*delta).tv_sec  = (*t_fin).tv_sec - (*t_ini).tv_sec;
            (*delta).tv_nsec = (*t_fin).tv_nsec - (*t_ini).tv_nsec;
        }
    }
}

int fibonacci_iterativo(int n)
{
	contador_1=0;
	int a = 1;
	int b = 0;
	int t = 0;

	long int tiempoComputo;

	for(int i = 0; i<=n; i++)
	{
		contador_1++;
		t = a + b;
		a = b;
		b = t;
	}
	return b;
}

int fibonacci_recursivo(int n)
{

	if(n < 2){
		contador_2++;
		return 1;
	}
	else{
		contador_2++;
		return fibonacci_recursivo(n - 2) + fibonacci_recursivo(n - 1);
	}
}

int main(int argc, char *argv[])
{
	int n;
	n = atoi(argv[1]);
	int Resultado_1;
	int Resultado_2;

	long int tiempoComputo;

	cout<<endl;
	cout<<endl;
	cout<<"FIBONACCI ITERATIVO: "<<endl;
	cout<<endl;
	for(int i = 1;i<=n;i++){
		clock_gettime(CLOCK_MONOTONIC, &tiempo1);
		Resultado_1 = fibonacci_iterativo(i);
		clock_gettime(CLOCK_MONOTONIC, &tiempo2);
		diff_time(&tiempo2, &tiempo1, &latencia);
		
	    tiempoComputo = latencia.tv_sec*1000000000 + latencia.tv_nsec;
	    cout<<"Tiempo con n igual: "<<i<<endl;
		cout << "Tiempo en nanosegundos:" << tiempoComputo << endl;
		cout << "Tiempo en milisegundos:" << tiempoComputo/1000000 << endl;
		cout << "Tiempo en segundos:" << (float)tiempoComputo/1000000000.0 << endl;
		cout<<endl;
	}
	cout<<"Conteo de operaciones: "<<contador_1;

	cout<<endl;
	cout<<endl;
	cout<<endl;

	cout<<"FIBONACCI RECURSIVO: "<<endl;
	cout<<endl;
	contador_2=0;
	for(int i = 1; i<=n; i++){	
    	clock_gettime(CLOCK_MONOTONIC, &tiempo1);
		Resultado_2 = fibonacci_recursivo(i);
		clock_gettime(CLOCK_MONOTONIC, &tiempo2);

		diff_time(&tiempo2, &tiempo1, &latencia);
	
    	tiempoComputo = latencia.tv_sec*1000000000 + latencia.tv_nsec;
    	cout<<"Tiempo con n igual: "<<i<<endl;
		cout << "Tiempo en nanosegundos:" << tiempoComputo << endl;
		cout << "Tiempo en milisegundos:" << tiempoComputo/1000000 << endl;
		cout << "Tiempo en segundos:" << (float)tiempoComputo/1000000000.0 << endl;
		cout<<endl;
	}

	cout<<"Conteo de operaciones: "<<contador_2;

	return 0;
}

