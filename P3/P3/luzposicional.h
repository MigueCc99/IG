#ifndef _LUZPOSICIONAL_H
#define _LUZPOSICIONAL_H
#include "aux.h"
#include "luz.h"

class LuzPosicional : public Luz{
	public:
		LuzPosicional( Tupla3f posicion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso);
		void setPosicion( Tupla3f posicion );
};
#endif