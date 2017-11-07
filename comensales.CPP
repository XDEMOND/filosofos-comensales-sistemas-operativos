@XDEMOND
#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>

#define fil 5

struct semaforo{
	int ciclo;
   bool sem;
   int s_c;
   semaforo *sig;
};
struct filosofo{
  int id;
  int estado;
  int comer;
  int pensar;
  filosofo *sig;
};
semaforo *p=NULL,	*q=NULL,	*aux=NULL,	*nuevo=NULL;
filosofo *pP=NULL,*qP=NULL,*auxP=NULL,	*nuevoP=NULL, *pI=NULL,*qI=NULL;
int filosofos = fil,ciclos = 1,i,tenedor;
bool semaforoBin[5],s_c,s_s;

void crearP(int num){
 	nuevoP 				= (filosofo*) malloc (sizeof(filosofo));
   nuevoP->id 			= num;
   nuevoP->estado 	= 0;
   nuevoP->pensar   	= rand()%6;
	nuevoP->comer 		= (rand()%4)+1;
   nuevoP->sig 		= NULL;
   if(pP==NULL){
   	pP = nuevoP;
      qP = nuevoP;
   }else{
   	qP->sig 	= nuevoP;
      qP 		= nuevoP;
   }
}

void intentando(int num){
 	nuevoP 				= (filosofo*) malloc (sizeof(filosofo));
   nuevoP->id 			= num;
   nuevoP->sig 		= NULL;
   if(pI==NULL){
   	pI = nuevoP;
      qI = nuevoP;
   }else{
   	qI->sig 	= nuevoP;
      qI 		= nuevoP;
   }
}

void mostrarP(){
   auxP = (filosofo*) malloc (sizeof(filosofo));
   auxP = pP;
   cout<<"FILOSOFO\t"<<endl;
   while(auxP!=NULL){
   	cout<<"F"<<auxP->id<<endl;
   	auxP = auxP->sig;
   }
}
void main(){
   cout<<endl<<"Tiempo\t";
   for(i = 1; i<=filosofos ;i++)
   	cout<<"F"<<i<<"\t";
   cout<<"\tSEMAFORO \tSeccion_Critica\tINTENTANDO"<<endl;
   auxP = (filosofo*) malloc (sizeof(filosofo));
   for(i=0;i<filosofos;i++){
   	semaforoBin[i] = true;
      crearP(i+1);
   }
   while(true){
   	s_c 		= false;
      s_s	  	= false;
      cout<<ciclos<<"\t";
      ciclos++;
   	auxP = pP;
	   while(auxP!=NULL){
      	auxP->pensar = auxP->pensar - 1;
         if(auxP->pensar == 0)
         	auxP->estado = 0;
         else if(auxP->pensar>0)
         	auxP->estado = 2;
      	switch(auxP->estado){
          	case 0:
            	cout<<"Wait(S)\t";
               if(auxP->id == filosofos)
               	tenedor = 0;
               else
               	tenedor = auxP->id;
               if(semaforoBin[auxP->id-1] == false || semaforoBin[tenedor] == false)
               	auxP->estado = 2;
               else{
               	auxP->estado	= 1;
                  semaforoBin[auxP->id-1] = false;
               	semaforoBin[tenedor] 	= false;
               }
               intentando(auxP->id);
            break;
            case 1:
            	s_c 		= true;
               cout<<"comer\t";
               if(auxP->id == filosofos)
               	tenedor = 0;
               else
               	tenedor = auxP->id;
               semaforoBin[auxP->id-1] = false;
               semaforoBin[tenedor] 	= false;
               if(auxP->comer == 0)
               	auxP->estado = 3;
               else
               	auxP->comer = auxP->comer-1;
            break;
            case 2:
             	cout<<"pensar\t";
            break;
            case 3:
               s_s = true;
               cout<<"S(S)\t";
               if(auxP->id == filosofos)
               	tenedor = 0;
               else
               	tenedor = auxP->id;
               semaforoBin[auxP->id-1] = true;
               semaforoBin[tenedor] 	= true;
               auxP->estado = 4;
            break;
            case 4:
            	cout<<"O.P.\t";
            break;
         }
   		auxP = auxP->sig;
   	}
      cout<<"\t";
      for(i = 0; i < filosofos ;i++)
      	cout<<semaforoBin[i]<<" ";
      cout<<"\t\t";
      if(s_c)
      	cout<<"F"<<pI->id<<"\t";
      else
         cout<<" -\t";
      auxP = pI;
	   while(auxP!=NULL){
         cout<<"F"<<auxP->id<<" ";
   		auxP = auxP->sig;
   	}
      if(s_s){
      	if(pI->sig==NULL)
         	break;
      	pI = pI->sig;
      	nuevoP = pP;
         while(nuevoP!=NULL){
         	if(nuevoP->id == pI->id)
            	break;
         	nuevoP = nuevoP->sig;
         }
      	nuevoP->estado = 1;
      }
      cout<<endl;
      getch();
   }
	getch();
}