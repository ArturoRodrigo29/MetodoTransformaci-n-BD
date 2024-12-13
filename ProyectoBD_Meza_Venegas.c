/*****************************************************************************************
//EQUIPO BASE DE DATOS
//VENEGAS MARIANO KARLA
//MEZA DIAZ ARTURO RODRIGO
//3CM1 PROF. NANCY OCOTITLA
//IMPLEMENTACION METODO DE TRANSFORMACION en C
*******************************************************************************************/
// Librerias necesarias
#include <stdio.h>//Necesaria para la lectura de datos e impresion en pantalla
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//Declaración de constates
#define EntMax 30
#define AttMax 30

//Declaración de estructuras
//Estructura para la definicion de atributos compuestos
typedef struct{
	int nAtri;
	char nombre[50];
	char atributos_comp[AttMax][50];
}Compuesto;
//estructura para la definicion de entidades
typedef struct {
	char nombre[50];
	char llavePrimaria[50];
	char tipo;
	char atributos_simples[AttMax][50];
	char atributos_multi[AttMax][50];
	char atributos_der[AttMax][50];
	int nAtri_simples;
	int nAtri_multi;
	int nAtri_der;
	int nAtri_comp;
	Compuesto Acomp [AttMax];
} Enti;

//estructura para la definicion de relaciones
typedef struct {
	char nombre[50];
	char tipo;
	char Enti1[50];
	char Enti2[50];
	char atributos[AttMax][50];
	char PrimeraCard;
	char SegundaCard;
	char Partic1;
	char Partic2;
	int nAtri;
} Rela;


//estructura para la definicion de relaciones del metodo relacional
typedef struct{
	char nombre[50];
	char LlavePrim[AttMax][50];
	char atributos[AttMax][50];
	int num_PK;
	int nAtri;
}MRelac;

//declaracion de nuestras variables globales
int nEnti = 0;
int NRelac = 0;
int nEntiRelac=0;

//Prototipos de funciones

void Paso1(Enti *entidades, MRelac *relacional);
void Paso2(Enti *entidades, MRelac *relacional, Rela *relaciones);
void Paso3(Enti *entidades, MRelac *relacional, Rela *relaciones);
void Paso4(Enti *entidades, MRelac *relacional, Rela *relaciones);
void Paso5(Enti *entidades, MRelac *relacional, Rela *relaciones);
void Paso6(Enti *entidades, MRelac *relacional, Rela *relaciones);
void Paso8(Enti *entidades, MRelac *relacional, Rela *relaciones);


//Función principal
int main() {
	//Estructura para entidades
	Enti entidades[EntMax]; 
	//Estructura para relaciones
	Rela relaciones[EntMax]; 
	//Estructura para metodo transformacion (Modelo MRelac)
	MRelac relacional[EntMax]; 
	//Pide los datos de las entidades
	printf("Digite el numero de entidades: ");
	scanf("%d", &nEnti);
	if(nEnti<=0)//caso base
		exit(0);
	if(nEnti>0){
		for (int i = 0; i < nEnti; i++) {
		char caracter;
		Enti e; //Se crea un struct temporal
		//Números de entidades a ingresar
		getchar();
		printf("Introduce nombre de entidad %d: ", i + 1);
		scanf("%[^\n]", e.nombre);
		//Tipo de entidad ingresada
		int aux=0; 
		do{
			getchar();
			printf("Introduce F si es entidad fuerte, D si debil (en mayusculas): ");
			scanf("%c", &caracter);
			//Se comprueba si lo introducido es una opción válida 
			if(caracter =='F' || caracter=='D'){ 
				aux=1;
				e.tipo=caracter;	
			}
			else{
				printf("Introduzca tipo de entidad correcta, por favor :d \n");
			}
		}while(aux==0);
		
		//Llave primaria-----------------------------------------------------------------------------------
		getchar();
		printf("Introduzca el atributo que es la llave primaria de entidad %d: ", i+1);
		scanf("%[^\n]", e.llavePrimaria);
		
		//Atributos simples--------------------------------------------------------------------------------
		printf("Introduzca el num de atributos simples de entidad %d: ", i + 1);
		scanf("%d", &e.nAtri_simples);
		for (int j = 0; j < e.nAtri_simples; j++) {
			getchar();
			printf("Introduzca el nombre del atributo %d: ", j + 1);
			scanf("%[^\n]", e.atributos_simples[j]);
		}
		
		//Atributos multivalor-----------------------------------------------------------------------------
		printf("Introduzca el num de atributos multivalor de entidad %d: ", i+1);
		scanf("%d", &e.nAtri_multi);
		for (int j = 0; j < e.nAtri_multi; j++) {
			getchar();
			printf("Introduzca el nombre del atributo multivalor %d: ", j + 1);
			scanf("%[^\n]", e.atributos_multi[j]);
		}
		
		//Atributos derivados------------------------------------------------------------------------------
		printf("Introduzca el num de atributos derivados de entidad %d: ", i+1);
		scanf("%d", &e.nAtri_der);
		for(int j=0;j<e.nAtri_der;j++){
			getchar();
			printf("Introduzca el nombre del atributo derivado %d: ", i+1);
			scanf("%[^\n]", e.atributos_der[j]);
		}
		
		//Atributos compuestos--------------------------------------------------------------------------------
		printf("Introduzca el num de atributos compuestos de entidad %d: ", i+1);
		scanf("%d", &e.nAtri_comp);
		for (int j = 0; j < e.nAtri_comp; j++) {
			getchar();
			printf("Introduzca el nombre del atributo compuesto %d: ", j + 1);
			scanf("%[^\n]", e.Acomp[j].nombre);			
			printf("Introduzca el num de atributos que tiene el atributo compuesto %d: ", j+1);
			scanf("%d", &e.Acomp[j].nAtri);
			for(int k=0;k<e.Acomp[j].nAtri;k++){
				getchar();
				printf("Introduzca el atributo %d del atributo %s: ", k+1, e.Acomp[j].nombre);
				scanf("%[^\n]", e.Acomp[j].atributos_comp[k]);
			}
		}
		entidades[i] = e; //pasamos datos del temporal al original
	}
	

	printf("\t\t Muestra de entidades registradas: \n");
	for(int i=0;i<nEnti;i++){
		printf("%d-. %s(%c)\n", i+1, entidades[i].nombre, entidades[i].tipo);
	}
	printf("\n \t\t RELACIONES Y CARACTERISTICAS");
	printf("\n Introduzca el num. de relaciones: ");
  	scanf("%d", &NRelac);
  	for (int i = 0; i < NRelac; i++) {
    	Rela r; // struct temporal
    	char ent1[20];
    	//Nombre de la relación
    	printf("Introduzca nombre de la relacion %d: ", i + 1);
    	scanf("%s", r.nombre);
    	
    	int aux=0, auxC1=0; 
    	do{
    		printf("Introduzca nombre de la entidad 1 de la relacion %d: ", i+1);
    		scanf("%s", ent1); 
    		
			for(int j=0;j<=nEnti;j++){
				if(strcmp(ent1, entidades[j].nombre)==0){
    				auxC1=j; 
					strcpy(r.Enti1, ent1); 
					aux=1; 
					break; 
				}
				if(j==nEnti){
					printf("Entidad no encontrada :( \n");
				}	
			} 								
		}while(aux==0);
		
		aux=0;
		char ent2[20];
		int auxC2=0; 
		do{
			printf("Introduzca el nombre de la entidad 2 de la relacion %d: ", i+1);
    		scanf("%s", ent2);
    		
			for(int j=0;j<=nEnti;j++){
			
    			if(strcmp(ent2, entidades[j].nombre)==0){
    				auxC2=j;
    				strcpy(r.Enti2, ent2);
					aux=1;
					break;
				}
				if(j==nEnti){
					printf("Entidad no encontrada :( \n");	
				}
			}	
		}while(aux==0);
		
		char card1;
		aux=0;
		do{
			getchar();
			printf("Introduzca la cardinalidad (1,N,M) de la entidad 1 : ", i+1);
    		scanf("%c", &card1);
    		if(card1=='1' || card1=='M' || card1=='N'){
    			aux=1; 
    			r.PrimeraCard=card1; 
			}
			else 
				printf("No es valida la opcion ingresada \n");
		}while(aux==0);
		
	
		aux=0;
		char card2;
		do{
			getchar();
			printf("Introduzca la cardinalidad (1,N,M) de la entidad 2 : ", i+1);
    		scanf("%c", &card2);
    		
    		if(card2=='1' || card2=='M' || card2=='N'){
    			aux=1;
    			r.SegundaCard=card2;
			}
			else 
				printf("No es valida la opcion ingresada\n");
		}while(aux==0);
		
		aux=0;
		char part1;
		do{
			getchar();
			printf("Introduzca la participacion de la entidad 1 \n (Escriba T si es total o P si es parcial en mayuscula) :", i+1);
			scanf("%c", &part1);
			if(part1=='T' || part1=='P'){
				aux=1; 
				r.Partic1=part1; 
			}
			else
				printf("Participación incorrecta :7 \n");
		}while(aux==0);
		
		aux=0;
		char part2;
		do{
			getchar();
			printf("Introduzca la participacion de la entidad 1 \n (Escriba T si es total o P si es parcial en mayuscula) : ", i+1);
			scanf("%c", &part2);
			if(part1=='T' || part1=='P'){
				aux=1; 
				r.Partic2=part2;//asignacion de participacion
			}
			else
				printf("Participacion incorrecta :7\n");
		}while(aux==0);
		
	
    	aux=0;
    	char relacion;
		do{
			getchar();
			printf("Introduzca si la relacion es Regular o Identificada (R o I en mayusc): ");
    		scanf("%c", &relacion);
			if(relacion =='I' || relacion=='R'){
				if(relacion == 'R'){
					if(entidades[auxC1].tipo=='F' && entidades[auxC2].tipo=='F'){
						aux=1;
						r.tipo=relacion; //Se asigna el tipo de relación ya validada a la relación
					}
					else
						printf("Lo sentimos, el tipo de su relación no valida para las entidades elegidas\n");
				}
				if(relacion == 'I'){
					
					if(entidades[auxC1].tipo == 'D' || entidades[auxC2].tipo== 'D'){
						aux=1; 
						r.tipo=relacion;
					}
					else
						printf("Lo sentimos, el tipo de su relacion no valida para las entidades elegidas\n");
				}
			}
			else{
				printf("Invalido tipo de relacion \n");
			}
		}while(aux==0);
		
		//Atributos a las relaciones
		printf("Introduzca el num de atributos que tiene la relacion %d: ", i+1);
		scanf("%d", &r.nAtri);
		for(int j=0;j<r.nAtri;j++){
			getchar();
			printf("Introduzca atributo %d: ", j+1);
			scanf("%[^\n]", r.atributos[j]);
		}
    	relaciones[i] = r;
  }
  
  Paso1(entidades, relacional);
  Paso2(entidades, relacional, relaciones);
  Paso3(entidades, relacional, relaciones);
  Paso4(entidades, relacional, relaciones);
  Paso5(entidades, relacional, relaciones);
  Paso6(entidades, relacional, relaciones);
		printf("\n Paso 7 \n");
		for(int j=0;j<nEntiRelac;j++){
			printf("%s=((", relacional[j].nombre);
			for(int i=0;i<relacional[j].num_PK;i++){
				printf("%s", relacional[j].LlavePrim[i]);
				if(i+1<relacional[j].num_PK)
					printf(", ");
			}
			printf(")(PK), ");
			for(int i=0;i<relacional[j].nAtri;i++){
				printf("%s", relacional[j].atributos[i]);
				if(i+1<relacional[j].nAtri)
					printf(", ");
			}
		printf(")\n");
		}
	//Paso8(entidades, relacional, relaciones);
  }	
}


void Paso1(Enti *entidades, MRelac *relacional){
	MRelac r; // estructura auxiliar 
	int auxRelacional=0;
		for(int i=0;i<nEnti;i++){
			//Valida si la entidad es Fuerte
			if(entidades[i].tipo== 'F'){
				int auxC=0, count=0; 
				nEntiRelac++; 
				r.num_PK=0;
				strcpy(r.nombre, entidades[i].nombre); //copia nombre y lo manda para el metodo
				strcpy(r.LlavePrim[0], entidades[i].llavePrimaria);//copia llave y lo manda para el metodo
				r.num_PK++;
			
				for(int j=0;j<entidades[i].nAtri_simples;j++){
					strcpy(r.atributos[j], entidades[i].atributos_simples[j]);//copia at. simples y lo manda para el metodo
					auxC++;
					count++;
				}

				for(int j=0;j<entidades[i].nAtri_comp;j++){
					for(int l=0, k=auxC;l<entidades[i].Acomp[j].nAtri;l++, k++){
						strcpy(r.atributos[k], entidades[i].Acomp[j].atributos_comp[l]);	
						count++; 				
					}
				}
				r.nAtri=count;
				relacional[auxRelacional]=r;
				auxRelacional++;
			}
		}
		system("cls");
		
		printf("\n Paso 1\n");
		for(int j=0;j<nEntiRelac;j++){
			printf("%s=((", relacional[j].nombre);
			for(int i=0;i<relacional[j].num_PK;i++){
				printf("%s", relacional[j].LlavePrim[i]);
				if(i+1<relacional[j].num_PK)
					printf(", ");
			}
			printf(")(PK), ");
			for(int i=0;i<relacional[j].nAtri;i++){
				printf("%s", relacional[j].atributos[i]);
				if(i+1<relacional[j].nAtri)
					printf(", ");
			}
		printf(")\n");
		}
}
void Paso2(Enti *entidades, MRelac *relacional, Rela *relaciones){
	MRelac r; // estructura auxiliar
	int auxRelacional=nEntiRelac; 
	int AuxIndex;
		for(int i=0;i<nEnti;i++){
			if(entidades[i].tipo== 'D'){
				int auxC=0, count=0; 
				nEntiRelac++; 
				r.num_PK=0;
				strcpy(r.nombre, entidades[i].nombre);
				strcpy(r.LlavePrim[0], entidades[i].llavePrimaria);
				r.num_PK++;
				
				for(int j=0;j<NRelac;j++){
					if(strcmp(entidades[i].nombre, relaciones[j].Enti1)==0){ 
						for(int k=0;k<nEnti;k++){
							if(strcmp(relaciones[j].Enti2, entidades[k].nombre)==0){
								AuxIndex=k;
							}
						}
						r.num_PK++;
						strcpy(r.LlavePrim[1], entidades[AuxIndex].llavePrimaria); //se copia y se concatena para la PK Y FK
						strcat(r.LlavePrim[1], "(FK)");
					}
					if(strcmp(entidades[i].nombre, relaciones[j].Enti2)==0){
						for(int k=0;k<nEnti;k++){
							if(strcmp(relaciones[j].Enti1, entidades[k].nombre)==0){
								AuxIndex=k;
							}
						}
						r.num_PK++;
						strcpy(r.LlavePrim[1], entidades[AuxIndex].llavePrimaria);
						strcat(r.LlavePrim[1], "(FK)");
					}
				}
				for(int j=0;j<entidades[i].nAtri_simples;j++){
					strcpy(r.atributos[j], entidades[i].atributos_simples[j]);
					auxC++;
					count++;
				}
				
				for(int j=0;j<entidades[i].nAtri_comp;j++){
					for(int l=0, k=auxC;l<entidades[i].Acomp[j].nAtri;l++, k++){
						strcpy(r.atributos[k], entidades[i].Acomp[j].atributos_comp[l]);	
						count++;
					}
				}
				r.nAtri=count;
				relacional[auxRelacional]=r;
				auxRelacional++;
			}
		}
		
		printf("\n Paso 2\n");
		for(int j=0;j<nEntiRelac;j++){
			printf("%s=((", relacional[j].nombre);
			for(int i=0;i<relacional[j].num_PK;i++){
				printf("%s", relacional[j].LlavePrim[i]);
				if(i+1<relacional[j].num_PK)
					printf(", ");
			}
			printf(")(PK), ");
			for(int i=0;i<relacional[j].nAtri;i++){
				printf("%s", relacional[j].atributos[i]);
				if(i+1<relacional[j].nAtri)
					printf(", ");
			}
		printf(")\n");
		}
}
void Paso3(Enti *entidades, MRelac *relacional, Rela *relaciones){
	int AuxIndex;
	int AuxIndex2, AuxIndex3, AuxIndex4;
	for(int i=0; i<NRelac;i++){
		if(relaciones[i].PrimeraCard=='1' && relaciones[i].SegundaCard=='1'){
			if(relaciones[i].Partic1=='T' && relaciones[i].Partic2=='P'){
				for(int j=0;j<nEntiRelac;j++){//encuentra auxC de ent. a cambiar
					if(strcmp(relaciones[i].Enti1, relacional[j].nombre)==0)
						AuxIndex=j;
				}
				for(int j=0;j<nEnti;j++){//hallar auxC de ent. que relaciona
					if(strcmp(relaciones[i].Enti2, entidades[j].nombre)==0)
						AuxIndex2=j;
				}
				for(int j=0;j<nEnti;j++){//ent. a cambiar en estructura entidades
					if(strcmp(relaciones[i].Enti1, entidades[j].nombre)==0)
						AuxIndex3=j;
				}
				for(int j=0;j<nEntiRelac;j++){//obtener llave foranea de entidad relacionada
					if(strcmp(relaciones[i].Enti2, relacional[j].nombre)==0)
						AuxIndex4=j;
				}		
				
				if(entidades[AuxIndex3].tipo=='F'){
					int k=relacional[AuxIndex].nAtri; //Variable auxiliar
					relacional[AuxIndex].nAtri++;
					strcpy(relacional[AuxIndex].atributos[k], entidades[AuxIndex2].llavePrimaria);
					strcat(relacional[AuxIndex].atributos[k], "(FK)");
		        int p3=0;
					for(int j=0;j<relaciones[i].nAtri;j++){
						relacional[AuxIndex].nAtri++;
						p3= relacional[AuxIndex].nAtri-1;
						strcpy(relacional[AuxIndex].atributos[p3], relaciones[i].atributos[j]);
					}
				}
				else{
					int p3=0;
					for(int j=0;j<relaciones[i].nAtri;j++){
						relacional[AuxIndex].nAtri++;
						p3= relacional[AuxIndex].nAtri-1;
						strcpy(relacional[AuxIndex].atributos[p3], relaciones[i].atributos[j]);
					}
				}
			}
			
			else if(relaciones[i].Partic1=='P' && relaciones[i].Partic2=='T'){
				for(int j=0;j<nEntiRelac;j++){
					if(strcmp(relaciones[i].Enti2, relacional[j].nombre)==0)
						AuxIndex=j;
				}
				for(int j=0;j<nEnti;j++){
					if(strcmp(relaciones[i].Enti1, entidades[j].nombre)==0)
						AuxIndex2=j;
				}
				for(int j=0;j<nEnti;j++){
					if(strcmp(relaciones[i].Enti2, entidades[j].nombre)==0)
						AuxIndex3=j;
				}
				for(int j=0;j<nEntiRelac;j++){
					if(strcmp(relaciones[i].Enti1, relacional[j].nombre)==0)
						AuxIndex4=j;
				}	
				
				if(entidades[AuxIndex3].tipo=='F'){
					int k=relacional[AuxIndex].nAtri; //Variable auxiliar
					relacional[AuxIndex].nAtri++;
					strcpy(relacional[AuxIndex].atributos[k], entidades[AuxIndex2].llavePrimaria);
					strcat(relacional[AuxIndex].atributos[k], "(FK)");
					int p3=0;
					for(int j=0;j<relaciones[i].nAtri;j++){
						relacional[AuxIndex].nAtri++;
						p3= relacional[AuxIndex].nAtri-1;
						strcpy(relacional[AuxIndex].atributos[p3], relaciones[i].atributos[j]);
					}
				}
				else{

					int p3=0;
					for(int j=0;j<relaciones[i].nAtri;j++){
						relacional[AuxIndex].nAtri++;
						p3= relacional[AuxIndex].nAtri-1;
						strcpy(relacional[AuxIndex].atributos[p3], relaciones[i].atributos[j]);
					}
				}
			}
			else {
				for(int j=0;j<nEntiRelac;j++){
					if(strcmp(relaciones[i].Enti1, relacional[j].nombre)==0)
						AuxIndex=j;
				}
			
				for(int j=0;j<nEnti;j++){
					if(strcmp(relaciones[i].Enti2, entidades[j].nombre)==0)
						AuxIndex2=j;
				}
				for(int j=0;j<nEnti;j++){ 
					if(strcmp(relaciones[i].Enti1, entidades[j].nombre)==0)
						AuxIndex3=j;
				}
				for(int j=0;j<nEntiRelac;j++){
					if(strcmp(relaciones[i].Enti2, relacional[j].nombre)==0)
						AuxIndex4=j;
				}		
				if(entidades[AuxIndex3].tipo=='F'){
					int k=relacional[AuxIndex].nAtri; //Variable auxiliar
					relacional[AuxIndex].nAtri++;
					strcpy(relacional[AuxIndex].atributos[k], entidades[AuxIndex2].llavePrimaria);
					strcat(relacional[AuxIndex].atributos[k], "(FK)");
					
					int p3=0;
					for(int j=0;j<relaciones[i].nAtri;j++){
						relacional[AuxIndex].nAtri++;
						p3= relacional[AuxIndex].nAtri-1;
						strcpy(relacional[AuxIndex].atributos[p3], relaciones[i].atributos[j]);
					}
				}
				else{

					int p3=0;
					for(int j=0;j<relaciones[i].nAtri;j++){
						relacional[AuxIndex].nAtri++;
						p3= relacional[AuxIndex].nAtri-1;
						strcpy(relacional[AuxIndex].atributos[p3], relaciones[i].atributos[j]);
					}
				}	
			}
		}
	}
		
		printf("\n Paso 3\n");
		for(int j=0;j<nEntiRelac;j++){
			printf("%s=((", relacional[j].nombre);
			for(int i=0;i<relacional[j].num_PK;i++){
				printf("%s", relacional[j].LlavePrim[i]);
				if(i+1<relacional[j].num_PK)
					printf(", ");
			}
			printf(")(PK), ");
			for(int i=0;i<relacional[j].nAtri;i++){
				printf("%s", relacional[j].atributos[i]);
				if(i+1<relacional[j].nAtri)
					printf(", ");
			}
		printf(")\n");
		}
}
void Paso4(Enti *entidades, MRelac *relacional, Rela *relaciones){
	int AuxIndex;
	int AuxIndex2, AuxIndex3, AuxIndex4;
	for(int i=0; i<NRelac;i++){
		if(relaciones[i].PrimeraCard=='N' && relaciones[i].SegundaCard=='1'){
				for(int j=0;j<nEntiRelac;j++){
					if(strcmp(relaciones[i].Enti1, relacional[j].nombre)==0)
						AuxIndex=j;
				}
				for(int j=0;j<nEnti;j++){
					if(strcmp(relaciones[i].Enti2, entidades[j].nombre)==0)
						AuxIndex2=j;
				}
				for(int j=0;j<nEnti;j++){
					if(strcmp(relaciones[i].Enti1, entidades[j].nombre)==0)
						AuxIndex3=j;
				}
				for(int j=0;j<nEntiRelac;j++){
					if(strcmp(relaciones[i].Enti2, relacional[j].nombre)==0)
						AuxIndex4=j;
				}		
				if(entidades[AuxIndex3].tipo=='F'){
					int k=relacional[AuxIndex].nAtri; //Variable auxiliar
					relacional[AuxIndex].nAtri++;
					strcpy(relacional[AuxIndex].atributos[k], entidades[AuxIndex2].llavePrimaria);
					strcat(relacional[AuxIndex].atributos[k], "(FK)");
					
					int p4=0;
					for(int j=0;j<relaciones[i].nAtri;j++){
						relacional[AuxIndex].nAtri++;
						p4= relacional[AuxIndex].nAtri-1;
						strcpy(relacional[AuxIndex].atributos[p4], relaciones[i].atributos[j]);
					}
				}
				else{

					int p4=0;
					for(int j=0;j<relaciones[i].nAtri;j++){
						relacional[AuxIndex].nAtri++;
						p4= relacional[AuxIndex].nAtri-1;
						strcpy(relacional[AuxIndex].atributos[p4], relaciones[i].atributos[j]);
					}
				}
			}
			else if(relaciones[i].PrimeraCard=='1' && relaciones[i].SegundaCard=='N'){
				for(int j=0;j<nEntiRelac;j++){
					if(strcmp(relaciones[i].Enti2, relacional[j].nombre)==0)
						AuxIndex=j;
				}
				for(int j=0;j<nEnti;j++){
					if(strcmp(relaciones[i].Enti1, entidades[j].nombre)==0)
						AuxIndex2=j;
				}
				for(int j=0;j<nEnti;j++){
					if(strcmp(relaciones[i].Enti2, entidades[j].nombre)==0)
						AuxIndex3=j;
				}
				for(int j=0;j<nEntiRelac;j++){
					if(strcmp(relaciones[i].Enti1, relacional[j].nombre)==0)
						AuxIndex4=j;
				}	
				if(entidades[AuxIndex3].tipo=='F'){
					int k=relacional[AuxIndex].nAtri; //Variable auxiliar
					relacional[AuxIndex].nAtri++;
					strcpy(relacional[AuxIndex].atributos[k], entidades[AuxIndex2].llavePrimaria);
					strcat(relacional[AuxIndex].atributos[k], "(FK)");
					
					int p4=0;
					for(int j=0;j<relaciones[i].nAtri;j++){
						relacional[AuxIndex].nAtri++;
						p4= relacional[AuxIndex].nAtri-1;
						strcpy(relacional[AuxIndex].atributos[p4], relaciones[i].atributos[j]);
					}
				}
				else{

					int p4=0;
					for(int j=0;j<relaciones[i].nAtri;j++){
						relacional[AuxIndex].nAtri++;
						p4= relacional[AuxIndex].nAtri-1;
						strcpy(relacional[AuxIndex].atributos[p4], relaciones[i].atributos[j]);
					}
				}
			}
	}
		
		printf("\n Paso 4\n");
		for(int j=0;j<nEntiRelac;j++){
			printf("%s=((", relacional[j].nombre);
			for(int i=0;i<relacional[j].num_PK;i++){
				printf("%s", relacional[j].LlavePrim[i]);
				if(i+1<relacional[j].num_PK)
					printf(", ");
			}
			printf(")(PK), ");
			for(int i=0;i<relacional[j].nAtri;i++){
				printf("%s", relacional[j].atributos[i]);
				if(i+1<relacional[j].nAtri)
					printf(", ");
			}
		printf(")\n");
		}
}

void Paso5(Enti *entidades, MRelac *relacional, Rela *relaciones){
	int auxC1, auxC2;
	for(int i=0;i<NRelac;i++){
		if((relaciones[i].PrimeraCard == 'M' && relaciones[i].SegundaCard=='N') || (relaciones[i].PrimeraCard=='N' && relaciones[i].SegundaCard=='M')){
			int auxC3=nEntiRelac;
			nEntiRelac++;
			// recorre y halla la entidad 1 de la relación
			for(int j=0; j<nEnti;j++){
				if(strcmp(relaciones[i].Enti1, entidades[j].nombre)==0)
					auxC1=j;
			}
			// recorre y halla la entidad 1 de la relación
			for(int j=0; j<nEnti;j++){
				if(strcmp(relaciones[i].Enti2, entidades[j].nombre)==0)
					auxC2=j;
			}
			
			strcpy(relacional[auxC3].nombre, relaciones[i].nombre);
				relacional[auxC3].num_PK=2; 
				strcpy(relacional[auxC3].LlavePrim[0], entidades[auxC1].llavePrimaria);
				strcat(relacional[auxC3].LlavePrim[0], "(FK)");
			    strcpy(relacional[auxC3].LlavePrim[1], entidades[auxC2].llavePrimaria); 
			    strcat(relacional[auxC3].LlavePrim[1], "(FK)");
			
			int p5=0;
			//Se agregan los atributos
				for(int j=0;j<relaciones[i].nAtri;j++){
					relacional[auxC3].nAtri++;
					p5= relacional[auxC3].nAtri-1;
					strcpy(relacional[auxC3].atributos[p5], relaciones[i].atributos[j]);
				}
		}
		
	}
		
		printf("\n Paso 5\n");
		for(int j=0;j<nEntiRelac;j++){
			printf("%s=((", relacional[j].nombre);
			for(int i=0;i<relacional[j].num_PK;i++){
				printf("%s", relacional[j].LlavePrim[i]);
				if(i+1<relacional[j].num_PK)
					printf(", ");
			}
			printf(")(PK), ");
			for(int i=0;i<relacional[j].nAtri;i++){
				printf("%s", relacional[j].atributos[i]);
				if(i+1<relacional[j].nAtri)
					printf(", ");
			}
		printf(")\n");
		}
}
void Paso6(Enti *entidades, MRelac *relacional, Rela *relaciones){
	for(int i=0;i<nEnti;i++){
		for(int j=0;j<entidades[i].nAtri_multi;j++){
			int auxC1=nEntiRelac;
			nEntiRelac++;
			strcpy(relacional[auxC1].nombre, entidades[i].atributos_multi[j]);
			strcat(relacional[auxC1].nombre, "_");
			strcat(relacional[auxC1].nombre, entidades[i].nombre); 
			
			relacional[auxC1].num_PK=2;
			strcpy(relacional[auxC1].LlavePrim[0], entidades[i].atributos_multi[j]); 
			strcpy(relacional[auxC1].LlavePrim[1], entidades[i].llavePrimaria);  
			strcat(relacional[auxC1].LlavePrim[1], "(FK)");
		}
	}
		printf("\n Paso 6\n");
		for(int j=0;j<nEntiRelac;j++){
			printf("%s=((", relacional[j].nombre);
			for(int i=0;i<relacional[j].num_PK;i++){
				printf("%s", relacional[j].LlavePrim[i]);
				if(i+1<relacional[j].num_PK)
					printf(", ");
			}
			printf(")(PK), ");
			for(int i=0;i<relacional[j].nAtri;i++){
				printf("%s", relacional[j].atributos[i]);
				if(i+1<relacional[j].nAtri)
					printf(", ");
			}
		printf(")\n");
		}
}


