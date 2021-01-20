#include "aux.h"
#include "malla.h"
#include <stdlib.h>

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

Malla3D::Malla3D(){}

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato(bool ajedrez, std::vector<Tupla3i> figura)
{

   if(ajedrez){
      std::vector<Tupla3i> par;
      std::vector<Tupla3i> impar;
      inicializa_colores();
      for(int i=0; i<figura.size(); i++){
         if(i%2 == 0)
            par.push_back(figura[i]);
         else
            impar.push_back(figura[i]);
      }
      
      glColorPointer(3,GL_FLOAT,0, c2.data() );
      glEnableClientState( GL_VERTEX_ARRAY );
      glVertexPointer( 3, GL_FLOAT, 0, v.data() ) ;
      glPolygonMode( GL_FRONT, GL_FILL);
      glDrawElements( GL_TRIANGLES, par.size()*3, GL_UNSIGNED_INT, par.data() );
      glColorPointer(3,GL_FLOAT,0, c3.data() );
      glDrawElements( GL_TRIANGLES, impar.size()*3, GL_UNSIGNED_INT, impar.data() );
      glDisableClientState( GL_VERTEX_ARRAY );

   }else{
      // visualizar la malla usando glDrawElements,

      // habilitar el uso de un array de vértices
      glEnableClientState( GL_VERTEX_ARRAY );

      // indicar el formato y la dirección de memoria del array de vértices
      // (son tuplas de 3 valores float, sin espacio entre ellas)
      glVertexPointer( 3, GL_FLOAT, 0, v.data() );

      if(glIsEnabled(GL_LIGHTING)){
         if(nv.size() == 0)
            calcular_normales();
         glNormalPointer( GL_FLOAT, 0, nv.data() );
         glEnableClientState( GL_NORMAL_ARRAY );
         glPolygonMode ( GL_FRONT, GL_FILL);
      }

      if(!glIsEnabled(GL_LIGHTING))
         glPolygonMode ( GL_FRONT, visualizacion);
      glPointSize(5.0);
      glEnableClientState( GL_COLOR_ARRAY) ;
      glColorPointer( 3, GL_FLOAT, 0, color_actual.data() );

      // Tabla de texturas
      if(!ct.empty() && textura != nullptr){
         glEnableClientState(GL_TEXTURE_COORD_ARRAY);
         glTexCoordPointer(2, GL_FLOAT, 0, ct.data());
      }

      // visualizar, indicando: tipo de primitiva, número de índices,
      // tipo de los índices, y dirección de la tabla de índices
      glDrawElements( GL_TRIANGLES, figura.size()*3, GL_UNSIGNED_INT, figura.data());

      // deshabilitar el array de vértices
      glDisableClientState( GL_VERTEX_ARRAY );

      if(glIsEnabled(GL_LIGHTING)){
         glDisableClientState( GL_NORMAL_ARRAY );
      }
      if(glIsEnabled(GL_TEXTURE_COORD_ARRAY)){
         glDisableClientState(GL_TEXTURE_COORD_ARRAY);
      }
   }

}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido(bool ajedrez, std::vector<Tupla3i> figura)
{

   if(ajedrez){
      std::vector<Tupla3i> par;
      std::vector<Tupla3i> impar;
      inicializa_colores();
      for(int i=0; i<figura.size(); i++){
         if(i%2 == 0)
            par.push_back(figura[i]);
         else
            impar.push_back(figura[i]);
      }

      id_vbo_ver = 0, id_vbo_tri = 0, id_vbo_col = 0;
      if (id_vbo_ver == 0 || id_vbo_tri == 0 || id_vbo_col == 0){
         id_vbo_ver = CrearVBO (GL_ARRAY_BUFFER, (3*v.size())*sizeof(float), v.data() );
         id_vbo_tri = CrearVBO (GL_ELEMENT_ARRAY_BUFFER, (3*par.size())*sizeof(int), par.data() );
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

      glDrawElements( GL_TRIANGLES, 3* par.size(), GL_UNSIGNED_INT, 0 ) ;
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

      glDisableClientState( GL_VERTEX_ARRAY );

      id_vbo_ver = id_vbo_tri = id_vbo_col = 0;
      if (id_vbo_ver == 0 || id_vbo_tri == 0 || id_vbo_col == 0){
         id_vbo_ver = CrearVBO (GL_ARRAY_BUFFER, (3*v.size())*sizeof(float), v.data() );
         id_vbo_tri = CrearVBO (GL_ELEMENT_ARRAY_BUFFER, (3*impar.size())*sizeof(int), impar.data() );
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

      glDrawElements( GL_TRIANGLES, 3* impar.size(), GL_UNSIGNED_INT, 0 ) ;
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

      glDisableClientState( GL_VERTEX_ARRAY );

   }else{

      if(glIsEnabled(GL_LIGHTING))
         calcular_normales();

      id_vbo_ver = id_vbo_tri = id_vbo_col = 0;
      if (id_vbo_ver == 0 || id_vbo_tri == 0 || id_vbo_col == 0){
         id_vbo_ver = CrearVBO (GL_ARRAY_BUFFER, (3*v.size())*sizeof(float), v.data() );
         id_vbo_tri = CrearVBO (GL_ELEMENT_ARRAY_BUFFER, (3*figura.size())*sizeof(int), figura.data() );
         id_vbo_col = CrearVBO (GL_ARRAY_BUFFER, (3*color_actual.size())*sizeof(float), color_actual.data() );
         id_vbo_nor = CrearVBO (GL_ARRAY_BUFFER, (3*nv.size())*sizeof(float), nv.data() );
         id_vbo_tex = CrearVBO (GL_ARRAY_BUFFER, (3*ct.size())*sizeof(float), ct.data() );
      }

      glBindBuffer( GL_ARRAY_BUFFER, id_vbo_ver );
      glVertexPointer( 3, GL_FLOAT, 0, 0 );
      glBindBuffer( GL_ARRAY_BUFFER, 0);
      glEnableClientState( GL_VERTEX_ARRAY );

      if(glIsEnabled(GL_LIGHTING)){
         glEnableClientState( GL_NORMAL_ARRAY );
         glBindBuffer( GL_ARRAY_BUFFER, id_vbo_nor );

         glNormalPointer( GL_FLOAT, 0, 0 );
         glBindBuffer( GL_ARRAY_BUFFER, 0);
      }

      glBindBuffer( GL_ARRAY_BUFFER, id_vbo_col );
      glColorPointer( 3, GL_FLOAT, 0, 0 );
      glBindBuffer( GL_ARRAY_BUFFER, 0 );

      if(!ct.empty() && textura != nullptr){
         glEnableClientState(GL_TEXTURE_COORD_ARRAY);
         glTexCoordPointer(2, GL_FLOAT, 0, ct.data());
      }

      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri );

      if(glIsEnabled(GL_LIGHTING))
         glPolygonMode( GL_FILL, visualizacion );     
      else
         glPolygonMode( GL_FRONT, visualizacion );
      glPointSize(5.0);

      glDrawElements( GL_TRIANGLES, 3* figura.size(), GL_UNSIGNED_INT, 0 ) ;
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

      glDisableClientState( GL_VERTEX_ARRAY );

      if(glIsEnabled(GL_LIGHTING)){
         glDisableClientState( GL_NORMAL_ARRAY );
      }
      if(glIsEnabled(GL_TEXTURE_COORD_ARRAY)){
         glDisableClientState(GL_TEXTURE_COORD_ARRAY);
      }
   }
}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(bool inmediato, GLenum tipo, int color, bool seleccion)
{
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

   if(textura != nullptr)
      textura->activar();

   if(inmediato){
      draw_ModoInmediato(false, f);
   }else{
      draw_ModoDiferido(false, f);
   }

}

void Malla3D::draw_ajedrez(bool inmediato){

   if(inmediato)
      draw_ModoInmediato(true,f);
   else
      draw_ModoDiferido(true,f);
   
   /*
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
   glDrawElements( GL_TRIANGLES, par.size()*3, GL_UNSIGNED_INT, par.data() );
   glColorPointer(3,GL_FLOAT,0, c3.data() );
   glDrawElements( GL_TRIANGLES, impar.size()*3, GL_UNSIGNED_INT, impar.data() );
   glDisableClientState( GL_VERTEX_ARRAY );
   */

}

GLuint Malla3D::CrearVBO (GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram){
   GLuint id_vbo;                                                          // resultado: identificador de VBO
   glGenBuffers( 1, &id_vbo );                                             // crear nuevo VBO, obtener identificador
   glBindBuffer( tipo_vbo, id_vbo );                                       // activar el VBO usando su identificador   
   glBufferData( tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW);    // esta instrucción hace la transferencia de datos desde RAM a GPU
   glBindBuffer( tipo_vbo, 0 );                                            // desactivación del VBO (activar 0)

   return id_vbo;    // devolver el identificador resultado
}

void Malla3D::inicializa_colores(){
   c1.resize(v.size()*2);
	c2.resize(v.size()*2);
	c3.resize(v.size()*2);
   orange.resize(v.size()*2);
   cyan.resize(v.size()*2);
   color_seleccion.resize(v.size()*2);

   for (int i=0; i<v.size()*2; i++){
      c1[i] = Tupla3f (1.0f,0.0f,0.0f);
      c2[i] = Tupla3f (0.0f,0.0f,1.0f);
      c3[i] = Tupla3f (0.0f,1.0f,0.0f);
      orange[i] = Tupla3f (1.0f,0.501961f,0.0f);
      cyan[i] = Tupla3f (0.0f,1.0f,1.0f);
      color_seleccion[i] = Tupla3f (1.0f,0.0f,0.0f);
   }
}

void Malla3D::calcular_normales(){
  // Gestionamos las normales de las caras
  for(int i = 0; i < this->f.size(); i++){
    Tupla3f p = v[f[i](0)];
    Tupla3f q = v[f[i](1)];
    Tupla3f r = v[f[i](2)];

    // Las dos aristas resultantes
    Tupla3f a = q-p;
    Tupla3f b = r-p;

    // Vector perpendicular a la cara
    Tupla3f mc = a.cross(b);

    // Normalizamos el vector y lo introducimos
    this->nc.push_back(mc.normalized());
  }

  // Gestionamos las normales de los vértices
  nv = std::vector<Tupla3f>(v.size(), {0, 0, 0});

  for(int i = 0; i < this->f.size(); i++){
    nv[f[i](0)] = (nv[f[i](0)] + nc[i]).normalized();
    nv[f[i](1)] = (nv[f[i](1)] + nc[i]).normalized();
    nv[f[i](2)] = (nv[f[i](2)] + nc[i]).normalized();
  }

}

void Malla3D::setMaterial(Material * mat){
   this->m = mat;
}

void Malla3D::setMaterialSeleccionado(Material * mat){
   material_seleccionado = mat;
}

void Malla3D::setTextura(Textura *textura){
   this->textura = textura;
}

Tupla3f Malla3D::getCentro(){
   return centro;
}

void Malla3D::asignaCentro(float cord_centro[]){
  int x=0,y=0,z=0;
  for (int i=0; i < v.size(); i++){
    x+=v[i](0);
    y+=v[i](1);
    z+=v[i](2);
  }
  x = x/v.size();
  y = y/v.size();
  z = z/v.size();

  centro(0) = cord_centro[0] * x + cord_centro[4] * y + cord_centro[8] * z + cord_centro[12];
  centro(1) = cord_centro[1] * x + cord_centro[5] * y + cord_centro[9] * z + cord_centro[13];
  centro(2) = cord_centro[2] * x + cord_centro[6] * y + cord_centro[10] * z + cord_centro[14];
}

void Malla3D::setSeleccionado(bool selecc){
  seleccionado = selecc;
}