#include <iostream>
#include <math.h>

using namespace std;

double fraccion_sucesiva(double entero, double decimal);
int cantidad_decimales=200;
double vector[2];

int main()
{	
	double entero = 0;
	double decimal = 0.111115;
	double resultado;
	resultado = fraccion_sucesiva(entero, decimal);
	
	cout<<vector[0]<<"/"<<vector[1];
	
	return 0;
}

double fraccion_sucesiva(double entero, double decimal){
	
	double division;
	double aux_entero;
	double aux_decimal;
	double denominador;
	

	int condicion=10;
	double auxiliar_principal;
	double contador = 1;

	
	division = 1/decimal;
	aux_entero = floor(division);
	aux_decimal = division - floor(division); 
	
	
	if(cantidad_decimales == 200){
		cantidad_decimales--;
		denominador = fraccion_sucesiva(aux_entero, aux_decimal);
		entero = 1;
		

		aux_decimal = denominador;
		
		while(condicion != 1){
			
			auxiliar_principal = denominador - floor(denominador);
			if(auxiliar_principal < 0.995001 && auxiliar_principal > 0.0050001){
				denominador = denominador + aux_decimal;
				contador ++;
			}
			else{
				condicion = 1;
			}
		}
		
		auxiliar_principal = denominador - floor(denominador);
		entero = contador;
		
		if(auxiliar_principal > 0.92)
			denominador = ceil(denominador);
		else
			denominador = floor(denominador);
			

		
		vector[0] = entero;
		vector[1] = denominador;
		
		return 0;
	}
	
	if(cantidad_decimales != 200 && cantidad_decimales != 0){
		cantidad_decimales--;
		return entero + 1 / fraccion_sucesiva(aux_entero, aux_decimal);
	}	
	else{
		return entero + division;
	}	
}
