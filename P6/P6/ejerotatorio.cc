#include "ejerotatorio.h"      
        
EjeRotatorio::EjeRotatorio(){
    aspa1 = new Aspa();
    aspa2 = new Aspa();
    aspa3 = new Aspa();
    esfera = new Esfera(50,50,1);
}
void EjeRotatorio::drawEje(bool ajedrez, bool inmediato, GLenum tipo_dibujado_actual, int color, bool tapas){
    if(ajedrez){
        glPushMatrix();
            // Transformaciones y dibujado de la esfera
            glScalef(75,75,75);
            esfera->draw_ajedrez(inmediato,tapas);
        glPopMatrix();
    }else{
        glPushMatrix();
            // Transformaciones y dibujado de la esfera
            glScalef(75,75,75);
            esfera->draw(inmediato, tipo_dibujado_actual, color, false, tapas);
        glPopMatrix();
    }
        glPushMatrix();
            // Transformaciones y dibujado de la aspa 1
            aspa1->drawAspa(ajedrez, inmediato, tipo_dibujado_actual, color, tapas);
        glPopMatrix();
        glPushMatrix();
            // Transformaciones y dibujado de la aspa 2
            glRotatef(230.0,1,0,0);
            aspa2->drawAspa(ajedrez, inmediato, tipo_dibujado_actual, color, tapas);
        glPopMatrix();
        glPushMatrix();
            // Transformaciones y dibujado de la aspa 3
            glRotatef(-230.0, 1, 0, 0);
            aspa3->drawAspa(ajedrez, inmediato, tipo_dibujado_actual, color, tapas);
        glPopMatrix();
}

void EjeRotatorio::setMaterial(Material *m){
  aspa1->setMaterial(m);
  aspa2->setMaterial(m);
  aspa3->setMaterial(m);
  esfera->setMaterial(m);
}