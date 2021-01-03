#include "dragon_ala.h"
#include "ply_reader.h"

Dragon_ala::Dragon_ala(){
    ala_interna = new Cubo(50);
    ala_externa = new Cubo(50);
}

void Dragon_ala::draw(bool inmediato, GLenum tipo, int color){
    glPushMatrix();
        glPushMatrix();
            glRotatef(30,0,0,1);
            glScalef(1,0.1,1);
            ala_interna->draw(inmediato,tipo,color,false);
        glPopMatrix();

		glTranslatef(40,25,0);
		glRotatef(-30,0,0,1);
		glScalef(1,0.1,1);
        ala_externa->draw(inmediato,tipo,color,false);
    glPopMatrix();
}

void Dragon_ala::draw_ajedrez(bool inmediato){
	glPushMatrix();
		glPushMatrix();
			glRotatef(30,0,0,1);
			glScalef(1,0.1,1);
			ala_interna->draw_ajedrez(inmediato);
		glPopMatrix();

		glTranslatef(40,25,0);
		glRotatef(-30,0,0,1);
		glScalef(1,0.1,1);
		ala_externa->draw_ajedrez(inmediato);
	glPopMatrix();
}

void Dragon_ala::setMaterial(Material * mat){
	ala_interna->setMaterial(mat);
	ala_externa->setMaterial(mat);
}
