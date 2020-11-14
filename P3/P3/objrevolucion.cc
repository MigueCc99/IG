#include "aux.h"
#include "objrevolucion.h"
#include <cmath>
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


ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapas) {
    crearMalla(archivo,num_instancias);
    this->tapas = tapas;
    if (tapas){
        this->crearTapaInferior();
        this->crearTapaSuperior();
    }
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias) {
    float alpha;
    float eje_x, eje_z;
    bool primero=false, ultimo=false;
	Tupla3f primer_punto;
	Tupla3f ultimo_punto;

	primer_punto = perfil_original[0];
	if (primer_punto(0)==0 && primer_punto(2)==0){
		perfil_original.erase(perfil_original.begin());
		primero = true;
	}

	ultimo_punto = perfil_original[perfil_original.size()-1];
	if (ultimo_punto(0)==0 && ultimo_punto(2)==0){
		perfil_original.pop_back();
		ultimo = true;
	}

    for (int i=0; i<num_instancias; i++) {
        for (int j=0; j<perfil_original.size(); j++){
            alpha = 2 * M_PI * i /num_instancias;
            eje_x = cos(alpha) * perfil_original[j](0) + sin(alpha) * perfil_original[j](2);
            eje_z = - sin(alpha) * perfil_original[j](0) + cos(alpha) * perfil_original[j](2);

            v.push_back(Tupla3f (eje_x,perfil_original[j](1),eje_z));
        }
    }

    int a,b;
    for (int i=0; i<num_instancias; i++) {
        for (int j=0; j<perfil_original.size()-1;j++) {
            a = perfil_original.size()*i+j;
            b = perfil_original.size()*((i+1)%num_instancias) + j;

            f.push_back(Tupla3i (a,b,b+1));
            f.push_back(Tupla3i (a,b+1,a+1));
        }
    }

    figura_sin_tapas = f.size();

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

