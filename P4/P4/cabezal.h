#ifndef CABEZAL_H_INCLUDED
#define CABEZAL_H_INCLUDED

#include "aux.h"
#include "ejerotatorio.h"
#include "cubo.h"

class Cabezal : public ObjRevolucion{
    private:
        EjeRotatorio *eje = nullptr;
        Cubo *c = nullptr;

        Material *mat = nullptr;
        float anguloRotacion = 0.0;
    public:
        Cabezal();
        void drawCabezal(bool ajedrez, bool inmediato, GLenum tipo_dibujado_actual, int color, bool tapas);
        void setAngulo(float anguloRotacion);
        void setMaterial(Material *m);
};

#endif