#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "aux.h"

class Camara{
protected:
    Tupla3f eye;
    Tupla3f at;
    Tupla3f up;

    bool rotando = false;

    int tipo;       // ORTOGONAL o PERSPECTIVA (ortogonal = 0, perspectiva = 1)
    float fovY, aspect, near, far, top, left;

    // Tuplas para el vector dirección y los ejes sobre la cámara
    Tupla3f vectorDirector;
    Tupla3f ejeX;
    Tupla3f ejeY;

    // Métodos relacionados con la matriz de rotación
    Tupla3f matrizRotacion(Tupla3f eje, Tupla3f vec, float angle);
    void rotarFirstPerson(float angle, char eje);
    void rotarExaminar(float angle, char eje);
public:
    // Constructores
    Camara();
    Camara(Tupla3f eye, Tupla3f at, Tupla3f up, int tipo, float alto, float ancho);
    
    // Métodos de rotación
    void rotarXExaminar(float angle);
    void rotarYExaminar(float angle);
    void rotarZExaminar(float angle);
    void rotarXFirstPerson(float angle);
    void rotarYFirstPerson(float angle);
    void rotarZFirstPerson(float angle);


    void mover(float x, float y, float z);
    void zoom(float factor);
    void setObserver();
    void setProyeccion();

    inline void setAt(Tupla3f punto){this->at = punto;};
    inline void setRotando(bool rot){this->rotando = rot;};
    inline bool getRotando(){return this->rotando;};
};
#endif