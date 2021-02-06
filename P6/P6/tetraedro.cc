#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro()
{
   
   	// inicializar la tabla de vértices
	Tupla3f v1(-50, -50, -50), v2(0, -50, 50), v3(50, -50, -50), v4(0, 50, 0);
	v.push_back(v1);
   	v.push_back(v2);
   	v.push_back(v3);
   	v.push_back(v4);
    
    // inicializar la tabla de caras o triángulos:
   	Tupla3i t1(0, 1, 3), t2(1, 2, 3), t3(2, 0, 3), t4(0, 2, 1);
   	f.push_back(t1);
   	f.push_back(t2);
   	f.push_back(t3);
   	f.push_back(t4);
}

