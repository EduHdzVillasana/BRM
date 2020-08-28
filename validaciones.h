#include <stdio.h>
#include <string.h>		//strcmp
#include <ctype.h>		//toupper
#include <stdlib.h> 	//atoi


int esEntero(char c[]);
int sonIguales(char *a, char *b);


int esEntero(char c[]){		//Funcion que evalua si una cadena de caracteres es un numero entero, de ser asi devuelve 1, en caso contrario devuelve 0
	int num;
	num = (long int)atol(c);
	if (num != 0)
		return num;
	else 
		return -1;	
}
int esReal(char c[])
{
	float num;
	num = (float)atof(c);
	if (num != 0)
		return num;
	else 
		return -1;	
}
int sonIguales(char a[], char b[]){		//Funcion que evalua si dos cadenas de caracteres son iguales, de ser asi devuelve 1, en caso contrario devuelve 0
	int i;
	char c[40];
	strcpy(c,a);
	for (i = 0; c[i] != '\0'; i++){
		c[i] = toupper(c[i]);
	}
	for (i = 0; b[i] != '\0'; i++){
		b[i] = toupper(b[i]);
	}
	if (strcmp(c, b) == 0)
		return 1;
	else 
		return 0;
}

