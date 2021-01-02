#include "dragon_cuello.h"
#include "ply_reader.h"

Dragon_cuello::Dragon_cuello(){
    ply::read("plys/ed_cuello.ply", this->v, this->f);
}