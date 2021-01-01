#include "molino.h"
        
Molino::Molino(){
    cabezal = new Cabezal();
    plataforma = new Cubo();
    soporte = new Cilindro(50,80,10);
}
void Molino::drawMolino(bool ajedrez, bool inmediato, GLenum tipo_dibujado_actual, int color, bool tapas){
    if(ajedrez){
        glPushMatrix();
            // Transformaciones y dibujado del soporte
            soporte->draw_ajedrez(inmediato, tapas);
        glPopMatrix();
        glPushMatrix();
            // Transformaciones y dibujado de la plataforma
            glScalef(1, 0.1, 1);
            plataforma->draw_ajedrez(inmediato);
        glPopMatrix();
    }else{
        glPushMatrix();
            // Transformaciones y dibujado del soporte
            soporte->draw(inmediato, tipo_dibujado_actual, color, false, tapas);
        glPopMatrix();
        glPushMatrix();
            // Transformaciones y dibujado de la plataforma
            glScalef(1, 0.1, 1);
            plataforma->draw(inmediato, tipo_dibujado_actual, color, false);
        glPopMatrix();
    }
        glPushMatrix();
            glPushMatrix();
                // Transformaciones y dibujado del soporte
                glTranslatef(0, altura, 0);
                if(ajedrez)
                    soporte->draw_ajedrez(inmediato, tapas);
                else
                    soporte->draw(inmediato, tipo_dibujado_actual, color, false, tapas);
            glPopMatrix();
            
            // Transformaciones y dibujado del cabezal
            glTranslatef(0, 80+altura, 0);
            glScalef(0.20, 0.20, 0.20);
            glRotatef(this->rotacionCabezalZ, 0, 0, 1);
            glRotatef(this->rotacionCabezalY, 0, 1, 0);
            cabezal->drawCabezal(ajedrez,inmediato,tipo_dibujado_actual,color,tapas);
        glPopMatrix();
}
void Molino::setAnguloCabezalY(float angulo){
    this->rotacionCabezalY = angulo;
}

void Molino::setAnguloCabezalZ(float angulo){
    this->rotacionCabezalZ = angulo;
}

void Molino::setMaterial(Material *m){
    soporte->setMaterial(m);
    plataforma->setMaterial(m);
    cabezal->setMaterial(m);
}
void Molino::setRotacionEje(float angulo){
    cabezal->setAngulo(angulo);
}
void Molino::setAltura(float altura){
    this->altura = altura;
}