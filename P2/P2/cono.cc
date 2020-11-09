#include "cono.h"

Cono::Cono(int num_instancias_perf, float h, float r){
	num_instancias = num_instancias_perf;

	aux.push_back( Tupla3f(r,0.0,0.0));
	aux.push_back( Tupla3f(0.0000001,h,0.0));



	tapas = true;


	crearMalla(aux,num_instancias);


}
