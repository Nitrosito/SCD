#include <iostream>
#include <cassert>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>      // incluye "time(....)"
#include <unistd.h>    // incluye "usleep(...)"
#include <stdlib.h>    // incluye "rand(...)" y "srand"

// ---------------------------------------------------------------------------
sem_t ingrediente[3];
sem_t estanco;
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
void *estanco_f(){
	while(true){
		//Espera a que un fumador recoga el ingrediente
		sem_wait(&estanco);
		//Genero ingrediente Aleatorio
		int random_number = rand() % 2 + 0;
		nombre_ingrediente[4]=random_number;
		cout << "He generado el ingrediente " << nombre_ingrediente[4] << endl << flush ;
		//Desbloqueo al fumador que le falta ese ingrediente
		sem_post(&ingrediente[random_number]);
	}
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Funcion que realizan los fumadores
void *fumador_f(void *id_fumador){
	    int idfumador = (int) id_fumador ; // número o índice de esta hebra
     	    nombre_ingrediente[id_fumador]=idfumador;

	while (true){
	   cout << "Soy el fumador " << id_fumador << " y estoy esperando el ingrediente " << nombre_ingrediente[id_fumador] << endl << flush;
	   //Espera a que se desbloquee su ingrediente
	   sem_wait(&ingrediente[id_fumador];
	   //Coge el ingrediente y se lo ""comunica"" a estanco
	   sem_post(&estanco);
	   cout << "Soy el fumador " << id_fumador << "y estoy comenzando a fumar " << endl << flush;
	   fumar();
	   cout << "Soy el fumador " << id_fumador << "y he acabado de fumar " << endl << flush;
   	}
}
// ----------------------------------------------------------------------------
int main(){
typedef enum  {Cerillas,Tabaco,Papel} nombre_ingrediente[4];

pthread_t fumador[3],estanco;
	// 0 Cerillas
	// 1 Tabaco
	// 2 Papel

  sem_init(&estanco,0,1);

  //Inicio a Estanco
  pthread_create(&estanco,NULL,&f_estanco,0);

  //Inicio a los fumadores y sus semaforos
  for(int i=0; i<3; i++){
	sem_init (&ingrediente[i],0,0);
	void *idfumador = (void *) i;
	pthread_create(&(fumador[i]),NULL,&fumador_f,idfumador;
  }

  pthread_join(estanco,NULL);

  return 0 ;
}
