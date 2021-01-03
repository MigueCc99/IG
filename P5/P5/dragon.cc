#include "dragon.h"

Dragon::Dragon(){
    cuerpo = new Dragon_cuerpo();
    cuello = new Dragon_cuello();
    cabeza = new Dragon_cabeza();
    cola = new Dragon_cola();
    ala = new Dragon_ala();
    
    giro_cola = 0;
    giro_ala = 0;
    desplazamientoy = desplazamientoz = 0;
    rotacionx = 0;
}

void Dragon::draw(bool inmediato, GLenum tipo, int color){
    glPushMatrix();
        glTranslatef(0,desplazamientoy,desplazamientoz);
        glRotatef(rotacionx,1,0,0);
        cuerpo->draw(inmediato,tipo,color,false);
        glPushMatrix();
            glTranslatef(0,0,32);
            cuello->draw(inmediato,tipo,color,false);
            glTranslatef(0,0,50);
            cabeza->draw(inmediato,tipo,color,false);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,0,-30);
            glPushMatrix();
                glRotatef(giro_cola,0,1,0);
                cola->draw(inmediato,tipo,color,false);
            glPopMatrix();
            glTranslatef(13,0,5);
            glPushMatrix();
                glPushMatrix();
                    glRotatef(giro_ala,0,0,1);
                    ala->draw(inmediato,tipo,color);
                glPopMatrix();
                glRotatef(180,0,1,0);
                glTranslatef(25,0,-50);
                glPushMatrix();
                    glRotatef(giro_ala,0,0,1);
                    ala->draw(inmediato,tipo,color);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void Dragon::draw_ajedrez(bool inmediato){
    glPushMatrix();
        glTranslatef(0,desplazamientoy,desplazamientoz);
        glRotatef(rotacionx,1,0,0);
        cuerpo->draw_ajedrez(inmediato);
        glPushMatrix();
            glTranslatef(0,0,32);
            cuello->draw_ajedrez(inmediato);
            glTranslatef(0,0,50);
            cabeza->draw_ajedrez(inmediato);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,0,-30);
            glPushMatrix();
                glRotatef(giro_cola,0,1,0);
                cola->draw_ajedrez(inmediato);
            glPopMatrix();
            glTranslatef(13,0,5);
            glPushMatrix();
                glPushMatrix();
                    glRotatef(giro_ala,0,0,1);
                    ala->draw_ajedrez(inmediato);
                glPopMatrix();
                glRotatef(180,0,1,0);
                glTranslatef(25,0,-50);
                glPushMatrix();
                    glRotatef(giro_ala,0,0,1);
                    ala->draw_ajedrez(inmediato);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void Dragon::setMaterial(Material *mat){
    cuerpo->setMaterial(mat);
    cuello->setMaterial(mat);
    cabeza->setMaterial(mat);
    cola->setMaterial(mat);
    ala->setMaterial(mat);
}

void Dragon::modificarGiroCola(float valor){
	if (giro_cola + valor > -50 && giro_cola + valor < 50)
	giro_cola += valor;
}

void Dragon::modificarGiroAlas(float valor){
	if (giro_ala + valor > -60 && giro_ala + valor < 50)
		giro_ala += valor;
}

void Dragon::modificarDesplazamiento(float valory, float valorz){
	desplazamientoy += valory;
	desplazamientoz += valorz;
}

void Dragon::modificarRotacionx(float valor){
	rotacionx += valor;
}