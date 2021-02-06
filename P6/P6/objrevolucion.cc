#include "aux.h"
#include "objrevolucion.h"
#include <cmath>
#include <algorithm>
#include "ply_reader.h"




// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapas) {
    ply::read_vertices(archivo,aux);
    this->num_instancias = num_instancias;
    this->tapas = tapas;


    crearMalla(aux,num_instancias);

}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> perfil, int num_instancias, bool tapas) {
    crearMalla(perfil,num_instancias);
    this->tapas = tapas;
    this->num_instancias = num_instancias;
    if (tapas){
        this->crearTapaInferior();
        this->crearTapaSuperior();
    }
}

std::vector<Tupla3f> ObjRevolucion::voltearVertices(const std::vector<Tupla3f> &perfil_original){
   std::vector<Tupla3f> volteado, aux = perfil_original;
   volteado.reserve(perfil_original.size());

   for(int i=0; i<perfil_original.size(); i++){
      volteado.push_back(aux.back());
      aux.pop_back();
   }

   return volteado;
}

void ObjRevolucion::crearTapaSuperior(){

    for (int i=0; i<num_instancias; i++){
        f.push_back( Tupla3i(v.size()-2,aux.size()*(i+1)-1,aux.size()*(((i+1)%num_instancias)+1)-1)) ;
    }

}

void ObjRevolucion::crearTapaInferior(){

    for (int i=0; i<num_instancias; i++){
        f.push_back( Tupla3i(v.size()-1,((i+1)%num_instancias)*aux.size(),i*aux.size()));
    }

}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias) {
   float alpha;
   float eje_x, eje_z;
   bool primero=false, ultimo=false;
	Tupla3f primer_punto;
	Tupla3f ultimo_punto;

   // Probamos a cambiar el orden del perfil_original
   //std::reverse(perfil_original.begin(), perfil_original.end());

   // Volteamos los vértices si están en orden ascendente
   std::vector<Tupla3f> perfil = (perfil_original[0](1) > perfil_original[perfil_original.size()-1](1)) ? voltearVertices(perfil_original) : perfil_original;

	primer_punto = perfil[0];
	if (primer_punto(0)==0 && primer_punto(2)==0){
		perfil.erase(perfil.begin());
		primero = true;
	}

	ultimo_punto = perfil[perfil.size()-1];
	if (ultimo_punto(0)==0 && ultimo_punto(2)==0){
		perfil.pop_back();
		ultimo = true;
	}

    for (int i=0; i<num_instancias; i++) {
        for (int j=0; j<perfil.size(); j++){
            alpha = 2 * M_PI * i /num_instancias;
            eje_x = cos(alpha) * perfil[j](0) + sin(alpha) * perfil[j](2);
            eje_z = - sin(alpha) * perfil[j](0) + cos(alpha) * perfil[j](2);

            v.push_back(Tupla3f (eje_x,perfil[j](1),eje_z));
        }
    }

    int a,b;
    for (int i=0; i<num_instancias; i++) {
        for (int j=0; j<perfil.size()-1;j++) {
            a = perfil.size()*i+j;
            b = perfil.size()*((i+1)%num_instancias) + j;

            f.push_back(Tupla3i (a,b,b+1));
            f.push_back(Tupla3i (a,b+1,a+1));
        }
    }

    figura_sin_tapas = f.size();
    fs = f;

    if (ultimo)
		v.push_back(ultimo_punto);
	else
		v.push_back( Tupla3f (0,v[v.size()-1](1),0));

    if (primero)
		v.push_back(primer_punto);
	else
                v.push_back( Tupla3f (0,v[0](1),0));

        if (tapas){
        this->crearTapaSuperior();
		  this->crearTapaInferior();
    }
    
}

void ObjRevolucion::setTapas(bool tapas){
    this->tapas = tapas;
}

void ObjRevolucion::draw(bool inmediato, GLenum tipo, int color, bool seleccion, bool tapas){

   visualizacion = tipo;
   inicializa_colores();
      switch (color){
         case 0:
            color_actual = c1;
            break;
         case 1:
            color_actual = c2;
            break;
         case 2:
            color_actual = c3;
            break;
         case 3:
            color_actual = orange;
            break;
         case 4:
            color_actual = cyan;
            break;
      }

   if(glIsEnabled(GL_LIGHTING)){
      if(seleccionado){
         material_seleccionado->aplicar();
      }else{
         m->aplicar();
      }
   }

   if(!tapas){
      this->TAM = figura_sin_tapas;
      if(inmediato){         
         draw_ModoInmediato(false);
      }else{
         draw_ModoDiferido(false);
      }
   }else{
      this->TAM = f.size();
      if(inmediato){
         draw_ModoInmediato(false);
      }else{
         draw_ModoDiferido(false);
      }
   }

}

void ObjRevolucion::draw_ajedrez(bool inmediato, bool tapas){

   if(!tapas){
      this->TAM = figura_sin_tapas;
      if(inmediato){
         draw_ModoInmediato(true);
      }else{
         draw_ModoDiferido(true);
      }
   }else{
      this->TAM = f.size();
      if(inmediato){
         draw_ModoInmediato(true);
      }else{
         draw_ModoDiferido(true);
      }
   }
   
}