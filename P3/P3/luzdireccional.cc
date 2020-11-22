#include "luzdireccional.h"
#include <cmath>

LuzDireccional::LuzDireccional( Tupla3f direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso){
    this->alpha = direccion[0];
    this->beta = direccion[1];

    this->id = idLuzOpenGL;
    this->colorAmbiente = colorAmbiente;
    this->colorEspecular = colorEspecular;
    this->colorDifuso = colorDifuso;

    calcularPosiciones();
    this->posicion[3] = 0;
}

void LuzDireccional::variarAnguloAlpha(float incremento){
    this->alpha += incremento;
    calcularPosiciones();
}

void LuzDireccional::variarAnguloBeta(float incremento){
    this->beta += incremento;
    calcularPosiciones();
}

void LuzDireccional::calcularPosiciones(){
    this->posicion[0] = sin(alpha*(M_PI/180));
    this->posicion[1] = sin(beta*(M_PI/180)); 
    this->posicion[2] = cos(alpha*(M_PI/180))*cos(beta*(M_PI/180));   
}