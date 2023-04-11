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
- smoothing: boolean parameter to control if the image should be smoothed before the application of the Sobel filter. Smoothing can be used to reduce noise
in the resulting image

<h1>
  Algorithm Fuction
</h1>

The algorithm works following these steps:
- the image is loaded from the path given using lodepng library, which returns a vecotr of RGBA pixels
- the RGBA pixels are organized in a matrix structure, that is a matrix in which every entry is represented by a custom type called RGBA, that is just
a group of four integers representing red, green, blue and transparency of the pixels
- the RGBA matrix is converted in a grayscale matrix (meaning a matrix in which every entry is just a single value)
- the grayscale matrix is the smoothed if the corresponding parameter is set to True
- the sobel operator is applied (both in x and y direction) to the grayscale matrix 
- values resulting from the application of the Sobel operator are filtered based on the threshold value specified by the user
- grayscale matrix is converted back to a vector of RGBA pixels in order to use lodepng to save a .png image

<h1>
  Results
</h1>

To show the results that this implementation can produce, I'm comparing an example taken from wikipedia to the result that my algorithm can give.
The following image is taken from the Sobel operator wikipedia page (<a href="https://en.wikipedia.org/wiki/Sobel_operator">Sobel operator</a>):
![Color picture of an engine](https://upload.wikimedia.org/wikipedia/commons/f/f0/Valve_original_%281%29.PNG)

and below the result of the application of the Sobel operator taken from wikipedia (left) is compared to the result that my implementation is able to produce (right):

Sobel operator wikipedia result             |  Sobel operator this implementation result
:-------------------------:|:-------------------------:
![](https://upload.wikimedia.org/wikipedia/commons/d/d4/Valve_sobel_%283%29.PNG)  |  ![](ComputerVision/convResult.png)

The result presented above in the image to the right, was obtained with a threshold of 20 and a pre-smoothing of the image.

Another result of this algorithm is shown below, where the image to the left was taken from the camera of my smartphone:

Smartphone photo             |  Sobel operator applied to the photo
:-------------------------:|:-------------------------:
![](ComputerVision/phone_img.png)  |  ![](ComputerVision/conv_phone_img.png)

<h1>
  Dependencies
</h1>

As already mentioned the only dependency is <a href="https://github.com/lvandeve/lodepng">lodepng</a>
