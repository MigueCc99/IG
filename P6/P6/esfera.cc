#include "esfera.h"


Esfera::Esfera(int num_vert_perfil, int num_instancias_perf, float r){
	float eje_x, eje_y, alpha;

	num_instancias = num_instancias_perf;

	for (int i=1; i<num_vert_perfil; i++){
		alpha = (M_PI * i) /(num_vert_perfil);
		eje_x =  r * sin(alpha);
		eje_y = -r * cos(alpha)  ;
		aux.push_back( Tupla3f(eje_x, eje_y, 0) );
	}

	tapas = true;

    crearMalla(aux,num_instancias_perf);




}
