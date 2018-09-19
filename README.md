OpenSimplex Godot integration
=================================

This is a simple wrapping of the OpenSimplex C library, designed to avoid the patent issue on Simplex noise.
The master branch is for Godot 3.x series.
For Godot 2.x, checkout branch `godot2`.

IMPORTANT: Godot 3.1 now integrates OpenSimplex under a very similar API,
as a result this module is no longer maintained in Godot 3.1 onwards.

Install
----------

You have to get the source code of Godot to compile it with the module.
Copy the contents of the repository inside an `opensimplex` directory under Godot's `modules` folder.
The name is important for the module to compile properly.

Example git command:
`git clone https://github.com/Zylann/godot_opensimplex.git opensimplex`

Example usage
-----------------

```gdscript
# Create basic open-simplex noise
var noise = OsnNoise.new()
noise.set_seed(666)

# Get values
noise.get_noise_3d(x, y, t)

# Create fractal noise helper
var fractal_noise = OsnFractalNoise.new()
fractal_noise.set_source_noise(noise)
fractal_noise.set_period(64)
fractal_noise.set_octaves(4)
fractal_noise.set_persistance(0.5)

# Get values
fractal_noise.get_noise3d(x, y, t)
```

Preview
-------

![3D noise screenshot](screenshot.png)
3D noise


Notes
-------

I'm not happy yet with the design, as you can see there are two steps before you can generate fractal noise.
This is mainly because the open-simplex C library allocates memory for a context everytime the seed is chosen.
There could be a Noise singleton with a global seed, but I'm not a big fan of globals.

I was initially going to integrate FastNoise because it doesn't allocates memory at all, is optimized and has more features,
but because of Simplex patent issues this is not possible yet. A good tradeoff would be to propose a pull request to FastNoise :)
