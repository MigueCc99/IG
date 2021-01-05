#include "camara.h"
#include "aux.h"

Camara::Camara(Tupla3f eye, Tupla3f at, Tupla3f up, int tipo, float left, float right, float near, float far, float top, float bottom){
  this->eye = eye;
  this->at = at;
  this->up = up;
  this->tipo = tipo;
  this->left = left;
  this->right = right;
  this->near = near;
  this->far = far;
  this->top = top;
  this->bottom = bottom;
}
void Camara::rotarXExaminar(float angle){
  eye = eye - at;

  float eje_y = cos(angle)*eye(1) - sin(angle)*eye(2);
  float eje_z = sin(angle)*eye(1) + cos(angle)*eye(2);

  eye(1) = eje_y; eye(2) = eje_z;

  eye = eye + at;
}
void Camara::rotarYExaminar(float angle){
  eye = eye - at;

  float eje_x = cos(angle)*eye(0) + sin(angle)*eye(2);
  float eje_z = -sin(angle)*eye(0) + cos(angle)*eye(2);

  eye(0) = eje_x; eye(2) = eje_z;

  eye = eye + at;
}
void Camara::rotarZExaminar(float angle){
  eye = eye - at;

  float eje_x = cos(angle)*eye(0) - sin(angle)*eye(1);
  float eje_y = sin(angle)*eye(0) + cos(angle)*eye(1);

  eye(0) = eje_x; eye(1) = eje_y;

  eye = eye + at;
}
void Camara::rotarXFirstPerson(float angle){
  at = at - eye;

  float eje_y = cos(angle)*at(1) - sin(angle)*at(2);
  float eje_z = sin(angle)*at(1) + cos(angle)*at(2);

  at(1) = eje_y; at(2) = eje_z;

  at = at + eye;
}
void Camara::rotarYFirstPerson(float angle){
  at = at - eye;

  float eje_x = cos(angle)*at(0) + sin(angle)*at(2);
  float eje_z = -sin(angle)*at(0) + cos(angle)*at(2);

  at(0) = eje_x; at(2) = eje_z;

  at = at + eye;
}
void Camara::rotarZFirstPerson(float angle){
  at = at - eye;

  float eje_x = cos(angle)*at(0) - sin(angle)*at(1);
  float eje_y = sin(angle)*at(0) + cos(angle)*at(1);

  at(0) = eje_x; at(1) = eje_y;
}
void Camara::mover(float x,float y,float z){}
void Camara::zoom(float factor){
  right = right*factor;
  left = left*factor;
  top = top * factor;
  bottom = bottom * factor;
}

void Camara::setObserver(){
  gluLookAt(eye(0),eye(1),eye(2),at(0),at(1),at(2),up(0),up(1),up(2));
}

void Camara::setProyeccion(){
  switch (tipo){
    case 0:
      glOrtho(left,right,bottom,top,near,far);
      break;
    case 1:
      glFrustum(left,right,bottom,top,near,far);
  }
}

Tupla3f Camara::getEye(){
  return eye;
}
Tupla3f Camara::getAt(){
  return at;
}
Tupla3f Camara::getUp(){
  return up;
}
float Camara::getLeft(){
  return left;
}
float Camara::getRight(){
  return right;
}
float Camara::getNear(){
  return near;
}
float Camara::getFar(){
  return far;
}
float Camara::getTop(){
  return top;
}
float Camara::getBottom(){
  return bottom;
}

void Camara::setEye(Tupla3f eye){
  this->eye = eye;
}
void Camara::setAt(Tupla3f at){
  this->at = at;
}
void Camara::setUp(Tupla3f up){
  this->up = up;
}
void Camara::setLeft(float left){
  this->left = left;
}
void Camara::setRight(float right){
  this->right = right;
}
void Camara::setNear(float near){
  this->near = near;
}
void Camara::setFar(float far){
  this->far = far;
}
void Camara::setTop(float top){
  this->top = top;
}
void Camara::setBottom(float bottom){
  this->bottom = bottom;
}
