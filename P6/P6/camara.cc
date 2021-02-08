#include "camara.h"

// Constructor por defecto
Camara::Camara(){};

// Constructor por parámetros
Camara::Camara(Tupla3f eye, Tupla3f at, Tupla3f up, int tipo, float alto, float ancho)
{
    this->eye = eye;
    this->at = at;
    this->up = up.normalized();
    this->tipo = tipo;
    this->left = alto/2;
    this->top = ancho/2;
    this->near = 50;
    this->far = 2500;
    this->fovY = atan(left/near)*(180/M_PI)*2;
    this->aspect = ancho/alto;

    // Vector director
    this->vectorDirector = at - eye;

    // Eje X. Producto vectorial entre el vector director y up.
    this->ejeX = vectorDirector.cross(up);
    this->ejeX = this->ejeX.normalized();

    // Eje Y. Producto vectorial entre ejeX y vector director.
    this->ejeY = ejeX.cross(vectorDirector);
    this->ejeY = this->ejeY.normalized();
}

// Rotar en X
void Camara::rotarXExaminar(float angle)
{
    rotarExaminar(angle, 'x');
}

// Rotar en Y
void Camara::rotarYExaminar(float angle)
{
    rotarExaminar(angle, 'y');
}

// Rotar en X en primera persona
void Camara::rotarXFirstPerson(float angle)
{
    rotarFirstPerson(angle, 'x');
}

// Rotar en Y en primera persona
void Camara::rotarYFirstPerson(float angle)
{
    rotarFirstPerson(angle, 'y');
}

// Trasladar la cámara
void Camara::mover(float x, float y, float z)
{
    this->eye = {x, y, z};
}

// Zoom en la escena
void Camara::zoom(float factor)
{   
    if(this->fovY-factor >= 1 && this->fovY-factor <= 180)
        this->fovY -= factor;

    this->left = tan((this->fovY/2)*(M_PI/180)) * this->near;
    this->top = this->left * this->aspect;
}

// Observador de la escena
void Camara::setObserver()
{
    gluLookAt(eye[0], eye[1], eye[2],
               at[0], at[1], at[2],
               up[0], up[1], up[2]);
}

// Proyección de la escena
void Camara::setProyeccion()
{
    if(this->tipo == 1)
        gluPerspective(fovY, aspect, near, far);
    
    else if(this->tipo == 0)
        glOrtho(-left, left, -top, top, near, far);
}

// Rotación en primera persona
void Camara::rotarFirstPerson(float angle, char eje)
{
    // Tuplas auxiliares
    Tupla3f newAt, newUp;

    // Vector dirección
    this->vectorDirector = at - eye;

    // Trabajamos mejor en radianes
    angle *= (M_PI/180);

    // Usamos la matriz de rotación
    if(eje == 'x'){
        newAt = matrizRotacion(ejeY, vectorDirector, angle);
        newUp = matrizRotacion(ejeY, up, angle);
        ejeX = matrizRotacion(ejeY, ejeX, angle);
    }

    else if(eje == 'y'){
        newAt = matrizRotacion(ejeX, vectorDirector, angle);
        newUp = matrizRotacion(ejeX, up, angle);
        ejeY = matrizRotacion(ejeX, ejeY, angle);        
    }

    // Cambiamos hacia donde estamos mirando
    this->at = newAt + eye;

    // Actualizamos Up
    this->up = newUp;
}

// Rotación en torno a un objeto
void Camara::rotarExaminar(float angle, char eje)
{
    // Tuplas auxiliares
    Tupla3f newAt, newUp, vD;

    // Vector dirección
    vD = eye - at;

    // Trabajamos mejor en radianes
    angle *= (M_PI/180);

    // Usamos la matriz de rotación
    if(eje == 'x'){
        vD = matrizRotacion(ejeY, vD, angle);
        newUp = matrizRotacion(ejeY, up, angle);
        ejeX = matrizRotacion(ejeY, ejeX, angle);
    }

    else if(eje == 'y'){
        vD = matrizRotacion(ejeX, vD, angle);
        newUp = matrizRotacion(ejeX, up, angle);
        ejeY = matrizRotacion(ejeX, ejeY, angle);        
    }

    // Cambiamos hacia donde estamos mirando
    this->eye = at + vD;

    // Actualizamos Up
    this->up = newUp;
}

// Matriz de rotación
Tupla3f Camara::matrizRotacion(Tupla3f eje, Tupla3f vec, float angle)
{
    Tupla3f res;

    res[0] = (cos(angle) + eje[0] * (eje[0] * (1-cos(angle)))) * vec[0] +
             (eje[0] * (eje[1] * (1-cos(angle))) - (eje[2]*sin(angle))) * vec[1] +
             (eje[0] * (eje[2] * (1-cos(angle))) + (eje[1]*sin(angle))) * vec[2];

    res[1] = (eje[1] * (eje[0] * (1-cos(angle))) + eje[2] * sin(angle)) * vec[0] +
             (cos(angle) + eje[1] * (eje[1] * (1-cos(angle)))) * vec[1] +
             (eje[1] * (eje[2] * (1-cos(angle))) - (eje[0]*sin(angle))) * vec[2];

    res[2] = (eje[2] * (eje[0] * (1-cos(angle))) - eje[1] * sin(angle)) * vec[0] +
             (eje[2] * (eje[1] * (1-cos(angle))) + (eje[0]*sin(angle))) * vec[1] +
             (cos(angle) + eje[2] * (eje[2] * (1-cos(angle)))) * vec[2];

    return res;
}