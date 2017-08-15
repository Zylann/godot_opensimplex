#include "register_types.h"
#include "noise.h"

void register_opensimplex_types() {

    ClassDB::register_class<OsnNoise>();
    ClassDB::register_class<OsnFractalNoise>();

}

void unregister_opensimplex_types() {

}

