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

To show the results that this implementation can produce, I'm comparing an example taken from wikipedia to the result that my algorithm can give.
The following image is taken from the Sobel operator wikipedia page (<a href="https://en.wikipedia.org/wiki/Sobel_operator">Sobel operator</a>):
![Color picture of an engine](https://upload.wikimedia.org/wikipedia/commons/f/f0/Valve_original_%281%29.PNG)

and below the result of the application of the Sobel operator taken from wikipedia (left) is compared to the result that my implementation is able to produce (right):

Sobel operator wikipedia result             |  Sobel operator this implementation result
:-------------------------:|:-------------------------:
![](https://upload.wikimedia.org/wikipedia/commons/d/d4/Valve_sobel_%283%29.PNG)  |  ![](https://upload.wikimedia.org/wikipedia/commons/d/d4/Valve_sobel_%283%29.PNG)

instead the following image is the result of the application of the sobel operator to

<h1>
  Dependencies
</h1>

As already mentioned the only dependency is <a href="https://github.com/lvandeve/lodepng">lodepng</a>
