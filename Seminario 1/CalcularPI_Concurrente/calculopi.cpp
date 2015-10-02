// *********************************************************************
// SCD. Ejemplos del seminario 1.
//
// Plantilla para el ejercicio de cálculo de PI
// *********************************************************************

#include <iostream>
#include <pthread.h>

using namespace std ;

// ---------------------------------------------------------------------
// constante y variables globales (compartidas entre hebras)

const unsigned long m = long(1024)*long(1024) ;  // número de muestras (un millón)
const unsigned n      = 4 ;                      // número de hebras
int corresponde = m/n;
double resultado_parcial[n] ; // tabla de sumas parciales (una por hebra)

// ---------------------------------------------------------------------
// implementa función $f$

double f( double x ){ 
   return 4.0/(1+x*x) ;     // $~~~~f(x)\,=\,4/(1+x^2)$
}
// ---------------------------------------------------------------------
// cálculo secuencial

double calcular_integral_secuencial( ){  
   double suma = 0.0 ;                      // inicializar suma
   for( unsigned long i = 0 ; i < m ; i++ ) // para cada $i$ entre $0$ y $m-1$
      suma += f( (i+0.5)/m );               // $~~~~~$ añadir $f(x_i)$ a la suma actual

   return suma/m ;                          // devolver valor promedio de $f$

}
// ---------------------------------------------------------------------
// función que ejecuta cada hebra

void * funcion_hebra( void * ih_void ){  
   unsigned long ih = (unsigned long) ih_void ; // número o índice de esta hebra
   double sumap = 0.0 ;
   // calcular suma parcial en "sumap"
   for(unsigned int i=corresponde*ih ; i < (ih+1)*corresponde ; i++)
	sumap+= f((i+0.5)/m);
   
   resultado_parcial[ih] = sumap; // guardar suma parcial en vector.
   return NULL ;
}
// ---------------------------------------------------------------------
// cálculo concurrente

double calcular_integral_concurrente( ){  
	pthread_t hebras[n];
	double resultado=0;

   // crear y lanzar $n$ hebras, cada una ejecuta "funcion\_concurrente"
	for(unsigned long i=0; i < n ; i++){
		void * numero = (void *) i;
		pthread_create(&(hebras[i]),NULL,&funcion_hebra,numero);		
	}
   // esperar (join) a que termine cada hebra, sumar su resultado
	for(unsigned int i=0; i < n ; i++)
		pthread_join(hebras[i],NULL);
   // devolver resultado completo
   	for(unsigned int i =0 ; i <n ; i++)
		resultado+=resultado_parcial[i];
   // Devolucion
   return resultado/m;
}

// ---------------------------------------------------------------------

int main(){
   
   cout << "Ejemplo 4 (cálculo de PI)" << endl ;
   double pi_sec = 0.0, pi_conc = 0.0 ;
   
   pi_sec  = calcular_integral_secuencial() ;
   pi_conc = calcular_integral_concurrente() ;
   
   cout << "valor de PI (calculado secuencialmente)  == " << pi_sec  << endl 
        << "valor de PI (calculado concurrentemente) == " << pi_conc << endl ; 
    
   return 0 ;
}
// ---------------------------------------------------------------------



// ----------------------------------------------------------------------------
