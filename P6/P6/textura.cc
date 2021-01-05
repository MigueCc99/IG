#include "textura.h"

using namespace jpg;

// Constructor por defecto
Textura::Textura(){};

// Constructor por parámetro
Textura::Textura(std::string archivo, GLuint id){
    this->textura_id = id;

    glGenTextures(1, &textura_id);

    // Cargamos la img
    if(this->pimg == nullptr)
        this->pimg = new Imagen(archivo);
    
    // Asignamos columnas y filas
    this->width = pimg->tamX();
    this->height = pimg->tamY();

    // Leemos los texels
    this->data = pimg->leerPixels();
}

// Funcion activar
void Textura::activar(){
    // Identificador de la textura activa
    glBindTexture(GL_TEXTURE_2D, textura_id);

    // Cuando está la iluminación activada
    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);

    // Cómo se selecciona el texel o texels a partir de una coordenada de textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Entorno para las texturas
    // glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    // Para coordenadas fuera del rango {[0,0], [1,1]}
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if(!enabled){
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
        enabled = true;        
    }
}