#include "luz.h"

void Luz::activar(){
    glEnable(this->id);
    glLightfv( this->id,GL_POSITION, this->posicion );
    glLightfv( this->id,GL_AMBIENT, this->colorAmbiente );
    glLightfv( this->id,GL_DIFFUSE, this->colorDifuso );
    glLightfv( this->id,GL_SPECULAR, this->colorEspecular );
}

GLenum Luz::getID(){
    return this->id;
}