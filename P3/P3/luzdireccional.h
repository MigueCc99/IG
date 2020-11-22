#ifndef _LUZDIRECCIONAL_H
#define _LUZDIRECCIONAL_H
#include "aux.h"
#include "luz.h"

class LuzDireccional : public Luz{
    protected:
        float alpha;
        float beta;
    public:
        // Construcción la fuente de luz
		LuzDireccional( Tupla3f direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso);

        // Variación de ángulo
        void variarAnguloAlpha(float incremento) override;
        void variarAnguloBeta(float incremento) override;
        void calcularPosiciones();
};

#endif