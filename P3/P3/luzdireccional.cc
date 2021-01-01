#include "luzdireccional.h"
#include <cmath>

LuzDireccional::LuzDireccional( Tupla2f direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso){
    this->alpha = direccion[0];
    this->beta = direccion[1];

    this->id = idLuzOpenGL;
    this->colorAmbiente = colorAmbiente;
    this->colorEspecular = colorEspecular;
    this->colorDifuso = colorDifuso;

    generarFuenteLuz();
    calcularPosiciones();
    this->posicion[3] = 0;
}

void LuzDireccional::generarFuenteLuz(){
   Tupla4f ambiente2(0.0215,	0.1745, 0.0215, 0.6), especular2(0.7038, 0.27048, 0.0828, 0.6), difuso2(0.0, 0.0, 0.0, 0.6);
   Material *m = new Material(difuso2, especular2, ambiente2, 0.01*128.0);
   esfera = new Esfera();
   esfera->setMaterial(m);
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

    glPushMatrix();
        esfera->draw(true, GL_FILL, 2, false, true);
        glScalef(20,20,20);
        glTranslatef(this->posicion[0], this->posicion[1], this->posicion[2]);
    glPopMatrix();
}