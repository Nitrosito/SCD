#include <iostream>
#include <cassert>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>      // incluye "time(....)"
#include <unistd.h>    // incluye "usleep(...)"
#include <stdlib.h>    // incluye "rand(...)" y "srand"

// ----------------------------------------------------------------------------
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

// falta: resto de funciones 
// ..............

// ----------------------------------------------------------------------------

int main(){
	// 0 Estanco
	// 1 Cerillas
	// 2 Tabaco
	// 3 Papel
  pthread_t fumador[4];

  //Inicio a los fumadores
  for(int i=0; i<3; i++){
	void *idIngrediente = (void *) i;
	pthread_create(&(fumador[i]),NULL,&fumador,idIngrediente;
  }
	

  return 0 ;
}
