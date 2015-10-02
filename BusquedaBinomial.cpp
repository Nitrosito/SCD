bool BusquedaBinomial(int* vector, int nelementos, int buscado){
	int inf, sup, centro;
	inf = 0;
	sup = nelementos-1;
	centro = ((sup-inf)/2)+inf;

	while(inf < sup){
		if(buscado == vector[centro])
			return true;
		else if(buscado < vector[centro])
			sup=centro -1;
		else
			inf = centro +1;	
	}
	return false;

}
