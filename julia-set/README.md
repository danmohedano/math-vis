# Julia Set Visualizer

## Foundation

[Julia sets](https://en.wikipedia.org/wiki/Julia_set) are related to complex dynamics. These sets consist of values such that an arbitrarily small perturbation can cause drastic changes in the sequence of iterated function values. The behaviour is commonly described as "chaotic". 

The complex dynamical system chosen for this visualization is the family of complex quadratic polynomials, defined as:

$$
	f_c(z) = z^2 + c
$$

Where $c$ is a complex constant. By fixing some $R > 0$ such that $R^2 - R \geq |c|$, then the Julia set of the system will be:

$$
K(f_c) = \{z \in \mathbb{C} : \forall n \in \mathbb{N}, |f_{c}^{n}(z)|\leq R\}
$$

Where $f_{c}^{n}(z)$ is the $n$ th iteration of the function. The Julia set $J(f_c)$ is then defined as the boundary of $K(f_c)$. These sets can be visualized by plotting each value $z$ as a point in two dimensional space, and linking the color or brightness used to the amount of iterations needed until divergence (if any). This is referred to as an escape time algorithm.

## Examples

![julia-21508](https://user-images.githubusercontent.com/43313293/222982338-0ffeb666-be54-4233-87b8-b6bd43d784bb.png)

![julia-151386](https://user-images.githubusercontent.com/43313293/222982341-1b8b4109-0cc7-417d-baba-ddef815e821c.png)

![julia-156886](https://user-images.githubusercontent.com/43313293/222982344-48b6ec67-b57a-41aa-af33-b12838ae31b5.png)

![julia-13210](https://user-images.githubusercontent.com/43313293/222982348-52e52d69-2e95-49d6-a100-b41abb56318e.png)

![julia-159906](https://user-images.githubusercontent.com/43313293/222982349-79688e02-aa69-4211-af85-4562c0b96ce4.png)

## Implementation

As it is computationally impossible to check if a function iteration diverges at any point, the property is discretized with a limited amount of maximum iterations checked. By doing so, if a given value $z$ reaches the maximum number of iterations, it is considered as "convergent".

The coloring of the pixels is done using [Bernstein polynomials](https://en.wikipedia.org/wiki/Bernstein_polynomial) which allows to blend the three main R,G,B color curves for seemless transition between them.

Because the visualization computes the iterative function for every point (pixel), it is very expensive. To improve the performance, OpenMP is used for parallelization.


## Usage

The project is implemented using [OpenFrameworks](https://openframeworks.cc/) for the rendering. Because of this, you can simply import the project into Visual Studio and run it.

As for controls: 
- A GUI is integrated into the app that lets you control all parameters of the Julia set: constant, escape radius, maximum number of iterations allowed, dimensions of the image, zoom and colors used in the gradient.
- Arrow keys (`UP, DOWN, LEFT, RIGHT`): allows movement within the image.
- `s`: saves the image in `png` format. The path for the resulting image is `bin/data/` inside of the project.
- `z, x`: zoom in and out of the image.



## Sources
- [Wikipedia "Julia Set" page](https://en.wikipedia.org/wiki/Julia_set)
- [Pezza's Work video on the subject](https://www.youtube.com/watch?v=uc2yok_pLV4&list=PLXwWpgaYLTFeNuCf40dfIdQFH_WYSzkTE&index=15&t=142s)
- ["Efficiently generating the Mandelbrot and Julia sets", Luc de Jonckheere](https://theses.liacs.nl/pdf/2018-2019-JonckheereLSde.pdf)
