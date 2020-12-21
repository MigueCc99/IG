#include "cono.h"

Cono::Cono(int num_instancias_perf, float h, float r){
	num_instancias = num_instancias_perf;

	aux.push_back( Tupla3f(0,r,0));
	aux.push_back( Tupla3f(0,0,h));

	tapas = true;


	crearMalla(aux,num_instancias);


}
