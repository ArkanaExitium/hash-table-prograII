/*
Este archivo solo incluye las estructuras, tipos de datos y
declaración de las operaciones del TAD  Lista.

EL CODIGO QUE IMPLEMENTA LAS FUNCIONES ES EL ARCHIVO: TADTablaHash.c
*/
#define TRUE	1
#define FALSE	0
//#define HASHSIZE 997
#define HASHSIZE 11
#include "TADLista.h"
typedef lista tablaHash;
void createTable(tablaHash *h);
void deleteTable(tablaHash *h);
void clearTable(tablaHash *h);
//Operaciones de posicionamiento y busqueda
unsigned long int hash1(char *llave);
unsigned long int hash2(char *llave);
int numberOfElementsInIndex(tablaHash *h,int index);
int numberOfElementsInHashTable(tablaHash *h);
//Operación de consulta
void printElementsInIndex(tablaHash *h,int index);
void printHashTable(tablaHash *h);
elemento retrieveElementFromOpenHTable(tablaHash *h, char *llave);
//elemento retrieveElementFromClosedHTable(tablaHash *h, char *llave);
//Operaciones de modificación
void insertElementIntoOpenHTable(tablaHash *h,elemento e);
void removeElementFromOpenHTable(tablaHash *h, char *llave);
//void insertElementIntoClosedHTableRecursive(tablaHash *h,elemento e,int indice,int contadorColisiones);
void insertElementIntoClosedHTable(tablaHash *h,elemento e);
//void removeElementFromClosedHTable(tablaHash *h, char *llave);
//falta implementar hash table cerrada