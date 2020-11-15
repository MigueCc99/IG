

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );
    tipo_dibujado.resize(3);

   // crear los objetos de la escena....
   cubo = new Cubo(50);
   tetraedro = new Tetraedro();
   beethoven = new ObjPLY("plys/beethoven.ply");
   peon = new ObjRevolucion("plys/peon.ply",20,true);
   cono = new Cono();
   cilindro = new Cilindro();
   esfera = new Esfera();
   peonBlanco = new ObjRevolucion("plys/peon.ply",20,true);
   peonNegro = new ObjRevolucion("plys/peon.ply",20,true);

   // Crear las luces
   luz0 = new LuzPosicional( Tupla3f(0.0, 0.0, 0.0), GL_LIGHT0, Tupla4f(1.0, 1.0, 1.0, 1.0), Tupla4f(1.0, 1.0, 1.0, 1.0), Tupla4f(1.0, 1.0, 1.0, 1.0));
   luz1 = new LuzDireccional( Tupla3f(100.0, 100.0, 100.0), GL_LIGHT1, Tupla4f(0.2, 1.0, 0.2, 1.0), Tupla4f(0.2, 1.0, 0.2, 1.0), Tupla4f(0.2, 1.0, 0.2, 1.0));

   // Crea los materiales
   m0 = new Material(Tupla4f(0.3,0.3,0.3,1.0),Tupla4f(1.0,1.0,1.0,1.0),Tupla4f(1.0,1.0,1.0,1.0), 10.0);
   m1 = new Material(Tupla4f(0.0,0.0,0.0,1.0),Tupla4f(0.0,0.0,0.0,1.0),Tupla4f(0.0,0.0,0.0,1.0), 10.0);

   peonBlanco->setMaterial(m0);
   peonNegro->setMaterial(m0);
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
   glEnable(GL_CULL_FACE);
   glEnable(GL_NORMALIZE);
   glShadeModel(GL_SMOOTH);

	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );
   pintaMenu(modoMenu);
}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
    ejes.draw();
    // COMPLETAR
    //   Dibujar los diferentes elementos de la escena
   for(int i=0; i<tipo_dibujado.size(); i++){
      if(tipo_dibujado[i]){
         int color = 0;
         switch(i){
            case 0:
               tipo_dibujado_actual = GL_POINT;
                  color = 0;
               break;
            case 1:
               tipo_dibujado_actual = GL_LINE;
                  color = 1;
               break;
            case 2:
               tipo_dibujado_actual = GL_FILL;
                  color = 2;
               break;
         }
// Escena P1
         if(escena_seleccionada == 1){
            if(ajedrez){
               if(objeto_seleccionado == 1){
                  glPushMatrix();
                     glTranslatef(-25,-25,-25);
                     cubo->draw_ajedrez(inmediato);
                  glPopMatrix();
               }else if(objeto_seleccionado == 2){
                  tetraedro->draw_ajedrez(inmediato);
               }
            }else{
               if(objeto_seleccionado == 1){
                  glPushMatrix();
                     glTranslatef(-25,-25,-25);
                     cubo->draw(inmediato, tipo_dibujado_actual, color, false);
                  glPopMatrix();
               }else if(objeto_seleccionado == 2){
                  tetraedro->draw(inmediato, tipo_dibujado_actual, color, false);
               }
            }
         }

// Escena P2
         if(escena_seleccionada == 2){
            if(ajedrez){
               
               glPushMatrix();
                  glTranslatef(-65,0,0);
                  glScalef(2,2,2);
                  beethoven->draw_ajedrez(inmediato);
               glPopMatrix();
               glPushMatrix();
                  glTranslatef(-35,0,0);
                  glScalef(20,20,20);
                  peon->draw_ajedrez(inmediato);
               glPopMatrix();
               glPushMatrix();
                  glTranslatef(0,0,0);
                  glScalef(20,20,20);
                  cono->draw_ajedrez(inmediato);
               glPopMatrix();        
               glPushMatrix();
                  glTranslatef(50,0,0);
                  glScalef(20,20,20);
                  cilindro->draw_ajedrez(inmediato);
               glPopMatrix();
               glPushMatrix();
                  glTranslatef(110,0,0);
                  glScalef(20,20,20);
                  esfera->draw_ajedrez(inmediato);
               glPopMatrix();
            }else{
               glPushMatrix();
                  glTranslatef(-65,0,0);
                  glScalef(2,2,2);
                  beethoven->draw(inmediato, tipo_dibujado_actual, color, false);
               glPopMatrix();
               glPushMatrix();
                  glTranslatef(-35,0,0);
                  glScalef(20,20,20);
                  peon->draw(inmediato, tipo_dibujado_actual, color, false);
               glPopMatrix();
               glPushMatrix();
                  glTranslatef(0,0,0);
                  glScalef(20,20,20);
                  cono->draw(inmediato, tipo_dibujado_actual, color, false);
               glPopMatrix();
               glPushMatrix();
                  glTranslatef(50,0,0);
                  glScalef(20,20,20);
                  cilindro->draw(inmediato, tipo_dibujado_actual, color, false);
               glPopMatrix();  
               glPushMatrix();
                  glTranslatef(110,0,0);
                  glScalef(20,20,20);
                  esfera->draw(inmediato, tipo_dibujado_actual, color, false);
               glPopMatrix();  
            }
         }
      }
   }
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;
   switch( toupper(tecla) )
   {
      case 'Q' :
         if (modoMenu!=NADA)
            modoMenu=NADA;            
         else {
            salir=true ;
         }
         break ;
      case 'O' :
         // ESTAMOS EN MODO SELECCION DE OBJETO
         modoMenu=SELOBJETO; 
         break ;
        case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         modoMenu=SELVISUALIZACION;
         break ;
       case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         modoMenu=SELDIBUJADO;
         break ;
       case 'E' :
         // ESTAMOS EN MODO SELECCION DE ESCENA
         modoMenu=SELESCENA;
         break ;
         // COMPLETAR con los diferentes opciones de teclado

      // SELECCION DE OBJETO
       case 'C' :
         if(modoMenu == SELOBJETO){
            objeto_seleccionado = 1;
         }
       break;
       case 'T' :
         if(modoMenu == SELOBJETO){
            objeto_seleccionado = 2;
         } 
       break;       

      // SELECCION DE DIBUJADO
       case '1' :
         if(modoMenu == SELDIBUJADO){
            inmediato = true;
         }else if(modoMenu == SELESCENA){
            escena_seleccionada = 1;
         }
       break;
       case '2' :
         if(modoMenu == SELDIBUJADO){
            inmediato = false;
         }else if(modoMenu == SELESCENA){
            escena_seleccionada = 2;
         }
       break;        
            
      // SELECCION VISUALIZACIÓN
       case 'P' :
         if(modoMenu == SELVISUALIZACION){
            ajedrez = false;
            if(tipo_dibujado[0] == false)
               tipo_dibujado[0] = true;
            else
               tipo_dibujado[0] = false;
         }         
       break;      
       case 'L' :
         if(modoMenu == SELVISUALIZACION){
            ajedrez = false;
            if(tipo_dibujado[1] == false)
               tipo_dibujado[1] = true;
            else
               tipo_dibujado[1] = false;
         }         
       break;   
       case 'S' :
         if(modoMenu == SELVISUALIZACION){
            ajedrez = false;
            if(tipo_dibujado[2] == false)
               tipo_dibujado[2] = true;
            else
               tipo_dibujado[2] = false;
         }         
       break;   
       case 'A' :
         if(modoMenu == SELVISUALIZACION){
            if(ajedrez == false)
               ajedrez = true;
            else
               ajedrez = false;
         }         
       break;   
   }

   pintaMenu(modoMenu);
   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}

void Escena::pintaMenu(menu tipo){
  std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

  switch (tipo){
    case (NADA):
    std::cout << "O -> Selección de objeto\n"; 
    std::cout << "E -> Selección de escena\n";  
    std::cout << "V -> Selección de modo de visualización\n";
    std::cout << "D -> Selección de modo de dibujado\n";
    std::cout << "Q -> Salir del programa\n";
    break;
    case (SELOBJETO):
    std::cout << "C -> Seleccionar cubo\n";   
    std::cout << "T -> Seleccionar tetraedro\n";
    std::cout << "Q -> Salir del menú\n";
    if (objeto_seleccionado == 1){
      std::cout << "Cubo seleccionado\n";
    }else{
      std::cout << "Tetraedro seleccionado\n";
    }
    break;
    case (SELESCENA):
    std::cout << "1 -> Seleccionar escena P1\n";
    std::cout << "2 -> Seleccionar escena P2\n";
    std::cout << "Q -> Salir del menú\n";
    break;
    case (SELVISUALIZACION):
    std::cout << "S -> Visualización en sólido\n";
    std::cout << "L -> Visualización en líneas\n";
    std::cout << "P -> Visualización en puntos\n";
    std::cout << "A -> Visualización en ajedrez\n";
    std::cout << "Q -> Salir del menú\n";
    break;
    case (SELDIBUJADO):
    std::cout << "1 -> Modo inmediato\n";
    std::cout << "2 -> Modo diferido\n";
    if (inmediato){
      std::cout << "Seleccionado el modo inmediato\n";
    }else{
      std::cout << "Seleccionado el modo diferido\n";
    }
    std::cout << "Q -> Salir del menú\n";
    break;
  }   
}
