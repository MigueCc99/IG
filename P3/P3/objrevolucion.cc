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

ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapas) {
    crearMalla(archivo,num_instancias);
    this->tapas = tapas;
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
/*
void ObjRevolucion::draw_ModoInmediato(bool ajedrez, bool tapas){

   if(ajedrez){
      std::vector<Tupla3i> par;
      std::vector<Tupla3i> impar;
      inicializa_colores();
      for(int i=0; i<f.size(); i++){
         if(i%2 == 0)
            par.push_back(f[i]);
         else
            impar.push_back(f[i]);
      }
      
      glColorPointer(3,GL_FLOAT,0, c2.data() );
      glEnableClientState( GL_VERTEX_ARRAY );
      glVertexPointer( 3, GL_FLOAT, 0, v.data() ) ;
      glPolygonMode( GL_FRONT, GL_FILL);
      if(tapas){
        glDrawElements( GL_TRIANGLES, par.size()*3, GL_UNSIGNED_INT, par.data() );
      }else{
        glDrawElements( GL_TRIANGLES, par.size()*3-(figura_sin_tapas/2)*3, GL_UNSIGNED_INT, par.data() );
      }
      glColorPointer(3,GL_FLOAT,0, c3.data() );
      if(tapas){
        glDrawElements( GL_TRIANGLES, impar.size()*3, GL_UNSIGNED_INT, impar.data() );
      }else{
        glDrawElements( GL_TRIANGLES, impar.size()*3-(figura_sin_tapas/2)*3, GL_UNSIGNED_INT, impar.data() );
      }
      glDisableClientState( GL_VERTEX_ARRAY );

   }else{
      // visualizar la malla usando glDrawElements,

      // habilitar el uso de un array de vértices
      glEnableClientState( GL_VERTEX_ARRAY );

      // indicar el formato y la dirección de memoria del array de vértices
      // (son tuplas de 3 valores float, sin espacio entre ellas)
      glVertexPointer( 3, GL_FLOAT, 0, v.data() );

      glPolygonMode ( GL_FRONT, visualizacion);
      glPointSize(5.0);
      glEnableClientState( GL_COLOR_ARRAY) ;
      glColorPointer( 3, GL_FLOAT, 0, color_actual.data() );
      // visualizar, indicando: tipo de primitiva, número de índices,
      // tipo de los índices, y dirección de la tabla de índices
      if(tapas){
        glDrawElements( GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data());
      }else{
        glDrawElements( GL_TRIANGLES, figura_sin_tapas*3, GL_UNSIGNED_INT, f.data());
      }

      // deshabilitar el array de vértices
      glDisableClientState( GL_VERTEX_ARRAY );
   }

}

void ObjRevolucion::draw_ModoDiferido(bool ajedrez, bool tapas)
{

   if(ajedrez){
      std::vector<Tupla3i> par;
      std::vector<Tupla3i> impar;
      inicializa_colores();
      for(int i=0; i<f.size(); i++){
         if(i%2 == 0)
            par.push_back(f[i]);
         else
            impar.push_back(f[i]);
      }
      id_vbo_ver = 0, id_vbo_tri = 0, id_vbo_col = 0;
      if (id_vbo_ver == 0 || id_vbo_tri == 0 || id_vbo_col == 0){
         id_vbo_ver = CrearVBO (GL_ARRAY_BUFFER, (3*v.size())*sizeof(float), v.data() );
         if(tapas){
            id_vbo_tri = CrearVBO (GL_ELEMENT_ARRAY_BUFFER, (3*par.size())*sizeof(int), par.data() );
         }else{
            id_vbo_tri = CrearVBO (GL_ELEMENT_ARRAY_BUFFER, (3*par.size())*sizeof(int) - 3*(figura_sin_tapas/2)*sizeof(int), par.data() );
         }
         id_vbo_col = CrearVBO (GL_ARRAY_BUFFER, (3*c2.size())*sizeof(float), c2.data() );
      }
   
      glBindBuffer( GL_ARRAY_BUFFER, id_vbo_ver );
      glEnableClientState( GL_VERTEX_ARRAY );
      glVertexPointer( 3, GL_FLOAT, 0, 0 );
      glBindBuffer( GL_ARRAY_BUFFER, 0);

      glBindBuffer( GL_ARRAY_BUFFER, id_vbo_col );
      glColorPointer( 3, GL_FLOAT, 0, 0 );
      glBindBuffer( GL_ARRAY_BUFFER, 0 );

      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri );

      glPolygonMode( GL_FRONT, GL_FILL );
      glPolygonMode( GL_FRONT, visualizacion );
      glPointSize(5.0);

      glDrawElements( GL_TRIANGLES, 3* f.size(), GL_UNSIGNED_INT, 0 ) ;
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

      glDisableClientState( GL_VERTEX_ARRAY );

      id_vbo_ver = 0, id_vbo_tri = 0, id_vbo_col = 0;
      if (id_vbo_ver == 0 || id_vbo_tri == 0 || id_vbo_col == 0){
         id_vbo_ver = CrearVBO (GL_ARRAY_BUFFER, (3*v.size())*sizeof(float), v.data() );
         if(tapas){
            id_vbo_tri = CrearVBO (GL_ELEMENT_ARRAY_BUFFER, (3*impar.size())*sizeof(int), impar.data() );
         }else{
            id_vbo_tri = CrearVBO (GL_ELEMENT_ARRAY_BUFFER, (3*impar.size())*sizeof(int) - 3*(figura_sin_tapas/2)*sizeof(int), impar.data() );
         }
         id_vbo_col = CrearVBO (GL_ARRAY_BUFFER, (3*c3.size())*sizeof(float), c3.data() );
      }
   
      glBindBuffer( GL_ARRAY_BUFFER, id_vbo_ver );
      glEnableClientState( GL_VERTEX_ARRAY );
      glVertexPointer( 3, GL_FLOAT, 0, 0 );
      glBindBuffer( GL_ARRAY_BUFFER, 0);

      glBindBuffer( GL_ARRAY_BUFFER, id_vbo_col );
      glColorPointer( 3, GL_FLOAT, 0, 0 );
      glBindBuffer( GL_ARRAY_BUFFER, 0 );

      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri );

      glPolygonMode( GL_FRONT, GL_FILL );

      glPolygonMode( GL_FRONT, visualizacion );
      glPointSize(5.0);

      glDrawElements( GL_TRIANGLES, 3* f.size(), GL_UNSIGNED_INT, 0 ) ;
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

      glDisableClientState( GL_VERTEX_ARRAY );

   }else{
      id_vbo_ver = 0, id_vbo_tri = 0, id_vbo_col = 0;
      if (id_vbo_ver == 0 || id_vbo_tri == 0 || id_vbo_col == 0){
         id_vbo_ver = CrearVBO (GL_ARRAY_BUFFER, (3*v.size())*sizeof(float), v.data() );
         id_vbo_tri = CrearVBO (GL_ELEMENT_ARRAY_BUFFER, (3*f.size())*sizeof(int), f.data() );
         id_vbo_col = CrearVBO (GL_ARRAY_BUFFER, (3*color_actual.size())*sizeof(float), color_actual.data() );
      }

      glBindBuffer( GL_ARRAY_BUFFER, id_vbo_ver );
      glVertexPointer( 3, GL_FLOAT, 0, 0 );
      glBindBuffer( GL_ARRAY_BUFFER, 0);
      glEnableClientState( GL_VERTEX_ARRAY );

      glBindBuffer( GL_ARRAY_BUFFER, id_vbo_col );
      glColorPointer( 3, GL_FLOAT, 0, 0 );
      glBindBuffer( GL_ARRAY_BUFFER, 0 );

      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri );

      glPolygonMode( GL_FRONT, visualizacion );
      glPointSize(5.0);

      if(tapas){
        glDrawElements( GL_TRIANGLES, 3* f.size(), GL_UNSIGNED_INT, 0 );
      }else{
        glDrawElements( GL_TRIANGLES, 3* figura_sin_tapas, GL_UNSIGNED_INT, 0 );
      }

      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

      glDisableClientState( GL_VERTEX_ARRAY );
   }
}
*/
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

   if(glIsEnabled(GL_LIGHTING))
      m->aplicar();

   if(!tapas){
      if(inmediato){
         draw_ModoInmediato(false,fs);
      }else{
         draw_ModoDiferido(false,fs);
      }
   }else{
      if(inmediato){
         draw_ModoInmediato(false,f);
      }else{
         draw_ModoDiferido(false,f);
      }
   }

}

void ObjRevolucion::draw_ajedrez(bool inmediato, bool tapas){

   if(!tapas){
      if(inmediato){
         draw_ModoInmediato(true,fs);
      }else{
         draw_ModoDiferido(true,fs);
      }
   }else{
      if(inmediato){
         draw_ModoInmediato(true,f);
      }else{
         draw_ModoDiferido(true,f);
      }
   }
   
}