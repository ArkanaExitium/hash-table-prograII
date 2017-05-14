/*
Para compilar este programa en Linux
gcc -c TADListaDobleLigada.c

gcc -o -pedantic -Wall -std=c99  heapsortLista heapsortLista.c TADListaDobleLigada.o

./heapsortLista

*/
#include <stdio.h>
#include <stdlib.h>	
#include <string.h> 
#include <time.h> 
#include "TADTablaHash.h"
void createTable(tablaHash *h)
{
	int i;
	for(i=0;i<HASHSIZE;i++)
	{
		Initialize(&h[i]);
	}
}
void deleteTable(tablaHash *h)
{
	int i;
	for(i=0;i<HASHSIZE;i++)
	{
		Destroy(&h[i]);
	}
}
void clearTable(tablaHash *h)//aqui se podria hacer esta funcion no solo para "inicializar" tablas hash recien creadas,sino para tambien limpiar tablas hash no recien creadas.De hecho no sería tan complicado,solo que ya no alcanzó el tiempo para implementar dicha funcion (inspirarse en insertOHT)
{
	int i;
	elemento e;
	strcpy(e.llave,"vacio");
	strcpy(e.informacion,"vacio");
	for(i=0;i<HASHSIZE;i++)
	{
		Add(&h[i],e);	
	}
}
unsigned long int hash1(char* llave)
{
	unsigned long int hash=0;
	int aux1,i;
	for(i=0;i<strlen(llave);i++)
	{
		if(i%3==0)
		{
			aux1=0;
			aux1+=(int)llave[i];
		}
		if(i%3==1)
			aux1-=(int)llave[i];
		if(i%3==2)
		{
			aux1*=(int)llave[i];
			hash+=aux1;
		}
	}
	return hash;
}
//Para hashing cerrado (doble hashing)
unsigned long int hash2(char* llave)
{
	unsigned long int hash=0;
	int aux1,i;
	for(i=0;i<strlen(llave);i++)
		hash+=(int)llave[i];
	return hash;
}
int numberOfElementsInIndex(tablaHash *h,int index)
{
	return Size(&h[index-1]);
}
int numberOfElementsInHashTable(tablaHash *h)
{
	int i,j;
	int numberOfElements=0;
	for(i=0;i<HASHSIZE;i++)
	{
		if(Size(&h[i])>0)
		{
			for(j=1;j<=Size(&h[i]);j++)
			{
				if(strcmp("vacio",Element(&h[i],j).llave))
				{
					numberOfElements++;
				}			
			}		
		}		
	}
	return numberOfElements;
}
void printElementsInIndex(tablaHash *h,int index)
{
	int i;
	posicion p1;
	elemento e;
	//numberOfElementsInIndex(&h,index)
	if(Size(&h[index-1])>0)
	{
		for(i=1;i<=Size(&h[index-1]);i++)
		{
			if(strcmp("vacio",Element(&h[index-1],i).llave)!=0 && strcmp("vacio",Element(&h[index-1],i).informacion)!=0)
			{
				printf("¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤ \n");
				printf("Indice:\t %d\n",i);
				printf("\t%s\n",Element(&h[index-1],i).llave);
				printf("\t%s\n",Element(&h[index-1],i).informacion);	
				printf("¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤ \n");
			}
			
		}
		if(strcmp("vacio",Element(&h[index-1],1).llave)!=0 && strcmp("vacio",Element(&h[index-1],1).informacion)!=0)
		{		
			printf("# de elementos:\t %d\n",Size(&h[index-1]));
			printf("_________________________________________\n");		
		}
	}
	else
	{
		printf("\nLa tabla hash en el indice %d esta vacia\n \n",index);
	}
	return;	
}
void printHashTable(tablaHash *h)
{
	int i;
	printf("\n \n");
	printf("••••••••••••••••••••••••••••••••••••••••• \n");
	for(i=0;i<HASHSIZE;i++)
	{
		if(strcmp("vacio",Element(&h[i],1).llave)!=0 && strcmp("vacio",Element(&h[i],1).informacion)!=0)
		{
			printf("_________________________________________ \n");	
			printf("\t Elemento :  %d \n",i+1);	
			printf("_________________________________________ \n");				
			printElementsInIndex(h,i+1);				
		}
	}
	printf("••••••••••••••••••••••••••••••••••••••••• \n");	
	printf("\n \n");	
}
void insertElementIntoOpenHTable(tablaHash *h,elemento e)
{	
	int indice=hash1(e.llave)%HASHSIZE;
	if(strcmp("vacio",Position(&h[indice-1],First(&h[indice-1])).llave)==0) // ¿El lugar escogido está vacio?
	{	
		Replace(&h[indice-1],ElementPosition(&h[indice-1],1),e);
	}
	else // ¿La llave está duplicada?
	{	
		Add(&h[indice-1],e);
	}	
}

void insertElementIntoClosedHTable(tablaHash *h,elemento e)
{	
	int contadorColisiones=0;
	int indice=abs(hash1(e.llave)%HASHSIZE);
//	int casoBaseRastreoCuadratico=1;
//	int indicadorDeSobrecargaDeHT=0;	
	while(!strcmp("vacio",Element(&h[indice-1],1).llave)==0 && strcmp(e.llave,Element(&h[indice-1],1).llave)==0 && numberOfElementsInHashTable(h)<HASHSIZE) // Mientras el lugar no esté vacio
	{	
//		indice+=casoBaseRastreoCuadratico;
//		casoBaseRastreoCuadratico+=2;
		
//		if(indice > HASHSIZE)
//		{
//			indice %= HASHSIZE-1;			
//		}
		contadorColisiones++;
		if(strcmp(e.llave,Element(&h[indice-1],1).llave)==0)
		{
			printf("Colisión #%d en posicion #%d de tabla hash",contadorColisiones,indice);		
		}		
		indice=(abs(hash1(e.llave)%HASHSIZE)+abs(hash2(e.llave)%HASHSIZE-6))%HASHSIZE;		
	}		
	if(strcmp("vacio",Element(&h[indice-1],1).llave)==0) // ¿El lugar escogido está vacio?
	{	
		Replace(&h[indice-1],ElementPosition(&h[indice-1],1),e);
	}
	else if(strcmp(e.llave,Element(&h[indice-1],1).llave) == 0) // ¿El lugar escogido contiene la misma llave?
	{	
		printf("\nError:Llave duplicada");
				//if(numberOfElementsInHashTable(h)==HASHSIZE)
	}	
	else 
	{	
		printf("\nError:Se ha excedido la capacidad de elementos a almacenar en la tabla hash (Open Addresing)");
	}	
}

/*
void insertElementIntoClosedHTableRecursive(tablaHash *h,elemento e,int indice,int contadorColisiones)
{
	if(strcmp(Element(&h[indice-1],1).llave,"vacio")==0) // ¿El lugar escogido está vacio?
	{	
		Replace(&h[indice-1],ElementPosition(&h[indice-1],1),e);
	}	
	else if(strcmp("vacio",Element(&h[indice-1],1).llave)!=0 && strcmp(e.llave,Element(&h[indice-1],1).llave)!=0) // ¿La llave está duplicada?
	{	
		++contadorColisiones;
		printf("\nColisión #%d en posicion #%d de tabla hash con el elemento %s \n",contadorColisiones,indice+1,e.llave);		
		indice=(abs(hash1(e.llave)%HASHSIZE)+(contadorColisiones*contadorColisiones))%HASHSIZE;
		insertElementIntoClosedHTableRecursive(h,e,indice,contadorColisiones);
	}
	else if(numberOfElementsInHashTable(h)==HASHSIZE)
	{
		printf("ERROR : La tabla hash esta llena,no se pueden insertar elementos");
	}
}
void insertElementIntoClosedHTable(tablaHash *h,elemento e)//de hecho,si nos basaramos en las funciones de insertar de la tabla has,podrimos crear funciones de modificion de elementos de la tabla,en vez de buscar la cadena vacio,buscariamos la llave y la reemplazariamos por otra.Eso ya no es necesario para las operaciones de la tabla hash,pero podría realizarse
{
	int indice=hash1(e.llave)%HASHSIZE;
	int contadorColisiones=0;
	if(strcmp(Element(&h[indice-1],1).llave,"vacio")==0) // ¿El lugar escogido está vacio?
	{	
		Replace(&h[indice-1],ElementPosition(&h[indice-1],1),e);
	}		
	else if(strcmp(Element(&h[indice-1],1).llave,"vacio")!=0 && strcmp(Element(&h[indice-1],1).llave,e.llave)!=0) // ¿El lugar escogido no está vacio?
	{	
		insertElementIntoClosedHTableRecursive(h,e,indice,contadorColisiones);
	}	
	else if(strcmp(e.llave,Element(&h[indice-1],1).llave)==0) // ¿La llave está duplicada?
	{	
		printf("\nERROR : La llave del elemento está duplicada");
	}
//	else
//	{
//		printf("\nERROR : La tabla hash esta llena,no se pueden insertar elementos");
//	}
}

*/









elemento retrieveElementFromOpenHTable(tablaHash *h, char *llave)
{
	int indice=hash1(llave)%HASHSIZE;
	int i;
	elemento e;
	clock_t start, end;
	boolean seEncontroLaInformacion=FALSE;
	strcpy(e.llave,llave);
	char auxInformacion[100];
	start = clock(); 
	for(i=1;i<=Size(&h[indice-1]);i++)
	{
		if(strcmp(llave,Element(&h[indice-1],i).llave)==0)
		{
			seEncontroLaInformacion=TRUE;
			strcpy(auxInformacion,Element(&h[indice-1],i).informacion);
		}			
	}
	if(seEncontroLaInformacion)
	{
		strcpy(e.informacion,auxInformacion);
		printf("\n'%s' fue la informacion encontrada asociada a %s \n",e.informacion,e.llave);
		end = clock(); 
		printf("Tiempo de busqueda en tabla hash (Open Hashing): %f segundos\n", (end - start) /(float) CLOCKS_PER_SEC);			
		return e;
	}
	if(!seEncontroLaInformacion)
	{
		printf("\nERROR (retrieveO): No se encontro informacion \n");
	}
}
void removeElementFromOpenHTable(tablaHash *h, char *llave)//revisar si funciona adecuadamente cuando hay mas de un elemento en una lista en particular de la tabla hash
{
	int indice=hash1(llave)%HASHSIZE;//aqui esta el detalle para implementar la funcion borrado en hashing cerrado
	int indiceAuxiliar,i;
	elemento e,e1;
	posicion posicionElementoAEliminar,p1,p2;
	boolean seEncontroElElemento=FALSE;
	printf("\nElemento a remover :   %s \n",llave);
	e1=retrieveElementFromOpenHTable(h,llave);
	printf("\n \n");
	strcpy(e.llave,"vacio");
	strcpy(e.informacion,"vacio");
	for(i=1;i<=Size(&h[indice-1]);i++)
	{
		if(strcmp("vacio",Element(&h[indice-1],i).llave)!=0 && strcmp("vacio",Element(&h[indice-1],i).informacion)!=0)//si el espacio no esta vacio
		{
			if(strcmp(e1.llave,Element(&h[indice-1],i).llave)==0 && strcmp(e1.informacion,Element(&h[indice-1],i).informacion)==0)//si se encuentra al elemento
			{
				seEncontroElElemento=TRUE;
				p1=ElementPosition(&h[indice-1],i);
				indiceAuxiliar=i;
			}				
		}		
	}	
	if(seEncontroElElemento==FALSE)
	{
		printf("%s no fue encontrado/a \n",llave);
	}
	else if(strcmp(Element(&h[indice-1],indiceAuxiliar).llave,llave)==0 && Size(&h[indice-1])==1 && seEncontroElElemento==TRUE) //si en el espacio se encuentra un solo elemento y es el que queremos eliminar

	{
		strcpy(e.llave,"vacio");
		strcpy(e.informacion,"vacio");
		Replace(&h[indice-1],ElementPosition(&h[indice-1],indiceAuxiliar),e);
		
	}
	else if(Size(&h[indice-1])!=1 && seEncontroElElemento==TRUE)
	{
		Remove(&h[indice-1],ElementPosition(&h[indice-1],indiceAuxiliar));
	}	
}