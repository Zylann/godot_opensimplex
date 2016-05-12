#include "noise.h"

OsnNoise::OsnNoise() : Reference(), _context(NULL), _seed(0) {
    open_simplex_noise(_seed, &_context);
}

OsnNoise::~OsnNoise() {
    if (_context) {
        open_simplex_noise_free(_context);
    }
}

void OsnNoise::set_seed(int seed) {
    if (seed == _seed)
        return;
    // This is not fair...
    if (_context)
        open_simplex_noise_free(_context);
    open_simplex_noise(seed, &_context);
    _seed = seed;
}

int OsnNoise::get_seed() {
    return _seed;
}

void OsnNoise::_bind_methods() {

    ObjectTypeDB::bind_method(_MD("get_seed"), &OsnNoise::get_seed);
    ObjectTypeDB::bind_method(_MD("set_seed", "seed"), &OsnNoise::set_seed);

    ObjectTypeDB::bind_method(_MD("get_noise_2d", "x", "y"), &OsnNoise::get_noise_2d);
    ObjectTypeDB::bind_method(_MD("get_noise_3d", "x", "y", "z"), &OsnNoise::get_noise_3d);
    ObjectTypeDB::bind_method(_MD("get_noise_4d", "x", "y", "z", "w"), &OsnNoise::get_noise_4d);

    ObjectTypeDB::bind_method(_MD("get_noise_2dv", "pos"), &OsnNoise::get_noise_2dv);
    ObjectTypeDB::bind_method(_MD("get_noise_3dv", "pos"), &OsnNoise::get_noise_3dv);

}


OsnFractalNoise::OsnFractalNoise() : Reference(), _persistance(0.5), _octaves(3), _period(64), _lacunarity(2.0) {

}

float OsnFractalNoise::get_noise_2d(float x, float y) {
    if (_noise.is_null())
        return 0;
    OsnNoise & src = **_noise;

    x /= _period;
    y /= _period;

    float amp = 1.0;
    float max = 1.0;
    float sum = src.get_noise_2d(x, y);

    unsigned int i = 0;
    while (++i < _octaves) {
        x *= _lacunarity;
        y *= _lacunarity;
        amp *= _persistance;
        max += amp;
        // TODO usually, we increase the seed here on every loop to avoid similarities...
        // But that would mean allocating a new osn_context for each!
        // So I fallback on X modification.
        x += _period;
        sum += src.get_noise_2d(x, y) * amp;
    }

    return sum / max;
}

float OsnFractalNoise::get_noise_3d(float x, float y, float z) {
    if (_noise.is_null())
        return 0;
    OsnNoise & src = **_noise;

    x /= _period;
    y /= _period;
    z /= _period;

    float amp = 1.0;
    float max = 1.0;
    float sum = src.get_noise_3d(x, y, z);

    unsigned int i = 0;
    while (++i < _octaves) {
        x *= _lacunarity;
        y *= _lacunarity;
        z *= _lacunarity;
        amp *= _persistance;
        max += amp;
        x += _period;
        sum += src.get_noise_3d(x, y, z) * amp;
    }

    return sum / max;
}

float OsnFractalNoise::get_noise_4d(float x, float y, float z, float w) {
    if (_noise.is_null())
        return 0;
    OsnNoise & src = **_noise;

    x /= _period;
    y /= _period;
    z /= _period;
    w /= _period;

    float amp = 1.0;
    float max = 1.0;
    float sum = src.get_noise_4d(x, y, z, w);

    unsigned int i = 0;
    while (++i < _octaves) {
        x *= _lacunarity;
        y *= _lacunarity;
        z *= _lacunarity;
        w *= _lacunarity;
        amp *= _persistance;
        max += amp;
        x += _period;
        sum += src.get_noise_4d(x, y, z, w) * amp;
    }

    return sum / max;
}

void OsnFractalNoise::_bind_methods() {

    ObjectTypeDB::bind_method(_MD("get_source_noise"), &OsnFractalNoise::get_source_noise);
    ObjectTypeDB::bind_method(_MD("set_source_noise", "noise_instance"), &OsnFractalNoise::set_source_noise);

    ObjectTypeDB::bind_method(_MD("set_octaves", "octave_count"), &OsnFractalNoise::set_octaves);
    ObjectTypeDB::bind_method(_MD("get_octaves"), &OsnFractalNoise::get_octaves);

    ObjectTypeDB::bind_method(_MD("set_period", "period"), &OsnFractalNoise::set_period);
    ObjectTypeDB::bind_method(_MD("get_period"), &OsnFractalNoise::get_period);

    ObjectTypeDB::bind_method(_MD("set_persistance", "persistance"), &OsnFractalNoise::set_persistance);
    ObjectTypeDB::bind_method(_MD("get_persistance"), &OsnFractalNoise::get_persistance);

    ObjectTypeDB::bind_method(_MD("set_lacunarity", "lacunarity"), &OsnFractalNoise::set_lacunarity);
    ObjectTypeDB::bind_method(_MD("get_lacunarity"), &OsnFractalNoise::get_lacunarity);

    ObjectTypeDB::bind_method(_MD("get_noise_2d", "x", "y"), &OsnFractalNoise::get_noise_2d);
    ObjectTypeDB::bind_method(_MD("get_noise_3d", "x", "y", "z"), &OsnFractalNoise::get_noise_3d);
    ObjectTypeDB::bind_method(_MD("get_noise_4d", "x", "y", "z", "w"), &OsnFractalNoise::get_noise_4d);

    ObjectTypeDB::bind_method(_MD("get_noise_2dv", "pos"), &OsnFractalNoise::get_noise_2dv);
    ObjectTypeDB::bind_method(_MD("get_noise_3dv", "pos"), &OsnFractalNoise::get_noise_3dv);

}

