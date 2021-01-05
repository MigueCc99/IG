#include "aspa.h"

// Constructor por defecto
Aspa::Aspa(){
    cilindro = new Cilindro(10,50,100,10);
}

// Método drawAspa
void Aspa::drawAspa(bool ajedrez, bool inmediato, GLenum tipo_dibujado_actual, int color, bool tapas){
    
    if(ajedrez){
        glPushMatrix();
            glTranslatef(10,50,0);
            glScalef(2,2,2);
            cilindro->draw_ajedrez(inmediato,tapas);
        glPopMatrix();
    }else{
        glPushMatrix();
            glTranslatef(10,50,0);
            glScalef(2,2,2);
            cilindro->draw(inmediato, tipo_dibujado_actual, color, false, tapas);
        glPopMatrix();
    }
}

// Método para establecer el material
void Aspa::setMaterial(Material *m){
    cilindro->setMaterial(m);
}