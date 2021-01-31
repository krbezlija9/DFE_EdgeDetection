# DFE_Edge_Detection

Edge detection of a picture.


Introduction
------------

* Edge detection takes a digital image with the help of various mathematical methods, draws lines ("edges") in the image at those places where the intensity of the image changes sharply/quickly
* The resulting image preserves some attributes of the original, even though it is a line drawing of the original image

Mathematical view
-----

* An edge in an certain point in the image represents the derivative of that point with respect to the rate of change in color
* To find an edge, edge detection calculates the derivative of each point in the image
* It considers all possible derivatives in all directions
* The most often used technique for finding the derivatives is convolution of the image with masks
* Convolution of the image with masks is done by multiplying a 3 x 3 bit of the original image by a 3 x 3 matrix, called the operator
* After the multiplication, the sum is taken and the result is written in the center point of the bit
* In our case, we used the Sharr operator

Usage
-----

* Edge detection is a fundamental tool used in image processing as well as machine learning and comupter vision
* The edges tell us where in the image we can find items, their size, shape and something about their texture
