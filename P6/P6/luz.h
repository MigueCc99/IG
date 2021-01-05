#ifndef _LUZ_H
#define _LUZ_H

#include "aux.h"

class Luz{
    protected:
        Tupla4f posicion;
        Tupla4f colorAmbiente;
        Tupla4f colorDifuso;
        Tupla4f colorEspecular;
        GLenum id;
    public:
        Luz(){};
        void activar();
        virtual void variarAnguloAlpha(float incremento){};
        virtual void variarAnguloBeta(float incremento){};
        virtual void setPosicion(Tupla3f posicion){};
        GLenum getID();
};

#endif