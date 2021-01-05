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
#include "molino.h"
#include "dragon.h"
#include "cuadro.h"
#include "camara.h"

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO,SELESCENA,SELUCES,GRADOSLIBERTAD,ANIMACION,CAMARA,SELECCIONAR} menu;
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
      bool giro0 = false, giro1 = false, desplazamiento0 = false;
      bool variar_alfa, variar_beta = false;
      
      std::vector<bool> tipo_dibujado;
      GLenum tipo_dibujado_actual;
      int escena_seleccionada = 6;
      int objeto_seleccionado = 2;
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
   Molino * molino = nullptr;
   Dragon * dragon = nullptr;

   // Sol
   Esfera * sol = nullptr;

   // Cuadro y suelo
   Cuadro* suelo = nullptr;
   Cuadro * cuadro = nullptr;

   // Luces
   Luz* cuadroLuces[8] = {nullptr};
   bool luces[8] = {false};
   bool modoIluminacion = false;
   bool animacionPuntual = false;

   // Materiales
   Material * m0 = nullptr;
   Material * m1 = nullptr;
   Material * m2 = nullptr;
   Material * oro = nullptr;
   Material * sol_material = nullptr;

   // Texturas
   Textura * tex1;
   Textura * tex2;
   Textura * tex3;
   Textura * tex4;

   float incremento_luz = -700;   
   bool tapas = true;

   // Variables animación del dragón
   bool activar_animacion = false;
   int num_fase = 0;

   float incremento_alas = 0.9;
   int fase_alas = 0;

   float cola_speed = 0.5;
   float alas_speed = 0.5;
   float desplazamiento_speed = 5.5;

   float incremento_desplazamiento = 0.9;
   float fase_desplazamientoy = 1;
   float fase_desplazamientoz = 1;

   float incremento_giro = 0.3;

   size_t tope1 = 300, tope2 = 0, limtope2 = 30, incremento1 = 0, incremento2 = 0;

   // Camaras
   std::vector<Camara> camaras;
   int camara_actual = 0;
   bool camara_raton = false;
   int x_anterior = 0, y_anterior = 0;
   bool zoom_raton_up = false, zoom_raton_down = false;

   Tupla3f centro_vista = Tupla3f(0,0,0);
   bool seleccion = false;
   bool fperson_camara = false;

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
   void animarModeloJerarquico();

   void clickRaton(int boton, int estado, int x, int y);
   void ratonMovido(int x, int y);

    void pintaMenu(menu tipo);

    void activacionLuces();

    void porDefecto();

};
#endif
