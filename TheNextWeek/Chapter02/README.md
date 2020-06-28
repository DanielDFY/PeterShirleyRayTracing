# Chapter 02

### Bounding volume hierarchy

![fig.bvol-hierarchy](note%20images/fig.bvol-hierarchy.jpg)



### Axis-Aligned Bounding Boxes (AABBs)

![fig.2daabb](note%20images/fig.2daabb.jpg)

2D axis-aligned bounding box



### Ray-slab intersection

 The ray can be thought of as just a function that given a *t* returns a location *P(t)*: ![](http://latex.codecogs.com/gif.latex?\mathbf{P}(t)%20=%20\mathbf{A}%20+%20t%20\mathbf{b})

Then we can get the t of hit points: ![](http://latex.codecogs.com/gif.latex?t_0%20=%20\frac{x_0%20-%20A_x}{b_x}) and ![](http://latex.codecogs.com/gif.latex?t_1%20=%20\frac{x_1%20-%20A_x}{b_x})

![fig.ray-slab](note%20images/fig.ray-slab.jpg)

If the ray is parallel to the plane, t<sub>0</sub> and t<sub>1</sub> will be undefined. And in 3D, those boundaries are planes.



### Ray-slab*t*-interval overlap

The key observation to turn that 1D math into a hit test is that for a hit, the *t*-intervals need to overlap.

![fig.rstio](note%20images/fig.rstio.jpg)

 In 2D the green and blue overlapping only happens if there is a hit.



### Ray Intersection with an AABB

Use ![](http://latex.codecogs.com/gif.latex?t_{x0}%20=%20\min(%20\frac{x_0%20-%20A_x}{b_x},%20\frac{x_1%20-%20A_x}{b_x})) and ![](http://latex.codecogs.com/gif.latex?t_{x1}%20=%20\max(%20\frac{x_0%20-%20A_x}{b_x},%20\frac{x_1%20-%20A_x}{b_x})) in case of ![](http://latex.codecogs.com/gif.latex?b_x%20=%200)

if ![](http://latex.codecogs.com/gif.latex?b_x%20=%200) and either ![](http://latex.codecogs.com/gif.latex?x_0%20-%20A_x%20=%200) or ![](http://latex.codecogs.com/gif.latex?x_1%20-%20A_x%20=%200) so we get a `NaN`. In that case we can probably accept either hit or no hit answer, but we’ll revisit that later.



### Splitting BVH Volumes

1. randomly choose an axis
2. sort the primitives (`using std::sort`)
3. put half in each subtree



### Output Display

Render with BVH.

![output](output.png)