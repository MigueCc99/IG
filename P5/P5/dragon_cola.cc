#include "dragon_cola.h"
#include "ply_reader.h"

Dragon_cola::Dragon_cola(){
    ply::read("plys/ed_cola.ply", this->v, this->f);
}