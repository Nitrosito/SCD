#include <iostream>
#include <cassert>
#include <pthread.h>
#include <semaphore.h>

using namespace std ;

// ---------------------------------------------------------------------
// constantes 
const unsigned 
  num_items  = 40 ,
  tam_vector = 10 ;              
// ---------------------------------------------------------------------
  int vector[tam_vector];
  int posicion_lectura=0;
  int posicion_escritura=0;

// ---------------------------------------------------------------------
// semaforos
  sem_t puede_escribir;
  sem_t puede_leer;
// ---------------------------------------------------------------------

unsigned producir_dato(){
  static int contador = 0 ;
  cout << "producido: " <<  contador << endl << flush ;
  return contador++ ;
}
// ---------------------------------------------------------------------

void consumir_dato( int dato ){
    cout << "dato recibido: " << dato << endl << flush;
}
// ---------------------------------------------------------------------

void * productor( void * ){   
  for( unsigned i = 0 ; i < num_items ; i++ ){ 
    int dato = producir_dato() ;
    sem_wait(&puede_escribir); //Comprobamos que queden huecos en el vector
    vector[posicion_escritura]=dato;

    if(posicion_escritura==tam_vector-1)
	posicion_escritura=0;
    else	
    	posicion_escritura++;
	
    sem_post(&puede_leer);
  }
  return NULL ;
}
// ---------------------------------------------------------------------

void * consumidor( void * ){   
  for( unsigned i = 0 ; i < num_items ; i++ ){   
    int dato ;
    sem_wait(&puede_leer);
    dato=vector[posicion_lectura];
    if(posicion_lectura==tam_vector-1)
	    posicion_lectura=0;
    else
	    posicion_lectura++;

    consumir_dato( dato );
    sem_post(&puede_escribir);
  }
  return NULL ;
}
//----------------------------------------------------------------------

int main(){

  pthread_t hebra_productor, hebra_consumidor;


  sem_init(&puede_escribir,0,tam_vector);
  sem_init(&puede_leer,0,0);


  pthread_create(&hebra_productor, NULL, productor,NULL);
  pthread_create(&hebra_consumidor,NULL, consumidor,NULL);

  pthread_join(hebra_productor,NULL);
  pthread_join(hebra_consumidor,NULL);

   return 0 ; 
}
