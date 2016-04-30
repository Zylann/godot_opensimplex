#include "noise.h"

Noise::Noise() : Reference(), _context(NULL), _seed(0) {
    open_simplex_noise(_seed, &_context);
}

Noise::~Noise() {
    if (_context) {
        open_simplex_noise_free(_context);
    }
}

void Noise::set_seed(int seed) {
    if (seed == _seed)
        return;
    // This is not fair...
    if (_context)
        open_simplex_noise_free(_context);
    open_simplex_noise(seed, &_context);
    _seed = seed;
}

int Noise::get_seed() {
    return _seed;
}

void Noise::_bind_methods() {

    ObjectTypeDB::bind_method(_MD("get_seed"), &Noise::get_seed);
    ObjectTypeDB::bind_method(_MD("set_seed", "seed"), &Noise::set_seed);

    ObjectTypeDB::bind_method(_MD("get_noise_2d", "x", "y"), &Noise::get_noise_2d);
    ObjectTypeDB::bind_method(_MD("get_noise_3d", "x", "y", "z"), &Noise::get_noise_3d);
    ObjectTypeDB::bind_method(_MD("get_noise_4d", "x", "y", "z", "w"), &Noise::get_noise_4d);

    ObjectTypeDB::bind_method(_MD("get_noise_2dv", "pos"), &Noise::get_noise_2dv);
    ObjectTypeDB::bind_method(_MD("get_noise_3dv", "pos"), &Noise::get_noise_3dv);

}


FractalNoise::FractalNoise() : Reference(), _persistance(0.5), _octaves(3), _period(64), _lacunarity(2.0) {

}

float FractalNoise::get_noise_2d(float x, float y) {
    if (_noise.is_null())
        return 0;
    Noise & src = **_noise;

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
        sum += src.get_noise_2d(x, y);
    }

    return sum / max;
}

float FractalNoise::get_noise_3d(float x, float y, float z) {
    if (_noise.is_null())
        return 0;
    Noise & src = **_noise;

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
        sum += src.get_noise_3d(x, y, z);
    }

    return sum / max;
}

float FractalNoise::get_noise_4d(float x, float y, float z, float w) {
    if (_noise.is_null())
        return 0;
    Noise & src = **_noise;

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
        sum += src.get_noise_4d(x, y, z, w);
    }

    return sum / max;
}

void FractalNoise::_bind_methods() {

    ObjectTypeDB::bind_method(_MD("get_source_noise"), &FractalNoise::get_source_noise);
    ObjectTypeDB::bind_method(_MD("set_source_noise", "noise_instance"), &FractalNoise::set_source_noise);

    ObjectTypeDB::bind_method(_MD("set_octaves", "octave_count"), &FractalNoise::set_octaves);
    ObjectTypeDB::bind_method(_MD("get_octaves"), &FractalNoise::get_octaves);

    ObjectTypeDB::bind_method(_MD("set_period", "period"), &FractalNoise::set_period);
    ObjectTypeDB::bind_method(_MD("get_period"), &FractalNoise::get_period);

    ObjectTypeDB::bind_method(_MD("set_persistance", "persistance"), &FractalNoise::set_persistance);
    ObjectTypeDB::bind_method(_MD("get_persistance"), &FractalNoise::get_persistance);

    ObjectTypeDB::bind_method(_MD("set_lacunarity", "lacunarity"), &FractalNoise::set_lacunarity);
    ObjectTypeDB::bind_method(_MD("get_lacunarity"), &FractalNoise::get_lacunarity);

    ObjectTypeDB::bind_method(_MD("get_noise_2d", "x", "y"), &FractalNoise::get_noise_2d);
    ObjectTypeDB::bind_method(_MD("get_noise_3d", "x", "y", "z"), &FractalNoise::get_noise_3d);
    ObjectTypeDB::bind_method(_MD("get_noise_4d", "x", "y", "z", "w"), &FractalNoise::get_noise_4d);

    ObjectTypeDB::bind_method(_MD("get_noise_2dv", "pos"), &FractalNoise::get_noise_2dv);
    ObjectTypeDB::bind_method(_MD("get_noise_3dv", "pos"), &FractalNoise::get_noise_3dv);

}

