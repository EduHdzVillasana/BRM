/*
	*********************P.I.A. EQUIPO 9***********************
	Materia: ESTRUCTURA DE DATOS 
	Grupo: 6
	Equipo: 9
	Integrantes del equpo:
		.- Brayan Adrian Montoya Morales 1847284
		.- Alberto Carlos Almaguer Rodriguez 1877448
		.- Eduardo Alán Hernández Villasana 1941416
		.- Ian Mauricio Saucedo Aleman 1868954
		.- Susana Enriquez Godina 1841762
*/
#include <stdio.h>
#include <conio.h>
#include <limits.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h> // Se usa para poder implementar booleanos
#include <windows.h> // Se usa para funcion setColor y gotoxy
#include "validaciones.h" // Libreria hecha para validaciones
#define AZUL 1 // Constantes de colores, se usan en la funcion setColor
#define ROJO 4
#define AMBAR 6
#define VERDE 10
#define BLANCO 15
struct municipios // Estructura que almacena los datos de los municipios
{
	char nombre[40];
	char estado[40];
};
typedef struct municipios MUN;
int G[1000][1000]; // Grafo que se manejará
int D=0; // Dimencion del grafo, Se manejo como variable global para poder modificar su tamaño
MUN M[1000]; // Arreglo de estructuras que almacena la informacion de todos los municipios
char nombreC[40]; // Nombre de la compañia, se mostrara en la cabecera de la pantalla
int gastos_fijos; // Factor para deducir el costo de los boletos
float rendimiento; // Rendimiento del autobus km/L
float precio_diesel; // Precio del litro de diesel en pesos mexicanos
int transbordos; // Variable usada para deducir el precio de los boletos
void inicializarDatos (); // Funcion que inicializa en ceros la matriz y el arreglo de estructuras
void imprimirArreglo (); // Funcion que no esta implementada en la funcion final
						 // Imprime los datos de todos los municipios
						 // Le servirá al programador que le de mantenimiento a la aplicacion
void imprimirRed(); // Funcion que no esta implementada en la funcion final
					// Imprime la matriz de adyasencia
					// Le servirá al programador que le de mantenimiento a la aplicacion
void imprimirSalidas(int i);// Funcion que imprime todos las rutas de todos los municipios
void cargarRed(char *); // Funcion que busca el archivo y lo carga a los datos del programa
void cargarD(char *); // Funcion que obtiene el numero de municipios, sirve para verificar que el archivo es valido
void crearRed(); // Funcion para crear una nueva red y guardarla
void exportarRed(char *, int); // Funcion que sirve para guardar o actualizar un archivo
void editor(char *); // Funcion que abre un menu editor de la red
void encontrarCamino (int ,int ); // Funcion que inmplementa el algoritmo de Dijskra para encontrar el camino mas corto
int minDistance(int dist[], bool sptSet[]); // Funcion complementara de encontrarCamino
void printPath(int parent[], int j); // Funcion complementaria de encontrarCamino
int printSolution(int dist[], int n, int parent[], int src, int dest); // Funcion complementaria de encontrarCamino
int menu(); // Imprime el menu y valida la opcion ingresada
int obtenerPosicion (char *, char *); // Busca un municipio por su nombre y estado
void gotoxy(int x,int y); // Mueve el cursor a una posicion indicada
void setColor(int ForgC); // Cambia el color de las letras del programa
int lenght(char a[]); // Indica la longitud de un arreglo de caracteres
void titulo(); // Imprime la cabecera del programa
int main ()
{
	system("MODE CON COLS=102"); // Especifica el tamaño de la pantalla
	setlocale(LC_ALL, ""); // Habilita el uso de la 'ñ' y de la tilde
	int op,src,dest,mun,i,j; // Variables de control
	char municipio1[40]; // Arreglos de caracteres que se leeran del teclao
	char municipio2[40];
	char estado1[40];
	char estado2[40];
	char opcion[40];
	char archivo[40];
	do
	{
		for (i=0; i<40; i++)
		{
			municipio1[i] = '\0';
			municipio2[i] = '\0';
			estado1[i]='\0';
			estado2[i]='\0';
			opcion[i]='\0';
		}
		system("cls");
		fflush(stdin);
		op=menu();
		fflush(stdin);
		switch(op)
		{
			case 1:
				system("cls");
				titulo();
				gotoxy(25,2); printf("Ingresa el nombre del archivo (sin la extencion)");
				gotoxy(25,3);gets(archivo); // Lee el nombre del archivo
				strcat(archivo,".grf");
				cargarD(archivo); // Carga la cantidad de municipios
				if (D <= 0) // Si la cantidad es 0 o menos, archivo invalio o no encontrado
				{
					setColor(ROJO);
					gotoxy(25,4); printf("*Archivo no encontrado o invalido");
					setColor(VERDE);
					gotoxy(25,5); printf("Presione enter para continuar...");
					setColor(VERDE);
					gotoxy(25,6); getch();
				}
				else
				{
					cargarRed(archivo); // Si si es valido y existe, lo carga y muestra la informacion
					system("cls");
					titulo();
					gotoxy(25,2); printf("Nombre de compania: %s",nombreC);
					gotoxy(25,3); printf("Gastos fijos: $%d",gastos_fijos);
					gotoxy(25,4); printf("Precio diesel: $%.2f",gastos_fijos);
					gotoxy(25,5); printf("Rendimiento: %.2f km/l\n", rendimiento);
					for (i=0; i<D; i++)
					{
						imprimirSalidas(i);
					}
					printf("\n                         Precione enter para continuar...\n                         ");
					// Se usaron 25 espacios para que todo este alineado
					getch();
				}
				break;
			case 2:
				crearRed();
				system("cls");
				titulo();
				if(D != 0) // Verifica que los datos ingresados son validos
				{
					gotoxy(25,2); printf("Ingrese el nombre del archivo (sin la extencion)");
					gotoxy(25,3); gets(archivo); // Lee como se llamara el archivo
					strcat(archivo,".grf");
					exportarRed(archivo,-1);
				}
				else
				{
					setColor(ROJO);
					gotoxy(25,2); printf("*Datos incorrectos");
					setColor(VERDE);
					gotoxy(25,3); printf("Precione enter para continuar...");
					gotoxy(25,4); getch();
				}
				break;				
			case 3:
				if (D != 0) // Verifica que previamente ya se haya cargado o creado una red
				{
					editor(archivo); // Manda llamar a la funcion editor
				}
				else 
				{
					titulo();
					setColor(ROJO);
					gotoxy(25,2); printf("Red no ha sido cargada");
					setColor(VERDE);
					gotoxy(25,3);printf("Precione enter para continuar...");
					gotoxy(25,4);getch();
				}
				break;
			case 4:
				if (D != 0)
				{
					do // Pide los datos del municipio de origen
					{// VALIDADO
						titulo();
						gotoxy(25,2); printf("Ingrese el nombre del municipio de origen");
						fflush(stdin);
						gotoxy(25,3); gets(municipio1);
						fflush(stdin);
						gotoxy(25,4); printf("Ingrese el estado del municipio de origen");
						fflush(stdin);
						gotoxy(25,5); gets(estado1);
						fflush(stdin);						
						src = obtenerPosicion(municipio1, estado1);
						if (src == -1)
						{
							setColor(ROJO);
							gotoxy(25,7); printf("No se encontro el municipio");
							setColor(VERDE);
							gotoxy(25,8); printf("Precione enter para continuar...");
							gotoxy(25,9); getch();
						}
						system("cls");
					}while (src<0 || src>=D);
					do // Pide los datos del municipio destino
					{// VALIDADO
						system("cls");
						titulo();
						gotoxy(25,2); printf("Ingrese el nombre del municipio destino");
						fflush(stdin);
						gotoxy(25,3); gets(municipio2);
						fflush(stdin);
						gotoxy(25,4); printf("Ingrese el estado del municipio destino");
						fflush(stdin);
						gotoxy(25,5); gets(estado2);
						fflush(stdin);						
						dest = obtenerPosicion(municipio2,estado2);
						if (dest == -1)
						{
							setColor(ROJO);
							gotoxy(25,7); printf("*No se encontro el municipio");
							setColor(VERDE);
							gotoxy(25,8); printf("Precione enter para continuar...");
							gotoxy(25,9); getch();
						}
						if (dest == src) // Verifica que el destino no sea el origen
						{
							setColor(ROJO);
							gotoxy(25,7); printf("*El destino no puede ser igual al origen");
							setColor(VERDE);
							gotoxy(25,8); printf("Precione enter para continuar...");
							gotoxy(25,9); getch();
						}
						system("cls");
					}while (dest<0 || dest>=D || dest==src);
					encontrarCamino(src,dest); // Manda llamar la funcion que implementa el algoritmo de Dijskra
					printf("\n                         Precione enter para continuar...\n                         ");
					getch();
				}
				else
				{
					titulo();
					setColor(ROJO);
					gotoxy(25,2); printf("Red no ha sido cargada");
					setColor(VERDE);
					gotoxy(25,3);printf("Precione enter para continuar...");
					gotoxy(25,4);getch();
				}
				break;
			case 5:
				do // Pide los datos del municipio a buscar y verifica que exista
				{ // VALIDADO
					titulo();
					fflush(stdin);
					gotoxy(25,2); printf("Ingrese el nombre del municipio que desea buscar");
					gotoxy(25,3); gets(municipio1);
					fflush(stdin);
					gotoxy(25,4); printf("Ingrese el estado del municipio que desea buscar");
					gotoxy(25,5); gets(estado1);
					mun = obtenerPosicion(municipio1, estado1);
					if (mun == -1)
					{
						setColor(ROJO);
						gotoxy(25,7); printf("No se encontro el municipio");
						setColor(VERDE);
						gotoxy(25,8); printf("Precione enter para continuar...");
						gotoxy(25,9); getch();
					}
				}while (mun<0 || mun>=D);
				system("cls");
				titulo();
				// Muestra la informacion
				imprimirSalidas(mun);
				printf("\n                         Precione enter para continuar...\n                         ");
				getch();
				break;
			case 6:
				fflush(stdin);
				titulo();
				for (i=0; i<D; i++) // Manda llamar la informacion de todos los municipios
				{
					imprimirSalidas(i);
				}
				printf("\n                         Precione enter para continuar...\n                         ");
				getch();
				break;					
		}
	}while (op != 7);
	system("cls");
	titulo();
	gotoxy(25,2); printf("Saliendo del programa...");
	gotoxy(25,3); printf("Ingrese una tecla para continuar");
	gotoxy (25,4); getch();
}
void titulo ()
{
	int i,j; // Variables de control
	setColor (AMBAR);// Cambia de color
	for (i=0; i<37; i++)
		printf("*");
	printf(" BUSCADOR DE LA RUTA MINIMA ");
	for (i=0; i<37; i++)
		printf("*");
	if (D != 0)
	{
		printf("\n");
		j=(102-lenght(nombreC))/2;
		for(i=0;i<j;i++)
			printf("*");
		printf(" %s ",nombreC);
		for(i=0;i<j-1;i++)
			printf("*");
	}
	setColor(VERDE);
}
int lenght (char a[])
{
	int i=0; // Variable de control
	while (a[i] != '\0')
	{
		i++; // Cuenta los caracteres antes del '\0'
	}
	return i;
}
int obtenerPosicion (char *mun, char *est)
{
	int pos = -1;
	int i;
	char nombre[40];
	for (i=0; i<D; i++) // Busca en el arreglo de estructuras el municipio con los datos recibidos, regresa la posicion
	{
		if (sonIguales(M[i].nombre,mun) == 1 && sonIguales(M[i].estado,est) == 1)
		{
			pos = i;
			i = D;
		}
	}
	return pos;
}
void imprimirSalidas(int i)
{
	int j;// Variable de control
	printf("                         Salidas de %s, %s a:\n",M[i].nombre,M[i].estado);
	for(j=0; j<D; j++)
	{
		if (G[i][j] != 0)
		{
			printf("                         %s,%s a %dKm\n",M[j].nombre, M[j].estado, G[i][j]); // Imprime la informacion y la distancia
		}
	}
	printf("\n");
}
int menu()
{
	int op=0;// Variables de control
	char opcion[40];
	system("cls");
	do
	{
		titulo(); // Imprime la cabecera
		gotoxy(25,2); printf("\n");
		gotoxy(25,3); printf("Ingrese la opcion:");
		gotoxy(25,4); printf("1.- Cargar archivo");
		gotoxy(25,5); printf("2.- Crear red");
		gotoxy(25,6); printf("3.- Editar red");
		gotoxy(25,7); printf("4.- Encontrar camino");
		gotoxy(25,8); printf("5.- Busqueda de municipio");
		gotoxy(25,9); printf("6.- Imprimir salidas de todos los municipios");
		gotoxy(25,10); printf("7.- Salir");
		gotoxy(25,12); printf(":");
		gets(opcion);
		op = esEntero(opcion);
		if (op<1 || op>7)// VALIDADO
		{
			setColor(ROJO);
			gotoxy(25,14); printf("*Opcion ingresada no valida");
			setColor(VERDE);
			gotoxy(25,15); printf("Precione enter para continuar");
			gotoxy(25,16); getch();
		}
		system("cls");
	}while (op<1 || op>7);
	return op;
}
void editor (char *archivo)
{
	int op,j,aux,i; // Variables de control
	int mun;
	char opcion[40];
	char municipio[40];
	char estado[40];
	for (i=0; i<40; i++)
	{
		opcion[i]='\0';
		municipio[i]='\0';
		estado[i]='\0';
	}
	do
	{
		do// VALIDADO
		{
			system("cls");
			titulo();
			gotoxy(25,2); printf("Ingrese una opcion:");
			gotoxy(25,3); printf("1.- Editar nombre y estado");
			gotoxy(25,4); printf("2.- Editar rutas");
			gotoxy(25,5); printf("3.- Agregar municipio");
			gotoxy(25,6); printf("4.- Eliminar municipio");
			gotoxy(25,7); printf("5.- Editar datos de la compañia");
			gotoxy(25,8); printf("6.- Salir");
			gotoxy(25,9); gets(opcion);
			op = esEntero(opcion);
			if (op<1 || op>6)
			{
				setColor(ROJO);
				gotoxy(25,11); printf("*Opcion ingresada no valida");
				setColor(VERDE);
				gotoxy(25,12); printf("Precione enter para continuar");
				gotoxy(25,13); getch();
			}
		}while (op<1 || op>6);
		switch (op)
		{
			case 1:
				do// Valida qe exista el municipio
				{
					system("cls");
					titulo();
					gotoxy(25,2); printf ("Ingresa el nombre del municipio:"); 
					fflush(stdin);
					gotoxy(25,3); gets(municipio);
					fflush(stdin);
					gotoxy(25,4); printf ("Ingresa el estado del municipio:"); 
					fflush(stdin);
					gotoxy(25,5); gets(estado);
					mun = obtenerPosicion(municipio,estado);
					
					if (mun == -1)
					{
						setColor(ROJO);
						gotoxy(25,7); printf("No se encontro el municipio");
						setColor(VERDE);
						gotoxy(25,8); printf("Precione enter para continuar...");
						gotoxy(25,9); getch();
					}
				}while (mun<0 && mun>=D);
				strcpy(M[mun].nombre,"\0");
				strcpy(M[mun].estado,"\0");
				fflush(stdin);
				system("cls");
				titulo();
				gotoxy(25,2); printf("Ingrese el nuevo nombre de %s:",M[mun].nombre);
				gotoxy(25,3); gets(M[mun].nombre);
				fflush(stdin);
				gotoxy(25,4); printf("Ingrese el estado de %s",M[mun].nombre);
				gotoxy(25,5); gets(M[mun].estado);
				fflush(stdin);
				exportarRed (archivo, -2);
				cargarD(archivo);
				cargarRed(archivo);
				break;
			case 2:
				do// VALIDADO
				{				// Valida que exista el municipio
					system("cls");
					titulo();
					gotoxy(25,2); printf ("Ingresa el nombre del municipio:"); 
					fflush(stdin);
					gotoxy(25,3); gets(municipio);
					fflush(stdin);
					gotoxy(25,4); printf ("Ingresa el estado del municipio:"); 
					fflush(stdin);
					gotoxy(25,5); gets(estado);
					mun = obtenerPosicion(municipio,estado);
					
					if (mun == -1)
					{
						setColor(ROJO);
						gotoxy(25,7); printf("No se encontro el municipio");
						setColor(VERDE);
						gotoxy(25,8); printf("Precione enter para continuar...");
						gotoxy(25,9); getch();
					}
				}while (mun<0 && mun>=D);
				for (j=0; j<D; j++)
				{
					G[mun][j] = 0;
					G[j][mun] = 0;
				}
				system("cls");
				for (j=(mun+1); j<D; j++)
				{
					do// VALIDADO
					{			// Pregunta si hay una conexion, si la hay, pide la distancia en KM
						system("cls");
						titulo();
						gotoxy(25,2); printf("Ingrese (1) si existe una ruta de %s, %s a %s, %s o viceversa. Ingrese (2) de lo contrario",M[mun].nombre,M[mun].estado,M[j].nombre,M[j].estado);
						gotoxy(25,3); gets(opcion);
						aux = esEntero(opcion);
						if (aux != 1 && aux != 2)
						{
							setColor(ROJO);
							gotoxy(25,5); printf("*Opcion ingresada no valida");
							setColor(VERDE);
							gotoxy(25,6); printf("Precione enter para continuar");
							gotoxy(25,7); getch();
						}
					}while (aux != 1 && aux != 2);
					if (aux == 1)
					{
						do// VALIDADO
						{
							system("cls");
							titulo();
							i = mun;
							gotoxy(25,2); printf("Ingrese distancia entre %s, %s y %s, %s",M[i].nombre,M[i].estado,M[j].nombre,M[j].estado);
							gotoxy(25,3); gets(opcion);
							G[i][j] = esEntero(opcion);
							G[j][i] = G[i][j];
							if (G[i][j] <=0)
							{
								setColor(ROJO);
								gotoxy(25,5); printf("*Distancia ingresada no valida");
								setColor(VERDE);
								gotoxy(25,6); printf("Precione enter para continuar");
								gotoxy(25,7); getch();
							}
						}while (G[mun][j] <=0);
					}
					else
					{
						G[mun][j] = 0;
						G[j][mun] = 0;
					}
				}
				exportarRed (archivo, -2);
				cargarD(archivo);
				cargarRed(archivo);
				break;
			case 3:
				mun=D;
				D++;
				strcpy(M[mun].nombre,"\0");
				strcpy(M[mun].estado,"\0");
				do// VALIDADO
				{			// Valida que no haya municioios repetidos
					system("cls");
					titulo();
					gotoxy(25,2); printf ("Ingresa el nombre del municipio:"); 
					fflush(stdin);
					gotoxy(25,3); gets(municipio);
					fflush(stdin);
					gotoxy(25,4); printf ("Ingresa el estado del municipio:"); 
					fflush(stdin);
					gotoxy(25,5); gets(estado);
					mun = obtenerPosicion(municipio,estado);
					
					if (mun != -1)
					{
						setColor(ROJO);
						gotoxy(25,7); printf("*Este municipio ya se ingreso");
						setColor(VERDE);
						gotoxy(25,8); printf("Precione enter para continuar...");
						gotoxy(25,9); getch();
					}
				}while (mun != -1);
				for (j=0; j<D; j++)
				{
					G[mun][j] = 0;
					G[j][mun] = 0;
				}
				for (j=0; j<D; j++)
				{
					if(j != mun)
					{
						do// VALIDADO
						{	// Pregunta si hay una conexion
							system("cls");
							titulo();
							gotoxy(25,2); printf("Ingrese (1) si existe una ruta de %s, %s a %s, %s o viceversa. Ingrese (2) de lo contrario",M[mun].nombre,M[mun].estado,M[j].nombre,M[j].estado);
							gotoxy(25,3); gets(opcion);
							aux = esEntero(opcion);
							if (aux != 1 && aux != 2)
							{
								setColor(ROJO);
								gotoxy(25,5); printf("*Opcion ingresada no valida");
								setColor(VERDE);
								gotoxy(25,6); printf("Precione enter para continuar");
								gotoxy(25,7); getch();
							}
						}while (aux != 1 && aux != 2);
						if (aux == 1 && j != mun)
						{
							do// VALIDADO
							{
								system("cls");
								titulo();
								i = mun;
								gotoxy(25,2); printf("Ingrese distancia entre %s, %s y %s, %s",M[i].nombre,M[i].estado,M[j].nombre,M[j].estado);
								gotoxy(25,3); gets(opcion);
								G[i][j] = esEntero(opcion);
								G[j][i] = G[i][j];
								if (G[i][j] <=0)
								{
									setColor(ROJO);
									gotoxy(25,5); printf("*Distancia ingresada no valida");
									setColor(VERDE);
									gotoxy(25,6); printf("Precione enter para continuar");
									gotoxy(25,7); getch();
								}
							}while (G[mun][j] <=0);
						}
						else
						{
							G[mun][j] = 0;
							G[j][mun] = 0;
						}
					}
				}
				exportarRed (archivo, -2);
				cargarD(archivo);
				cargarRed(archivo);
				break;
			case 4:
				do// VALIDADO
				{ // Valida que exista el municipio
					system("cls");
					titulo();
					gotoxy(25,2); printf ("Ingresa el nombre del municipio:"); 
					fflush(stdin);
					gotoxy(25,3); gets(municipio);
					fflush(stdin);
					gotoxy(25,4); printf ("Ingresa el estado del municipio:"); 
					fflush(stdin);
					gotoxy(25,5); gets(estado);
					mun = obtenerPosicion(municipio,estado);
					
					if (mun == -1)
					{
						setColor(ROJO);
						gotoxy(25,7); printf("No se encontro el municipio");
						setColor(VERDE);
						gotoxy(25,8); printf("Precione enter para continuar...");
						gotoxy(25,9); getch();
					}
				}while (mun<0 && mun>=D);
				exportarRed (archivo, mun);
				cargarD(archivo);
				cargarRed(archivo);
				break;
			case 5:
				system("cls");
				titulo();
				gotoxy(25,2); printf("Introdusca el nombre de la compañía");
				gotoxy(25,3); gets (nombreC);
				do
				{ // Pide los datos de la compañia y los factores del precio
					system("cls");
					titulo();
					gotoxy(25,2); printf("Introdusca los gastos fijos\n");
					gotoxy(25,3); gets(opcion);
					gastos_fijos = esEntero(opcion);
					if (gastos_fijos == -1)
					{
						setColor(ROJO);
						gotoxy(25,5); printf("*Dato ingresado invalido");
						setColor(VERDE);
						gotoxy(25,6); printf("Precione enter para continuar");
						gotoxy(25,7); getch();
					}
				}while (gastos_fijos == -1);
				do
				{
					system ("cls");
					titulo();
					gotoxy(25,2); printf("Introdusca el precio del diesel por litro");
					gotoxy(25,3); gets(opcion);
					precio_diesel = esReal(opcion);
					if (precio_diesel == -1)
					{
						setColor(ROJO);
						gotoxy(25,5); printf("*Dato ingresado invalido");
						setColor(VERDE);
						gotoxy(25,6); printf("Precione enter para continuar");
						gotoxy(25,7); getch();
					}
				}while (precio_diesel == -1);
				do
				{
					system ("cls");
					titulo();
					gotoxy(25,2); printf("Introdusca el precio el rendimiento de los autobuses en km/L\n");
					gotoxy(25,3); gets(opcion);
					rendimiento = esReal(opcion);
					if (rendimiento == -1)
					{
						setColor(ROJO);
						gotoxy(25,5); printf("*Dato ingresado invalido");
						setColor(VERDE);
						gotoxy(25,6); printf("Precione enter para continuar");
						gotoxy(25,7); getch();
					}
				}while (rendimiento == -1);
				exportarRed (archivo, -2);
				break;
		}
	}	while (op>=1 && op<=5);
}
void exportarRed (char *nombre, int modo)
{
	if (modo == -2 || modo>=0)
	{
		int f = remove(nombre); // Verifica el modo, si es actualizar o es guardar por primera vez
								// Si es actualizar o eliminar un municipio, elimina el archivo
	}
	int i,j,bai=0,baj=0;
	FILE *arc = fopen(nombre,"a");
	if (modo>=0) // Dependiendo del modo escribe D o D-1
	{
		fprintf (arc,"%d,%s,%d,%f,%f,\n",D-1,nombreC,gastos_fijos,precio_diesel,rendimiento);
	}
	else
	{
		fprintf (arc,"%d,%s,%d,%f,%f,\n",D,nombreC,gastos_fijos,precio_diesel,rendimiento);
	}
	for (i=0; i<D; i++) // Escribe los datos del municipio
	{
		if (i != modo)
		{
			fprintf(arc,"%s,%s,\n",M[i].nombre,M[i].estado);
		}
	}
	for (i=0; i<D; i++)
	{
		if (i>modo&&modo>=0)
		{
			bai = 1;
		}
		if (i != modo)
		{
			for (j=(i+1); j<D; j++) // Escribe las aristas
			{
				if (j>modo&&modo>=0)
				{
					baj = 1;
				}
				if(G[i][j] != 0 && j != modo)
				{
					fprintf(arc,"%d,%d,%d,\n",i-bai,j-baj,G[i][j]);
				}
			}
			baj=0;
		}
	}
	fclose(arc);
}
void crearRed ()
{
	int i,j,dim,aux,mun;
	char municipio[40];
	char estado[40];
	char opcion[40];
	for(i=0; i<40; i++)
	{
		municipio[i]='\0';
		estado[i]='\0';
		opcion[i]='\0';
	}
	system ("cls");
	titulo();
	gotoxy(25,2); printf("Introdusca el nombre de la compañia\n");
	gets (nombreC);
	do
	{
		system("cls");
		titulo();
		gotoxy(25,2); printf("Introdusca los gastos fijos\n");
		gotoxy(25,3); gets(opcion);
		gastos_fijos = esEntero(opcion);
		if (gastos_fijos == -1)
		{
			setColor(ROJO);
			gotoxy(25,5); printf("*Dato ingresado invalido");
			setColor(VERDE);
			gotoxy(25,6); printf("Precione enter para continuar");
			gotoxy(25,7); getch();
		}
	}while (gastos_fijos == -1);
	do
	{
		system ("cls");
		titulo();
		gotoxy(25,2); printf("Introdusca el precio del diesel por litro");
		gotoxy(25,3); gets(opcion);
		precio_diesel = esReal(opcion);
		if (precio_diesel == -1)
		{
			setColor(ROJO);
			gotoxy(25,5); printf("*Dato ingresado invalido");
			setColor(VERDE);
			gotoxy(25,6); printf("Precione enter para continuar");
			gotoxy(25,7); getch();
		}
	}while (precio_diesel == -1);
	do
	{
		system ("cls");
		titulo();
		gotoxy(25,2); printf("Introdusca el precio el rendimiento de los autobuses en km/L\n");
		gotoxy(25,3); gets(opcion);
		rendimiento = esReal(opcion);
		if (rendimiento == -1)
		{
			setColor(ROJO);
			gotoxy(25,5); printf("*Dato ingresado invalido");
			setColor(VERDE);
			gotoxy(25,6); printf("Precione enter para continuar");
			gotoxy(25,7); getch();
		}
	}while (rendimiento == -1);
	do 
	{
		system("cls");
		titulo();
		gotoxy(25,2); printf("Introdusca la cantidad de municipios: \n");
		gotoxy(25,3); gets (opcion);
		dim = esEntero(opcion);
		if (dim <= 0)
		{
			setColor(ROJO);
			gotoxy(25,5); printf("*Dato ingresado invalido");
			setColor(VERDE);
			gotoxy(25,6); printf("Precione enter para continuar");
			gotoxy(25,7); getch();
		}
	} while (dim<=0);
	D=dim;
	inicializarDatos ();
	for (i=0; i<D; i++)
	{
		do// VALIDADO
		{
			system("cls");
			titulo();
			fflush(stdin);
			gotoxy(25,2); printf("Ingrese el municipio %d:\n",i+1);
			gotoxy(25,3); gets(municipio);
			fflush(stdin);
			gotoxy(25,4); printf("Ingrese el estado de %s\n",M[i].nombre);
			gotoxy(25,5); gets(estado);
			fflush(stdin);
			mun = obtenerPosicion(municipio,estado);
			if (mun != -1)
			{
			setColor(ROJO);
			gotoxy(25,7); printf("*Este municipio ya fue ingresado");
			setColor(VERDE);
			gotoxy(25,8); printf("Precione enter para continuar");
			gotoxy(25,9); getch();
			}
		} while (mun != -1);
		strcpy(M[i].estado,estado);
		strcpy(M[i].nombre,municipio);
	}
	for (i=0; i<D; i++)
	{
		for (j=(i+1); j<D; j++)
		{
			do// VALIDADO
			{
				system("cls");
				titulo();
				gotoxy(25,2); printf("Ingrese (1) si existe una ruta de %s, %s a %s, %s o viceversa. Ingrese (2) de lo contrario\n",M[i].nombre,M[i].estado,M[j].nombre,M[j].estado);
				gotoxy(25,3); gets(opcion);
				aux = esEntero(opcion);
				if (aux != 1 && aux != 2)
				{
					setColor(ROJO);
					gotoxy(25,5); printf("*Opcion ingresada invalida");
					setColor(VERDE);
					gotoxy(25,6); printf("Precione enter para continuar");
					gotoxy(25,7); getch();
				}
			}while (aux != 1 && aux != 2);
			if (aux == 1)
			{
				do// VALIDADO
				{
					system("cls");
					titulo();
					gotoxy(25,2); printf("Ingrese distancia entre %s, %s y %s, %s\n",M[i].nombre,M[i].estado,M[j].nombre,M[j].estado);
					gotoxy(25,5); gets(opcion);
					G[i][j] = esEntero(opcion);
					G[j][i] = G[i][j];
					if (G[i][j] <=0)
					{
						setColor(ROJO);
						gotoxy(25,5); printf("*Distancia ingresada invalida");
						setColor(VERDE);
						gotoxy(25,6); printf("Precione enter para continuar");
						gotoxy(25,7); getch();
					}					
				}while (G[i][j] <=0);
			}
			else
			{
				G[i][j] = 0;
				G[j][i] = 0;
			}
		}
	}
}
void cargarD (char *archivo)
{
	char c;
	char aux [80];
	int ba = 0,i=0, n=0, k=0,l;
	FILE *arc = fopen(archivo,"rb");
	c=fgetc(arc);
	while(c!=EOF&&k==0)
	{
		if (c=='\n')
		{
			k++;
		}
		else if (c==',')
		{
			switch (ba)
			{
				case 0:
					n = atoi(aux);
					break;
				case 1:
					strcpy (nombreC,aux);
					break;
				case 2:
					gastos_fijos = atoi(aux);
					break;
				case 3:
					precio_diesel = atof(aux);
					break;
				case 4:
					rendimiento = atof(aux);
					break;
			}
			ba++;
			i=0;
			for (l=0;l<sizeof(aux);l++)
			{
				aux[l]='\0';
			}
		}
		else if (c!='\r')
		{
			aux[i]=c;
			i++;
		}
		c=fgetc(arc);
	}
	fclose (arc);
	D = n;
}
void cargarRed(char *archivo)
{
	char c;
	char aux [80];
	int ba=0, i=0, n=0, k=0, ci, cj, cpeso, l;
	FILE *arc = fopen(archivo,"rb");
	c=fgetc(arc);
	inicializarDatos();
	for (l=0;l<sizeof(aux);l++)
	{
		aux[l]='\0';
	}
	i=0;
	{
		while(c != EOF)
		{
			if (k>D)
			{
				if (c == '\n')
				{
					ba=0;
					G[ci][cj] = cpeso;
					G[cj][ci] = cpeso;
				}
				else if (c == ',')
				{
					switch (ba)
					{
						case 0:
							ci = atoi(aux);
							break;
						case 1:
							cj = atoi(aux);
							break;
						case 2:
							cpeso = atoi(aux);
							break;
					}
					i=0;
					ba++;
					for (l=0;l<sizeof(aux);l++)
					{
						aux[l]='\0';
					}
				}
				else if (c!='\r')
				{
					aux[i]=c;
					i++;
				}
			}
			else
			{
				if (k == 0)
				{
					if (c == '\n')
					{
						k++;
					}
				}
				else 
				{
					if (c == '\n')
					{
						k++;
						ba = 0;
					} 
					else if (c == ',')
					{
						i=0;
						if (ba == 0)
						{
							fflush(stdin);
							strcpy(M[k-1].nombre,aux);
						}
						if (ba == 1)
						{
							fflush(stdin);
							strcpy(M[k-1].estado,aux);
						}
						ba++;
						for (l=0;l<sizeof(aux);l++)
						{
							aux[l]='\0';
						}
					}
					else if (c!='\r')
					{
						aux[i]=c;
						i++;
					}
				}
			}
			c=fgetc(arc);
		}
		fclose(arc);
	}
}
void imprimirArreglo ()
{
	int i;
	char aux[40];
	for (i=0; i<D; i++)
	{
		printf("Municipio: %s, Estado: %s\n",M[i].nombre,M[i].estado);
	}
}
void imprimirRed ()
{
	int i, j;
    printf("\nMatriz\n\t");
    for (i=0; i<D;i++)
    {
    	printf("%5d\t",i);
	}
	printf("\n\t");
    for (i=0; i<D;i++)
    {
    	printf("___\t");
	}
	printf("\n");
    for (i=0;i<D;i++)
    {
    	printf("%5d|\t",i);
    	for (j=0;j<D;j++)
    	{
    		printf ("%5d\t",G[i][j]);
		}
		printf("\n");
	}
}
int minDistance(int dist[], bool sptSet[]) 
{ 
	int v;
	// Initialize min value 
	int min = INT_MAX, min_index; 

	for (v = 0; v < D; v++) 
		if (sptSet[v] == false && dist[v] <= min) 
			min = dist[v], min_index = v; 

	return min_index; 
} 
void printPath(int parent[], int j) 
{ 
	
	// Base Case : If j is source 
	if (parent[j] == - 1) 
		return; 
	printPath(parent, parent[j]); 
	setColor(BLANCO);
	printf("                         De %s, %s a %s, %s\n",M[parent[j]].nombre,M[parent[j]].estado,M[j].nombre,M[j].estado); 
	transbordos ++;
} 
void inicializarDatos ()
{
	int i,j;
	for (i = 0; i < 1000; i++)
	{
		for (j=0; j < 1000; j++)
		{
			G[i][j] = 0;
		}
	}
	for (i = 0; i < 1000; i++)
	{
		for (j=0; j<40; j++)
		{
			M[i].estado[i]='\0';
			M[i].nombre[i]='\0';
		}
	}
}
int printSolution(int dist[], int n, int parent[], int src, int dest) 
{  
	system ("cls");
	titulo();
	transbordos = 0;
	printf("                         Rutas a tomar de %s, %s a %s, %s :\n",M[src].nombre,M[src].estado,M[dest].nombre,M[dest].estado);
	printPath(parent, dest);
	setColor (VERDE);
	printf("                         Autobuses a tomar: %d\nDistancia total: %dKm\nPrecio total: $%.2f\n",transbordos,dist[dest], (float)(transbordos*gastos_fijos) + (precio_diesel * dist[dest])/(4*rendimiento));
} 
void encontrarCamino (int src, int dest)
{
	
	// The output array. dist[i] 
	// will hold the shortest 
	// distance from src to i 
	int V = D;
	int dist[V]; 

	// sptSet[i] will true if vertex 
	// i is included / in shortest 
	// path tree or shortest distance 
	// from src to i is finalized 
	bool sptSet[V]; 

	// Parent array to store 
	// shortest path tree 
	int parent[V]; 

	// Initialize all distances as 
	// INFINITE and stpSet[] as false 
	int i;
	for (i = 0; i < V; i++) 
	{ 
		parent[src] = -1; 
		dist[i] = INT_MAX; 
		sptSet[i] = false; 
	} 

	// Distance of source vertex 
	// from itself is always 0 
	dist[src] = 0; 

	// Find shortest path 
	// for all vertices 
	int count;
	for (count = 0; count < V - 1; count++) 
	{ 
		// Pick the minimum distance 
		// vertex from the set of 
		// vertices not yet processed. 
		// u is always equal to src 
		// in first iteration. 
		int u = minDistance(dist, sptSet); 

		// Mark the picked vertex 
		// as processed 
		sptSet[u] = true; 

		// Update dist value of the 
		// adjacent vertices of the 
		// picked vertex. 
		int v;
		for (v = 0; v < V; v++) 

			// Update dist[v] only if is 
			// not in sptSet, there is 
			// an edge from u to v, and 
			// total weight of path from 
			// src to v through u is smaller 
			// than current value of 
			// dist[v] 
			if (!sptSet[v] && G[u][v] && 
				dist[u] + G[u][v] < dist[v]) 
			{ 
				parent[v] = u; 
				dist[v] = dist[u] + G[u][v]; 
			} 
	} 

	// print the constructed 
	// distance array 
	printSolution(dist, V, parent, src,dest); 
}
void gotoxy(int x,int y)
{ 
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
}
void setColor(int ForgC)
 {
     WORD wColor;

      HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
      CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
                 //Mask out all but the background attribute, and add in the forgournd     color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
 }
