#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "aux.h"

class Camara{
protected:
    Tupla3f eye;
    Tupla3f at;
    Tupla3f up;
    int tipo;       // ORTOGONAL o PERSPECTIVA
    float left, right, near, far, top, bottom;  // o bien aspect, fov, near, far;
public:
    Camara(Tupla3f eye, Tupla3f at, Tupla3f up, int tipo, float left, float right, float near, float far, float top, float bottom) ; // con los parametros necesarios
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

    Tupla3f getEye();
    Tupla3f getAt();
    Tupla3f getUp();
    float getLeft();
    float getRight();
    float getNear();
    float getFar();
    float getTop();
    float getBottom();

    void setEye(Tupla3f eye);
    void setAt(Tupla3f at);
    void setUp(Tupla3f up);
    void setLeft(float left);
    void setRight(float right);
    void setNear(float near);
    void setFar(float far);
    void setTop(float top);
    void setBottom(float bottom);
};
#endif