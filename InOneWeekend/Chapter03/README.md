# Chapter 03

### Ray

Think of a ray as a function `P(t)=A+tb`. Here `P` is a 3D position along a line in 3D. `A` is the ray origin and `b` is the ray direction. The ray parameter `t` is a real number.

![fig.lerp](note images/fig.lerp.jpg)



### Sending Rays Into the Scene

* Calculate the ray from the eye to the pixel.
* Determine which objects the ray intersects.
* Compute a color for that intersection point.

![fig.camera-geometry](note images/fig.camera-geometry.jpg)



### Output Display

A blue-to-white gradient depending on ray Y coordinate.

![output](output.png)

