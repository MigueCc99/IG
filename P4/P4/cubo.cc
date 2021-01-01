#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{

   // inicializar la tabla de vértices
   v.resize(8);
	v[0] = Tupla3f (0,0,0);
	v[1] = Tupla3f (0,0,lado);
	v[2] = Tupla3f (0,lado,0);
	v[3] = Tupla3f (0,lado,lado);
	v[4] = Tupla3f (lado,0,0);
	v[5] = Tupla3f (lado,0,lado);
	v[6] = Tupla3f (lado,lado,0);
	v[7] = Tupla3f (lado,lado,lado);

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
	f.resize(12);
	f[5] = Tupla3i (7,1,5);
	f[4] = Tupla3i (7,3,1);
	f[11] = Tupla3i (0,2,4);
	f[10] = Tupla3i (2,6,4);
	f[6] = Tupla3i (7,5,6);
	f[7] = Tupla3i (5,4,6);
	f[3] = Tupla3i (0,1,3);
	f[2] = Tupla3i (0,3,2);
	f[0] = Tupla3i (2,3,6);
	f[1] = Tupla3i (3,7,6);
	f[9] = Tupla3i (5,0,4);
	f[8] = Tupla3i (5,1,0);

}

