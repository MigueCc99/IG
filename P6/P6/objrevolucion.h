// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

typedef enum {EJE_X, EJE_Y, EJE_Z} rotacion;

class ObjRevolucion : public Malla3D
{
   public:
    ObjRevolucion();
    ObjRevolucion(const std::string & archivo, int num_instancias, bool tapas) ;
    ObjRevolucion(std::vector<Tupla3f> perfil, int num_instancias, bool tapas) ;
    void setTapas(bool tapas);
    void draw(bool inmediato, GLenum tipo, int color, bool seleccion, bool tapas);
    void draw_ajedrez(bool inmediato, bool tapas);

protected:

    std::vector<Tupla3i> fs;
    int ejeRevolucion = 0;
    bool tapas;
    std::vector<Tupla3f> aux;
    int num_instancias;

    std::vector<Tupla3f> voltearVertices(const std::vector<Tupla3f> &perfil_original);

    void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias);
    void crearTapaSuperior();
    void crearTapaInferior();

} ;




#endif
