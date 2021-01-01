#ifndef ASPA_H_INCLUDED
#define ASPA_H_INCLUDED

#include "aux.h"
#include "cilindro.h"
#include "material.h"
#include "cono.h"

class Aspa : public ObjRevolucion{
    private:
        Cilindro *cilindro = nullptr;
        Material *mat = nullptr;
    public:
    Aspa();
    void drawAspa(bool ajedrez, bool inmediato, GLenum tipo_dibujado_actual, int color, bool tapas);
    void setMaterial(Material *m);
};

#endif