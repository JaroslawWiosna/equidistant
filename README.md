# EQUIDISTANT

Imagine a [closed line segment](https://en.wikipedia.org/wiki/Line_segment) with two or more points randomly put on it. It is unlikely that the points would be equidistant.

> [equidistant](http://www.thefreedictionary.com/equidistant) - equally distant.
> By this term I mean that the distance from point to the closest neighbour is the same as from any other point to its closest neighbour. Also the distance should be as large as possible. 

...but we know that putting the points in one dimentional line is no a big deal. One has to simply... It doesn't matter. No one cares about points.

So let's make next step: What about 2D?

Here is an analogy:

Imagine [cow grazing](http://dictionary.cambridge.org/dictionary/english/graze).
Each animal wants to be as far away from another as possible, so it can eat grass in peace.

Let's make next step: What about sphere?
Nowadays it is belived that people have to think globally. Let's make an assumption that Earth is not flat. In fact Earth is a huge sphere.

What is the algorithm for equidistance the points on a sphere? But is it even possible?

Yes, it is, but only for [platonic solids](https://en.wikipedia.org/wiki/Platonic_solid)

The ultimate question of this project is: 
What will happen if we want to make five or seven equidistanced on a sphere?

### TO-DO LIST

 [ ] - implement an algorithm for 4, 6, 8, 12, 20
 [ ] - check what is going to happen when thera are 5, 7 points.



### VISUALIZATION


## MEANING
[whats-the-word-for-having-the-same-distance-to-neighbours](http://english.stackexchange.com/questions/318094/whats-the-word-for-having-the-same-distance-to-neighbours/318257)

https://www.physicsforums.com/threads/uniform-grid-of-points-on-a-sphere.649761/#post-4294920
http://mathworld.wolfram.com/SpherePointPicking.html

# TROUBLESHOTING
 sudo apt-get install libvtk6-dev tcl-vtk
 sudo ln -s /usr/lib/x86_64-linux-gnu/libproj.so.9 /usr/lib/x86_64-linux-gnu/libproj.so 
