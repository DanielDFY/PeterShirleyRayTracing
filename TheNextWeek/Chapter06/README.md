# Chapter 06

### Ray-rectangle intersection

![fig.ray-rect](note%20images/fig.ray-rect.jpg)

Recall that a ray ![](http://latex.codecogs.com/gif.latex?\mathbf{P}(t)%20=%20\mathbf{A}%20+%20t%20\mathbf{b}) has its z component defined by ![](http://latex.codecogs.com/gif.latex?P_z(t)%20=%20A_z%20+%20t%20b_z). Rearranging those terms we can get ![](http://latex.codecogs.com/gif.latex?t%20=%20\frac{k-A_z}{b_z}) where ![](http://latex.codecogs.com/gif.latex?z=k).

Once we have t, we can plug that into the equations for x and y: ![](http://latex.codecogs.com/gif.latex?x%20=%20A_x%20+%20t%20b_x), ![](http://latex.codecogs.com/gif.latex?y%20=%20A_y%20+%20t%20b_y)

It is a hit if ![](http://latex.codecogs.com/gif.latex?x_0%20%3C%20x%20%3C%20x_1) and ![](http://latex.codecogs.com/gif.latex?y_0%20%3C%20y%20%3C%20y_1).



### Output Display

Cornell box

![output](output.png)