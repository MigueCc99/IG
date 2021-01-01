#ifndef MOLINO_H_INCLUDED
#define MOLINO_H_INCLUDED

#include "aux.h"
#include "cabezal.h"
#include "material.h"

class Molino : public ObjRevolucion{
    private:
        Cabezal *cabezal = nullptr;
        Cubo *plataforma = nullptr;
        Cilindro *soporte = nullptr;

        Material *mat = nullptr;

        float rotacionCabezalY = 0.0;
        float rotacionCabezalZ = 0.0;
        float altura = 0.0;
    public:
        Molino();
        void drawMolino(bool ajedrez, bool inmediato, GLenum tipo_dibujado_actual, int color, bool tapas);
        void setAnguloCabezalY(float angulo);
        void setAnguloCabezalZ(float angulo);
        void setMaterial(Material *m);
        void setRotacionEje(float angulo);
        void setAltura(float altura);
};

#endif