#include "material.h"
#include "malla.h"

Material::Material(){}

Material::Material(Tupla4f ambiente, Tupla4f especular, Tupla4f difuso, float brillo){
    this->ambiente = ambiente;
    this->especular = especular;
    this->difuso = difuso;
    this->brillo = brillo;
}

void Material::aplicar(){
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambiente);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,especular);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,difuso);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,brillo);
}