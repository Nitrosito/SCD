#include <iostream>
#include <cassert>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>      // incluye "time(....)"
#include <unistd.h>    // incluye "usleep(...)"
#include <stdlib.h>    // incluye "rand(...)" y "srand"
using namespace std;
// ---------------------------------------------------------------------------
sem_t ingrediente[3];
sem_t mutex;
sem_t estanco;
string nombre_ingrediente[3];
// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
// función que simula la acción de fumar  como un retardo aleatorio de la hebra
void fumar() { 
   //  inicializa la semilla aleatoria  (solo la primera vez)
   static bool primera_vez = true ;
   if ( primera_vez ){
      primera_vez = false ;
      srand( time(NULL) );    
   }
   
   // calcular un numero aleatorio de milisegundos (entre 1/10 y 2 segundos)
   const unsigned miliseg = 100U + (rand() % 1900U) ; 

   // retraso bloqueado durante 'miliseg' milisegundos
   usleep( 1000U*miliseg ); 
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Funcion que realiza el estanco
void *estanco_f(void*){
	while(true){
		//Espera a que un fumador recoga el ingrediente
		sem_wait(&estanco);
		//Genero ingrediente Aleatorio
		int random_number = rand() % 3 + 0;

     		sem_wait(&mutex);
		cout << "He generado el ingrediente " << nombre_ingrediente[random_number] << endl << flush ;
	        sem_post(&mutex);

		//Desbloqueo al fumador que le falta ese ingrediente
		sem_post(&ingrediente[random_number]);
	}
	return NULL;
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Funcion que realizan los fumadores
void *fumador_f(void *id_fumador){
	   unsigned long idfumador = (unsigned long) id_fumador ; // número o índice de esta hebra
	   while (true){
    	   sem_wait(&mutex);
	   cout << "Soy el fumador " << id_fumador << " y estoy esperando el ingrediente " << nombre_ingrediente[idfumador] << endl << flush;
	   sem_post(&mutex);

	   //Espera a que se desbloquee su ingrediente
	   sem_wait(&ingrediente[idfumador]);
	   //Coge el ingrediente y se lo ""comunica"" a estanco
	   sem_post(&estanco);

    	   sem_wait(&mutex);
	   cout << "Soy el fumador " << idfumador << " y estoy comenzando a fumar " << endl << flush;
	   sem_post(&mutex);

	   fumar();

    	   sem_wait(&mutex);
	   cout << "Soy el fumador " << idfumador << " y he acabado de fumar " << endl << flush;
	   sem_post(&mutex);
   	}
	   return NULL;
}
// ----------------------------------------------------------------------------
int main(){
nombre_ingrediente[0]="Cerillas";
nombre_ingrediente[1]="Tabaco";
nombre_ingrediente[2]="Papel";
pthread_t fumador[3],estancot;
	// 0 Cerillas
	// 1 Tabaco
	// 2 Papel

  sem_init(&estanco,0,1);
  sem_init(&mutex,0,1);

  //Inicio a Estanco
  pthread_create(&estancot,NULL,&estanco_f,NULL);

  //Inicio a los fumadores y sus semaforos
  for(unsigned int i=0; i<3; i++){
	sem_init (&ingrediente[i],0,0);
	void *idfumador = (void *) i;
	pthread_create(&(fumador[i]),NULL,&fumador_f,idfumador);
  }

  pthread_join(estancot,NULL);
  for(int i=0; i <3; i++)
	  pthread_join(fumador[i],NULL);
  

  return 0 ;
}
