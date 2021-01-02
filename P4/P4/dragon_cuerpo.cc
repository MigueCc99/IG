#include "dragon_cuerpo.h"
#include "ply_reader.h"

Dragon_cuerpo::Dragon_cuerpo(){
    ply::read("plys/ed_cuerpo.ply", this->v, this->f);
}