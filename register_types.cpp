#include "register_types.h"
#include "noise.h"

void register_opensimplex_types() {

    ObjectTypeDB::register_type<Noise>();
    ObjectTypeDB::register_type<FractalNoise>();

}

void unregister_opensimplex_types() {

}

