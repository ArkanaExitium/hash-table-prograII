/*
Para compilar este programa en Linux
gcc -c TADListaDobleLigada.c
gcc -c TADTablaHash.c
gcc -g mainHashTable.c  TADTablaHash.o TADListaDobleLigada.o -lm
./a.out
*/
#include <stdio.h>
#include <stdlib.h>	
#include <string.h> 
#include <time.h> 
#include <unistd.h>
#include <math.h>
#include "TADTablaHash.h"
void procedimientoHashAbierto(void)
{
	int selector;
	int contador,contador1;
	elemento e,e1;
	lista Hash[HASHSIZE]; //creamos la tabla hash
	char llaveAuxiliar[150]=" ";
	char informacionAuxiliar[150]=" ";
	createTable(Hash);
	clearTable(Hash);	
	do{
		printf("\nTabla Hash con Hashing Abierto \n");
		printf("Seleccione cualquier una opcion del menu: \n");
		printf("1.-Insertar en tabla hash \n");
		printf("2.-Desplegar tabla hash \n");
		printf("3.-Buscar elemento en tabla hash \n");
		printf("4.-Eliminar elemento de tabla hash \n");		
		printf("5.-Salir de menu de selección de tabla hash (Hashing Abierto)  \n");
		printf("Opcion: ");
		scanf("%d",&selector);
		switch(selector)
		{
			case 1:
				system("clear");
				printf("\nIngrese nombre de persona u objeto y posteriormente ingrese su informacion asociada para almacenar en tabla hash:       \n");					
				contador= read(0,llaveAuxiliar, 109);//pequeño bug con nombres largos como el mio...deberia hacer al hash una funcion unsigned int
				llaveAuxiliar[contador] = '\0';					
				contador1= read(0,informacionAuxiliar, 99);
				informacionAuxiliar[contador1] = '\0';				
				strcpy(e.llave,llaveAuxiliar);
				strcpy(e.informacion,informacionAuxiliar);				
				insertElementIntoOpenHTable(Hash,e);	
				printf("\nInserción exitosa \n");	
				strcpy(e.llave,"vacio");
				strcpy(e.informacion,"vacio");				
			break;
			case 2:
				system("clear");
				printHashTable(Hash);
			break;
			case 3:
				system("clear");
				printf("\nIngrese nombre de persona u objeto para buscar en tabla hash:       \n");
				contador= read(0,llaveAuxiliar, 109);
				llaveAuxiliar[contador] = '\0';					
				e1=retrieveElementFromOpenHTable(Hash,llaveAuxiliar);
				strcpy(e1.llave,"vacio");
				strcpy(e1.informacion,"vacio");					
			break;				
			case 4:
				system("clear");
				printf("\nIngrese nombre de persona u objeto para eliminar en tabla hash:       \n");
				contador= read(0,llaveAuxiliar, 109);
				llaveAuxiliar[contador] = '\0';			
				removeElementFromOpenHTable(Hash,llaveAuxiliar);
			break;							
			case 5:
				system("clear");
				deleteTable(Hash);					
			break;
		}
	}while(selector!=5);
	return;	
}
void procedimientoHashCerrado(void)
{
	int selector;
	int contador,contador1;
	elemento e,e1;
	lista Hash[HASHSIZE]; //creamos la tabla hash
	char llaveAuxiliar[150]=" ";
	char informacionAuxiliar[150]=" ";
	createTable(Hash);
	clearTable(Hash);	
	do{
		printf("\nTabla Hash con Open Addresing \n");
		printf("Seleccione cualquier una opcion del menu: \n");
		printf("1.-Insertar en tabla hash \n");
		printf("2.-Desplegar tabla hash \n");
		printf("3.-Buscar elemento en tabla hash \n");
		printf("4.-Eliminar elemento de tabla hash \n");		
		printf("5.-Salir de menu de selección de tabla hash (Open Addresing)  \n");
		printf("Opcion: ");
		scanf("%d",&selector);
		switch(selector)
		{
			case 1:
				system("clear");
				system("clear");
				printf("\nIngrese nombre de persona u objeto (Mayúsculas) y luego su informacion asociada para almacenar en tabla hash:       \n");					
				contador= read(0,llaveAuxiliar, 109);//pequeño bug con nombres largos como el mio
				llaveAuxiliar[contador] = '\0';					
				contador1= read(0,informacionAuxiliar, 99);
				informacionAuxiliar[contador1] = '\0';				
				strcpy(e.llave,llaveAuxiliar);
				strcpy(e.informacion,informacionAuxiliar);				
				insertElementIntoClosedHTable(Hash,e);	
				printf("\nInserción exitosa \n");	
				strcpy(e.llave,"vacio");
				strcpy(e.informacion,"vacio");	
			break;
			case 2:
				system("clear");
				printHashTable(Hash);
			break;
			case 3:
				system("clear");
				printf("Buscar elemento en tabla hash \n");
			break;				
			case 4:
				system("clear");
				printf("Eliminar elemento de tabla hash \n");
			break;							
			case 5:
				system("clear");
				deleteTable(Hash);
			break;
		}
	}while(selector!=5);
	return;	
}
void procedimiento(void)
{
	int selector;
	do{
		printf("\nTipo de Tabla Hash \n");
		printf("Seleccione cualquier una opcion del menu: \n");
		printf("1.-Tabla Hash con hashing abierto \n");
		printf("2.-Tabla Hash con hashing cerrado (Open Addresing) \n");		
		printf("3.-Salir de menu de selección de tabla hash \n");
		printf("Opcion: ");
		scanf("%d",&selector);
		switch(selector)
		{
			case 1:
				system("clear");
				procedimientoHashAbierto();
			break;
			case 2:
				system("clear");
				procedimientoHashCerrado();
			break;				
			case 3:
				system("clear");
			break;
		}
	}while(selector!=3);
	return;	
}
void Menu(void)
{
	int selector;
	do{
		printf("\nMétodo de Busqueda Hash \n");
		printf("Seleccione cualquier una opcion del menu: \n");
		printf("1.-Empezar con el programa \n");
		printf("2.-Salir del programa \n");
		printf("Opcion: ");
		scanf("%d",&selector);
		switch(selector)
		{
			case 1:
				system("clear");
				procedimiento();
			break;
			case 2:
				system("clear");
			break;
		}
	}while(selector!=2);
	return;
}	
int main(void)
{
	Menu();
	return 0;
}
