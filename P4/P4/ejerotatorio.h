#ifndef EJEROTATORIO_H_INCLUDED
#define EJEROTATORIO_H_INCLUDED
#include "aux.h"
#include "esfera.h"
#include "aspa.h"

class EjeRotatorio : public ObjRevolucion{
    private:
        Aspa *aspa1 = nullptr;
        Aspa *aspa2 = nullptr;
        Aspa *aspa3 = nullptr;
        Esfera *esfera = nullptr;

        Material *mat = nullptr;
    public:
        EjeRotatorio();
        void drawEje(bool ajedrez, bool inmediato, GLenum tipo_dibujado_actual, int color, bool tapas);
        void setMaterial(Material *m);
};

#endif