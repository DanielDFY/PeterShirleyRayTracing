# Chapter 03

### Texture Coordinates for Spheres

If we have a ![](http://latex.codecogs.com/gif.latex?(\theta,\phi)) in spherical coordinates, we just need to scale θ and ϕ to fractions. If θ is the angle down from the pole, and ϕ is the angle around the axis through the poles, the normalization to [0,1] would be:

![](http://latex.codecogs.com/gif.latex?u%20=%20\frac{\phi}{2\pi}), ![](http://latex.codecogs.com/gif.latex?v%20=%20\frac{\theta}{\pi})

To compute θ and ϕ, for a given hit point, the formula for spherical coordinates of a unit radius sphere on the origin is:

![](http://latex.codecogs.com/gif.latex?x%20=%20\cos(\phi)%20\cos(\theta)), ![](http://latex.codecogs.com/gif.latex?y%20=%20\sin(\phi)%20\cos(\theta)), ![](http://latex.codecogs.com/gif.latex?z%20=%20\sin(\theta))

Then do inverting with functions  in `<cmath>`:

![](http://latex.codecogs.com/gif.latex?\phi%20=%20\text{atan2}(y,%20x)), ![](http://latex.codecogs.com/gif.latex?\theta%20=%20\text{asin}(z))



### Output Display

![output](output.png)