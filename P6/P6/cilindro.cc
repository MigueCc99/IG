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

void Cilindro::setCoordenadas(){
	float h= 0.0, alfa = 0.0, u_text = 0.0, v_text = 0.0;
	for (int i=0; i<v.size()-2; i++){
		alfa = atan2(v[i](2),v[i](0));
		h = v[i](1);

		u_text = 1/2 + (alfa)/(2*M_PI);
		v_text = (h)/altura;


		ct.push_back(Tupla2f(u_text,v_text));
	}
}