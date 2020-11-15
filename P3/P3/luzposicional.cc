#include "luzposicional.h"

LuzPosicional::LuzPosicional( Tupla3f posicion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso){

	this->posicion = Tupla4f(posicion(0), posicion(1), posicion(2), 1.0);
	id = idLuzOpenGL;
	this->colorAmbiente = colorAmbiente;
	this->colorDifuso = colorDifuso;
	this->colorEspecular = colorEspecular;

}