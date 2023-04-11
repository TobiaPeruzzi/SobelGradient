# SobelGradient

This is a minimal implementation of Sobel Gradient. It has only one dependency: lodepng to load and write png files.
The code is organized in the following way:
- algorithms: contains the implementation of sobel convolution
- types: contains all type definition useful to perform sobel convolution
- lib: contains external libraries (only lodepng)

<h1>
  Parameters
</h1>

Only 2 parameters are used in this implementation:
- threshold: user-defined value to control how steep the gradient magnitude should be to be considered as an edge in the image
- smoothing: boolean parameter to control if the image should be smoothed before the application of the Sobel filter

<h1>
  Results
</h1>


<h1>
  Dependencies
</h1>

As already mentioned the only dependency is <a href="https://github.com/lvandeve/lodepng">lodepng</a>
