#ifndef _LUZDIRECCIONAL_H
#define _LUZDIRECCIONAL_H
#include "aux.h"
#include "luz.h"
#include "esfera.h"

class LuzDireccional : public Luz{
    protected:
        Esfera * esfera = nullptr;
        float alpha;
        float beta;
    public:
        // Construcción la fuente de luz
		LuzDireccional( Tupla2f direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso);

        void generarFuenteLuz();

        // Variación de ángulo
        void variarAnguloAlpha(float incremento) override;
        void variarAnguloBeta(float incremento) override;
        void calcularPosiciones();
};

#endif