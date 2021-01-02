#include "cabezal.h"

Cabezal::Cabezal(){
    eje = new EjeRotatorio();
    c = new Cubo();
}
void Cabezal::drawCabezal(bool ajedrez, bool inmediato, GLenum tipo_dibujado_actual, int color, bool tapas){
    if(ajedrez){
        glPushMatrix();
            // Transformaciones y dibujado del cubo
            glTranslatef(0,-10,0);
            glScalef(75,20,20);
            c->draw_ajedrez(inmediato);
        glPopMatrix();
    }else{
        glPushMatrix();
            // Transformaciones y dibujado del cubo
            glTranslatef(0,-10,0);
            glScalef(75,20,20);
            c->draw(inmediato, tipo_dibujado_actual, color, false);
        glPopMatrix();
    }
        glPushMatrix();
            // Transformaciones y dibujado del eje rotatorio
            glTranslatef(-70,0,0);
            glRotatef(this->anguloRotacion,1,0,0);
            eje->drawEje(ajedrez,inmediato,tipo_dibujado_actual,color,tapas);
        glPopMatrix();
}


void Cabezal::setAngulo(float anguloRotacion){
    this->anguloRotacion = anguloRotacion;
}

void Cabezal::setMaterial(Material *m){
    eje->setMaterial(m);
    c->setMaterial(m);
}