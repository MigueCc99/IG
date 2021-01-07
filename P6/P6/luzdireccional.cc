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
   Material *sol_material = new Material(Tupla4f(0.24725,0.1995,0.0745,1.0),Tupla4f(0.7516,0.60648,0.22648,1.0),Tupla4f(0.628281,0.555802,0.366065,1.0), 10.0);
   Material *suelo_tierra = new Material(Tupla4f(0.40, 0.26, 0.13,1.0),Tupla4f(0.40, 0.26, 0.13,1.0),Tupla4f(0.40, 0.26, 0.13,1.0),10.0);
   esfera = new Esfera();
   esfera->setMaterial(sol_material);
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