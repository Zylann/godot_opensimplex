#include "register_types.h"
#include "noise.h"

void register_opensimplex_types() {

    ObjectTypeDB::register_type<OsnNoise>();
    ObjectTypeDB::register_type<OsnFractalNoise>();

}

void unregister_opensimplex_types() {

}

