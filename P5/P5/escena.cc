

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
   molino = new Molino();  // Modelo Jerárquico
   dragon = new Dragon();  // Modelo Jerárquico

   // Cuadro y suelo
   cuadro = new Cuadro();
   suelo = new Cuadro();

   // Creamos las luces
   cuadroLuces[0] = new LuzPosicional({0, 0, 0}, GL_LIGHT1, {0.2, 0.2, 0.2, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0});
   cuadroLuces[1] = new LuzDireccional({0, 0}, GL_LIGHT2, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0});

   /*
      cuadroLuces[0] = new LuzPosicional( Tupla3f(0.0, 0.0, 0.0), GL_LIGHT0, Tupla4f(1.0, 1.0, 1.0, 1.0), Tupla4f(1.0, 1.0, 1.0, 1.0), Tupla4f(1.0, 1.0, 1.0, 1.0));;
      cuadroLuces[1] = new LuzDireccional( Tupla3f(100.0, 100.0, 100.0), GL_LIGHT1, Tupla4f(0.2, 1.0, 0.2, 1.0), Tupla4f(0.2, 1.0, 0.2, 1.0), Tupla4f(0.2, 1.0, 0.2, 1.0));
   */

   // Creamos los materiales

// Materiales
   Tupla4f ambiente1(0.135, 0.2225, 0.1575, 0.1), especular1(0.0, 0.0, 0.0, 0.1), difuso1(0.786, 0.89, 0.97, 0.1);
   Tupla4f ambiente2(0.0215,	0.1745, 0.0215, 0.6), especular2(0.7038, 0.27048, 0.0828, 0.6), difuso2(0.0, 0.0, 0.0, 0.6);
   Tupla4f ambiente3(0.0, 0.05, 0.0, 0.078125), especular3(0.04, 0.7, 0.04, 0.078125), difuso3(0.4, 0.5, 0.4, 0.078125);

   m0 = new Material(difuso1, especular1, ambiente1, 0.1*128.0);
   m1 = new Material(difuso2, especular2, ambiente2, 0.01*128.0);
   m2 = new Material(Tupla4f(0.4,0.0,0.0,1.0),Tupla4f(1.0,0.0,0.0,1.0),Tupla4f(1.0,0.0,0.0,1.0), 10.0);
   oro = new Material(Tupla4f(0.24725,0.1995,0.0745,1.0),Tupla4f(0.75164,0.60648,0.22648,1.0),Tupla4f(0.628281,0.555802,0.366065,1.0), 10.0);

   tetraedro->setMaterial(m2);
   cono->setMaterial(m2);
   cilindro->setMaterial(m2);
   esfera->setMaterial(m2);
   peonBlanco->setMaterial(oro);
   peonNegro->setMaterial(m1);
   molino->setMaterial(oro);
   dragon->setMaterial(oro);
   cuadro->setMaterial(m0);
   suelo->setMaterial(m0);

// Texturas
   tex1 = new Textura("img/text-madera.jpg", 1);
   tex2 = new Textura("img/dunas.jpg", 2);
   tex3 = new Textura("img/text-lata-1.jpg", 3);
   tex4 = new Textura("img/suelo.jpeg", 3);

   cuadro->setTextura(tex2);
   cuadro->setCoordenadas();
   suelo->setTextura(tex4);
   suelo->setCoordenadas();
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
   porDefecto();
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
   glDisable(GL_LIGHTING);
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
                  peon->draw_ajedrez(inmediato,tapas);
               glPopMatrix();
               glPushMatrix();
                  glTranslatef(0,0,0);
                  glScalef(20,20,20);
                  cono->draw_ajedrez(inmediato,tapas);
               glPopMatrix();        
               glPushMatrix();
                  glTranslatef(50,0,0);
                  glScalef(20,20,20);
                  cilindro->draw_ajedrez(inmediato,tapas);
               glPopMatrix();
               glPushMatrix();
                  glTranslatef(110,0,0);
                  glScalef(20,20,20);
                  esfera->draw_ajedrez(inmediato,tapas);
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
                  peon->draw(inmediato, tipo_dibujado_actual, color, false, tapas);
               glPopMatrix();
               glPushMatrix();
                  glTranslatef(0,0,0);
                  glScalef(20,20,20);
                  cono->draw(inmediato, tipo_dibujado_actual, color, false, tapas);
               glPopMatrix();
               glPushMatrix();
                  glTranslatef(50,0,0);
                  glScalef(20,20,20);
                  cilindro->draw(inmediato, tipo_dibujado_actual, color, false, tapas);
               glPopMatrix();  
               glPushMatrix();
                  glTranslatef(110,0,0);
                  glScalef(20,20,20);
                  esfera->draw(inmediato, tipo_dibujado_actual, color, false, tapas);
               glPopMatrix();  
            }
         }
// Escena P3
         if(escena_seleccionada == 3){  

            activacionLuces();

            if(ajedrez){
               glPushMatrix();
                  glTranslatef(-90,0,0);
                  glScalef(0.5,0.5,0.5);
                  tetraedro->draw_ajedrez(inmediato);
               glPopMatrix();
               /*
               glPushMatrix();
                  glTranslatef(0,0,0);
                  glScalef(20,20,20);
                  cono->draw_ajedrez(inmediato,tapas);
               glPopMatrix();   
                */     
               glPushMatrix();
                  glTranslatef(85,0,0);
                  glScalef(20,20,20);
                  cilindro->draw_ajedrez(inmediato,tapas);
               glPopMatrix();
               glPushMatrix();
                  glTranslatef(160,0,0);
                  glScalef(20,20,20);
                  esfera->draw_ajedrez(inmediato,tapas);
               glPopMatrix();
               glPushMatrix();
                  glTranslatef(-35,0,0);
                  glScalef(20,20,20);
                  peonBlanco->draw_ajedrez(inmediato, tapas);
               glPopMatrix();
               glPushMatrix();
                  glTranslatef(35,0,0);
                  glScalef(20,20,20);
                  peonNegro->draw_ajedrez(inmediato, tapas);
               glPopMatrix();   
            }else{
               glPushMatrix();
                  glTranslatef(-90,0,0);
                  glScalef(0.5,0.5,0.5);
                  tetraedro->draw(inmediato, tipo_dibujado_actual, color, false);
               glPopMatrix();
               /*
               glPushMatrix();
                  glTranslatef(0,0,0);
                  glScalef(20,20,20);
                  cono->draw(inmediato, tipo_dibujado_actual, color, false, tapas);
               glPopMatrix();
               */
               glPushMatrix();
                  glTranslatef(85,0,0);
                  glScalef(20,20,20);
                  cilindro->draw(inmediato, tipo_dibujado_actual, color, false, tapas);
               glPopMatrix();  
               glPushMatrix();
                  glTranslatef(160,0,0);
                  glScalef(20,20,20);
                  esfera->draw(inmediato, tipo_dibujado_actual, color, false, tapas);
               glPopMatrix();  
               glPushMatrix();
                  glTranslatef(-35,0,0);
                  glScalef(20,20,20);
                  peonBlanco->draw(inmediato, tipo_dibujado_actual, color, false, tapas);
               glPopMatrix();
               glPushMatrix();
                  glTranslatef(35,0,0);
                  glScalef(20,20,20);
                  peonNegro->draw(inmediato, tipo_dibujado_actual, color, false, tapas);
               glPopMatrix();
            }
         }   

// Escena P4
         if(escena_seleccionada == 4){
            activacionLuces();
            if(ajedrez){
               glPushMatrix();
                  glTranslatef(0,130,0);
                  dragon->draw_ajedrez(inmediato);                 
               glPopMatrix();
            }else{
               glPushMatrix();
                  glTranslatef(0,130,0);
                  dragon->draw(inmediato, tipo_dibujado_actual, color);                 
               glPopMatrix();
            }
         }

// Escena P5
         if(escena_seleccionada == 5){
            activacionLuces();
            glPushMatrix();
               glEnable(GL_TEXTURE_2D);
               glPushMatrix();
                  glTranslatef(-350, 650, -500);
                  glScalef(8, 8, 8);
                  glRotatef(-90, 0, 0, 1);
                  cuadro->draw(inmediato, tipo_dibujado[2], color, false); 
               glPopMatrix();
               glPushMatrix();
                  glTranslatef(-350, -100, -375);
                  glRotatef(-90, 1, 0, 0);
                  glRotatef(-90, 0, 0, 1);
                  glScalef(8, 8, 8);
                  suelo->draw(inmediato, tipo_dibujado[2], color, false); 
               glPopMatrix();
               glDisable(GL_TEXTURE_2D);
               if(ajedrez){
                  glPushMatrix();
                     glTranslatef(0,50,0);
                     dragon->draw_ajedrez(inmediato);                 
                  glPopMatrix();
               }else{
                  glPushMatrix();
                     glTranslatef(0,50,0);
                     dragon->draw(inmediato, tipo_dibujado_actual, color);                 
                  glPopMatrix();
               }
            glPopMatrix();
         }      
      }
   }
}

void Escena::animarModeloJerarquico(){
   if(activar_animacion){
      switch(num_fase){
         case 0:
            dragon->modificarDesplazamiento(incremento_desplazamiento, incremento_desplazamiento);
            dragon->modificarRotacionx(-incremento_giro);
            incremento1++;
            if(incremento1 > tope1){
               num_fase = 1;
               incremento1 = 0;
            }
            break;
         case 1:
            dragon->modificarDesplazamiento(incremento_desplazamiento, -incremento_desplazamiento);
            dragon->modificarRotacionx(-incremento_giro);
            incremento1++;
            if(incremento1 > tope1){
               num_fase = 2;
               incremento1 = 0;
            }
            break;
         case 2:
            dragon->modificarDesplazamiento(-incremento_desplazamiento, -incremento_desplazamiento);
            dragon->modificarRotacionx(-incremento_giro);
            incremento1++;
            if(incremento1 > tope1){
               num_fase = 3;
               incremento1 = 0;
            }
            break;     
         case 3:
            dragon->modificarDesplazamiento(-incremento_desplazamiento, incremento_desplazamiento);
            dragon->modificarRotacionx(-incremento_giro);
            incremento1++;
            if(incremento1 > tope1){
               num_fase = 0;
               incremento1 = 0;
            }
            break;         
      }

      switch(fase_alas){
         case 0:
            dragon->modificarGiroAlas(incremento_alas);
            dragon->modificarGiroCola(incremento_alas);
            tope2++;
            if(tope2 > limtope2){
               limtope2 = 60;
               fase_alas = 1;
               tope2 = 0;
            }
            break;
         case 1:
            dragon->modificarGiroAlas(-incremento_alas);
            dragon->modificarGiroCola(-incremento_alas);
            tope2++;
            if(tope2 > 60){
               fase_alas = 0;
               tope2 = 0;
            }
            break;
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
         if(escena_seleccionada == 1)
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
         }else if(modoMenu == SELVISUALIZACION){
            tapas = !tapas;
         }  
       break;       

      // SELECCION DE DIBUJADO
       case '1' :
         if(modoMenu == SELDIBUJADO){
            inmediato = true;
         }else if(modoMenu == SELESCENA){
            escena_seleccionada = 1;
         }else if(modoMenu == SELVISUALIZACION && modoIluminacion){
            luces[1] = !luces[1];
            std::cout << "\n\tLuz 1 activada\n";
         }else if(modoMenu == GRADOSLIBERTAD){
            giro1 = !giro1;
         }
       break;
       case '2' :
         if(modoMenu == SELDIBUJADO){
            inmediato = false;
         }else if(modoMenu == SELESCENA){
            escena_seleccionada = 2;
         }else if(modoMenu == GRADOSLIBERTAD){
            desplazamiento0 = !desplazamiento0;
         }
       break;  
       case '3' :
         if(modoMenu == SELESCENA){
            escena_seleccionada = 3;
         }
       break; 
       case '4' :
         if(modoMenu == SELESCENA){
            escena_seleccionada = 4;
         }
       break;        
            
      // SELECCION VISUALIZACIÓN
       case 'P' :
         if(modoMenu == SELVISUALIZACION && !modoIluminacion){
            ajedrez = false;
            modoIluminacion = false;
            if(tipo_dibujado[0] == false)
               tipo_dibujado[0] = true;
            else
               tipo_dibujado[0] = false;
         }         
       break;      
       case 'L' :
         if(modoMenu == SELVISUALIZACION){
            ajedrez = false;
            modoIluminacion = false;
            if(tipo_dibujado[1] == false)
               tipo_dibujado[1] = true;
            else
               tipo_dibujado[1] = false;
         }         
       break;   
       case 'S' :
         if(modoMenu == SELVISUALIZACION){
            ajedrez = false;
            modoIluminacion = false;
            if(tipo_dibujado[2] == false)
               tipo_dibujado[2] = true;
            else
               tipo_dibujado[2] = false;
         }         
       break;   
       case 'A' :
         if(modoMenu == SELVISUALIZACION && !modoIluminacion){
            modoIluminacion = false;
            ajedrez = !ajedrez;
            if(ajedrez){
               std::cout << "\nModo ajedrez activado\n";
            }

            else{
               std::cout << "\nModo lineas desactivado\n";
            }
         }else if(modoMenu == SELVISUALIZACION && modoIluminacion){
            if(variar_beta)
               variar_beta = false;
            variar_alfa = !variar_alfa;
         }else if(modoMenu == NADA || modoMenu == ANIMACION){
            if(!activar_animacion){
               modoMenu = ANIMACION;
            }else{
               modoMenu = NADA;
            }
            activar_animacion = !activar_animacion;
         }         
       break;  
       case 'I' :
         if(modoMenu == SELVISUALIZACION){
            if(escena_seleccionada == 3 || escena_seleccionada == 4 || escena_seleccionada == 5){
            modoIluminacion = !modoIluminacion;
            if(modoIluminacion){
               std::cout << "\nIluminación activada\n";
            }else{
               std::cout << "\nIluminación desactivada\n";
            }
            }
         }         
       break; 
       case '0' :
         if(modoMenu == SELVISUALIZACION && modoIluminacion){
            luces[0] = !luces[0];
            std::cout<<"\n\tLuz 0 activada\n";
         }else if(modoMenu == GRADOSLIBERTAD){
            giro0 = !giro0;
         } 
       break;       
       case 'B' :
         if(modoIluminacion){
            if(variar_alfa)
               variar_alfa = false;
            variar_beta = !variar_beta;
         }         
       break;    
       case '<' :
         if(modoIluminacion){
            if(variar_alfa)
               cuadroLuces[1]->variarAnguloAlpha(-10.0);
            else if (variar_beta)
               cuadroLuces[1]->variarAnguloBeta(-10.0);
         }         
       break; 
       case '>' :
         if(modoIluminacion){
            if(variar_alfa)
               cuadroLuces[1]->variarAnguloAlpha(10.0);
            else if (variar_beta)
               cuadroLuces[1]->variarAnguloBeta(10.0);
         }         
       break;   
       case '+' :
         if(modoMenu == GRADOSLIBERTAD){
            if(giro0){
               dragon->modificarGiroCola(cola_speed);
            }
            if(giro1){
               dragon->modificarGiroAlas(alas_speed);
            }
            if(desplazamiento0){
               dragon->modificarDesplazamiento(desplazamiento_speed,desplazamiento_speed);
            }
         }else if(modoMenu == ANIMACION){
            incremento_alas += 0.2;
            incremento_desplazamiento += 0.2;
            incremento_giro += 0.07;

            tope1 -= 45;
         }
       break; 
       case '-':
          if (modoMenu == GRADOSLIBERTAD){

             if (giro0){
                dragon->modificarGiroCola(-cola_speed);
             }
             if (giro1){
                dragon->modificarGiroAlas(-alas_speed);
             }
             if (desplazamiento0){
                dragon->modificarDesplazamiento(-desplazamiento_speed,-desplazamiento_speed);
             }
          }else if (modoMenu == ANIMACION){
             incremento_alas -= 0.2;
             incremento_desplazamiento -= 0.2;
             incremento_giro -= 0.07;

             tope1 += 90;
          }
       break;   
       case 'M' :
         if(giro0){
            cola_speed += 0.1;
         }
         if(giro1){
            alas_speed += 0.1;
         }
         if(desplazamiento0){
            desplazamiento_speed += 0.1;
         }
       break;  
       case 'N' :
         if(giro0){
            cola_speed -= 0.1;
         }
         if(giro1){
            alas_speed -= 0.1;
         }
         if(desplazamiento0){
            desplazamiento_speed -= 0.1;
         }
       break;  
       case 'G':
       if(modoMenu == NADA)
         modoMenu = GRADOSLIBERTAD;
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
    if(escena_seleccionada == 1)
      std::cout << "O -> Selección de objeto\n"; 
    std::cout << "E -> Selección de escena\n";  
    std::cout << "V -> Selección de modo de visualización\n";
    std::cout << "D -> Selección de modo de dibujado\n";
    std::cout << "A -> Animación automática\n";
    std::cout << "G -> Movimiento grados de libertad\n";
    std::cout << "Q -> Salir del programa\n";
    break;
    case (SELOBJETO):
    std::cout << "Modo Objeto - Opciones Disponibles\n";
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
    std::cout << "Modo Escena - Opciones Disponibles\n";
    std::cout << "1 -> Seleccionar escena P1\n";
    std::cout << "2 -> Seleccionar escena P2\n";
    std::cout << "3 -> Seleccionar escena P3\n";
    std::cout << "4 -> Seleccionar escena P4\n";
    std::cout << "5 -> Seleccionar escena P5\n";
    std::cout << "Q -> Salir del menú\n";
    if (escena_seleccionada == 1){
      std::cout << "Escena P1 seleccionada\n";
    }else if (escena_seleccionada == 2){
      std::cout << "Escena P2 seleccionada\n";
    }else if (escena_seleccionada == 3){
      std::cout << "Escena P3 seleccionada\n";
    }else if (escena_seleccionada == 4){
      std::cout << "Escena P4 seleccionada\n";
    }else if (escena_seleccionada == 5){
      std::cout << "Escena P5 seleccionada\n";
    }
    break;
    case (SELVISUALIZACION):

    if(!modoIluminacion){
      std::cout << "Modo de Visualización - Opciones Disponibles\n";
      std::cout << "S -> Visualización en sólido\n";
      std::cout << "L -> Visualización en líneas\n";
      std::cout << "P -> Visualización en puntos\n";
      std::cout << "A -> Visualización en ajedrez\n";
      std::cout << "T -> Gestión de tapas: " << tapas << std::endl;
      if(escena_seleccionada == 3 || escena_seleccionada == 4 || escena_seleccionada == 5)
         std::cout << "I -> Activar iluminación\n";
      std::cout << "Q -> Salir del menú\n";
    }
    else{
      std::cout << "Modo Iluminación - Opciones Disponibles\n";
      std::cout << "0 -> Activar luz posicional\n";
      std::cout << "1 -> Activar luz direccional\n";
      std::cout << "A -> Seleccionar angulo alfa de luz 1\n";
      std::cout << "B -> Seleccionar angulo beta de luz 1\n";
      std::cout << "Q -> Salir del menú\n";
      if(variar_alfa){
         std::cout << "Variando el angulo alfa\n";
      }else if(variar_beta){
         std::cout << "Variando el angulo beta\n";
      }
      std::cout << "> -> Incrementar ángulo seleccionado\n";
      std::cout << "< -> Decrementar ángulo seleccionado\n";
      std::cout << "I -> Desactivar iluminación\n";
      std::cout << "Q -> Salir del menú\n";
    }
    break;
    case (SELDIBUJADO):
    std::cout << "Modo Dibujado - Opciones Disponibles\n";
    std::cout << "1 -> Modo inmediato\n";
    std::cout << "2 -> Modo diferido\n";
    if (inmediato){
      std::cout << "Seleccionado el modo inmediato\n";
    }else{
      std::cout << "Seleccionado el modo diferido\n";
    }
    std::cout << "Q -> Salir del menú\n";
    break;
    case (GRADOSLIBERTAD):
    std::cout << "0 -> Activar giro cola (" << giro0 << ")\n";
    std::cout << "1 -> Activar giro alas (" << giro1 << ")\n";
    std::cout << "2 -> Activar desplazamiento (" << desplazamiento0 << ")\n";
    std::cout << "+ -> Aumentar grados de libertad\n";
    std::cout << "- -> Disminuir grados de libertad\n";
    std::cout << "M -> Aumentar velocidad de partes seleccionadas\n";
    std::cout << "N -> Disminuir velocidad partes seleccionadas\n";
    std::cout << "Q -> Salir del menú\n";
    break;
    case (ANIMACION):
    std::cout << "La animación ha comenzado\n";
    std::cout << "A -> Detener la animación\n";
    std::cout << "Q -> Salir del menú\n";
    break;
  }
}


void Escena::activacionLuces(){
   if(modoIluminacion){
      if(!glIsEnabled(GL_LIGHTING)){
         glEnable(GL_LIGHTING);
      }

      for(int i=0; i<2; i++){
         if(cuadroLuces[i] != nullptr && luces[i]){
            cuadroLuces[i]->activar();
         }
         else if(cuadroLuces[i] != nullptr && !luces[i]){
            glDisable(cuadroLuces[i]->getID());
         }
      }
   
      glShadeModel(GL_SMOOTH);
   }
   else{
      if(glIsEnabled(GL_LIGHTING)){
         glDisable(GL_LIGHTING);
      }
      glShadeModel(GL_FLAT);      
   }
}

void Escena::porDefecto(){
   tipo_dibujado[2] = true;
   modoIluminacion = true;
   for(int i=0; i<2; i++){
      cuadroLuces[i]->activar();
      luces[i] = true;
   }
}