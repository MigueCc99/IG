#ifndef DRAGON_ALA_H_INCLUDED
#define DRAGON_ALA_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "cubo.h"

class Dragon_ala : public Malla3D
{
    public:

    Cubo * ala_interna = nullptr;
    Cubo * ala_externa = nullptr;

    Dragon_ala();

    void draw(bool inmediato, GLenum tipo, int color);
    void draw_ajedrez(bool inmediato);
    void setMaterial(Material * mat);

};

#endif