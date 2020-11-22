#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "objrevolucion.h"
#include "cono.h"
#include "cilindro.h"
#include "esfera.h"
#include "luz.h"
#include "luzposicional.h"
#include "luzdireccional.h"

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO,SELESCENA,SELUCES} menu;
typedef enum {CUBO, TETRAEDRO} menu_figura;

class Escena
{

   private:

   

 // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
       
       // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();
    


   void clear_window();

   // SELECTORES DE MENÚ
      menu modoMenu=NADA;
      menu_figura figura;
   // SELECTOR DE MODO DE DIBUJADO
      bool inmediato = true;
   // SELECTOR DE FORMA DE DIBUJADO
      bool ajedrez = false;
      bool luces = false;
      bool is_luz0, is_luz1 = false;
      bool variar_alfa, variar_beta = false;
      
      std::vector<bool> tipo_dibujado;
      GLenum tipo_dibujado_actual;
      int escena_seleccionada = 4;
      int objeto_seleccionado = 3;
   // Objetos de la escena
   Ejes ejes;
   Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
   Tetraedro * tetraedro= nullptr ; // es importante inicializarlo a 'nullptr'
   ObjPLY * beethoven = nullptr;
   ObjRevolucion * peon = nullptr;
   Cono * cono = nullptr;
   Cilindro * cilindro = nullptr;
   Esfera * esfera = nullptr;
   ObjRevolucion * peonBlanco = nullptr;
   ObjRevolucion * peonNegro = nullptr;

   // Luces
   LuzPosicional *luz0 = nullptr;
   LuzDireccional *luz1 = nullptr;

   // Materiales
   Material * m0 = nullptr;
   Material * m1 = nullptr;
   Material * m2 = nullptr;

   float incremento_luz = -700;   
   bool tapas = true;
   
   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;
    void dibujar_seleccion();

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

    void pintaMenu(menu tipo);

};
#endif
