#include "cuadro.h"

// Constructor por defecto
Cuadro::Cuadro()
{
    // Creamos la tabla de vértices
    Tupla3f v1(0.0, 0.0, 0.0), v2(100.0, 0.0, 0.0), v3(0.0, 100.0, 0.0), v4(100.0, 100.0, 0.0);
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);
    v.push_back(v4);

    // Creamos la tabla de triángulos
    Tupla3i t1(2, 0, 1), t2(1, 3, 2);
    f.push_back(t1);
    f.push_back(t2);

    // Creamos la tabla de colores
    Tupla3f c1(255, 0.0, 0.0), c2(255, 0.0, 0.0), c3(255, 0.0, 0.0), c4(255, 0.0, 0.0);
    c.push_back(c1);
    c.push_back(c2);
    c.push_back(c3);
    c.push_back(c4);
}

// Coordenadas de textura
void Cuadro::setCoordenadas()
{
    // Creamos la tabla de coordenadas
    Tupla2f co1(0.0, 0.0), co2(1, 0.0), co3(0.0, 1), co4(1, 1);
    this->ct.push_back(co1);
    this->ct.push_back(co3);
    this->ct.push_back(co2);
    this->ct.push_back(co4);
}