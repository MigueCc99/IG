#include "cilindro.h"

Cilindro::Cilindro(int num_vert_perfil, int num_instancias_perf, float h, float r){
	altura = h;
	radio = r;
	num_instancias = num_instancias_perf;
	tapas = true;

	aux.push_back( Tupla3f(r,0.0,r));
	aux.push_back( Tupla3f(r,h,r));

	crearMalla(aux,num_instancias_perf);



}

