#ifndef DRAGON_H_INCLUDED
#define DRAGON_H_INCLUDED

#include "aux.h"
#include "dragon_cuerpo.h"
#include "dragon_cuello.h"
#include "dragon_cabeza.h"
#include "dragon_cola.h"
#include "dragon_ala.h"

class Dragon{
    public:
    
    float giro_cuello, giro_cola, giro_ala, desplazamientoy, desplazamientoz, rotacionx;

    Dragon_cuerpo * cuerpo = nullptr;
    Dragon_cuello * cuello = nullptr;
    Dragon_cabeza * cabeza = nullptr;
    Dragon_cola * cola = nullptr;
    Dragon_ala * ala = nullptr;
    
    Dragon();

    void draw(bool inmediato, GLenum tipo, int color);
    void draw_ajedrez(bool inmediato);
    void setMaterial(Material *mat);

    void modificarGiroCuello(float valor);
    void modificarGiroCola(float valor);
    void modificarGiroAlas(float valor);
    void modificarDesplazamiento(float valory, float valorz);
    void modificarRotacionx(float valor);
};

#endif