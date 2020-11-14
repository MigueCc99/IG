#ifndef CILINDRO_H_INCLUDED
#define CILINDRO_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************

class Cilindro : public ObjRevolucion
{
   private:
	float altura, radio;
   public:
   Cilindro(int num_vert_perfil=10, int num_instancias_perf=20, float h=1.0, float r=1.0);
} ;




#endif
