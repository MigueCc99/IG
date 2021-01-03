#include "dragon_cabeza.h"
#include "ply_reader.h"

Dragon_cabeza::Dragon_cabeza(){
	ply::read( "plys/ed_cabeza.ply", this->v, this->f );
}