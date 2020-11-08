#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro()
{
   
   // inicializar la tabla de vértices
	v.resize(4);
	v[0]= Tupla3f (0,0,0);
	v[1]= Tupla3f (0,0,80);
	v[2]= Tupla3f (80,0,0);
	v[3]= Tupla3f (0,80,0);

   // inicializar la tabla de caras o triángulos:

	f.resize(4);
	f[0]= Tupla3i (0,2,1);
	f[1]= Tupla3i (2,3,1);
	f[2]= Tupla3i (1,3,0);
	f[3]= Tupla3i (3,2,0);

}

