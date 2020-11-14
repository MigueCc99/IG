#ifndef CONO_H_INCLUDED
#define CONO_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************

class Cono : public ObjRevolucion
{
   private:
	float altura, radio;
   public:
   Cono(int num_instancias_perf=20, float h=1.0, float r=1.0);

} ;




#endif
