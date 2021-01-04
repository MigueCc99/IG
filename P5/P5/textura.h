#ifndef TEXTURA_H_INCLUDED
#define TEXTURA_H_INCLUDED

#include "aux.h"
#include "jpg_imagen.hpp"
#include "jpg_jinclude.h"

using namespace jpg;

class Textura{
    protected:
        GLuint textura_id = 0;
        unsigned char *data;
        Imagen *pimg = nullptr;
        unsigned int width, height;
        bool enabled = false;
    
    public:
        Textura();
        Textura(std::string archivo, GLuint id);
        void activar();
        inline GLuint getID(){ return this->textura_id; }
        inline unsigned int getWidth(){ return this->width; };
        inline unsigned int getHeight(){ return this->height; };
};

#endif