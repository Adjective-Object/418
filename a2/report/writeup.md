---
title: CSC418 (Computer Graphics) Assignment 1
author: Maxwell Huang-Hobbs
date: Monday October 5, 2015
bibliography: writeup-library.bib
csl: chicago.csl
---

# Part A: Questions
1.  a. We know three points of correspondence, so we can show how A transforms the matrix of the input points into the matrix of the output points. This results in the following equations (full expansion of solving for the inverse and multiplying matricies in the appendix)
    \begin{equation}\begin{split}
    \left\lbrack
        \begin{array}{ccc}
            &   & \\
            & A & \\
            &   &
        \end{array}
    \right\rbrack
    \left\lbrack
        \begin{array}{ccc}
            2 & 1 &  3 \\
            1 & 2 & -1 \\
            3 & 1 &  1
        \end{array}
    \right\rbrack &=
    \left\lbrack
        \begin{array}{ccc}
            10 & 8 & 2 \\
            8  &-4 & 0 \\
            1  & 1 & 1
        \end{array}
    \right\rbrack\\
    \left\lbrack
        \begin{array}{ccc}
            &   & \\
            & A & \\
            &   &
        \end{array}
    \right\rbrack &=
    \left\lbrack
        \begin{array}{ccc}
            10 & 8 & 2 \\
            8  &-4 & 0 \\
            1  & 1 & 1
        \end{array}
    \right\rbrack
    \left\lbrack
        \begin{array}{ccc}
            2 & 1 &  3 \\
            1 & 2 & -1 \\
            3 & 1 &  1
        \end{array}
    \right\rbrack^{-1}\\
    \left\lbrack
        \begin{array}{ccc}
            &   & \\
            & A & \\
            &   &
        \end{array}
    \right\rbrack &=
    \left\lbrack
        \begin{array}{ccc}
            10 & 8 & 2 \\
            8  &-4 & 0 \\
            1  & 1 & 1
        \end{array}
    \right\rbrack
    \left\lbrack
        \begin{array}{ccc}
            0.6  & 0.4  & -1.4 \\
            -0.8 & -0.2 &  2.2 \\
            0.2  & -0.2 &  0,1
        \end{array}
    \right\rbrack\\
    \left\lbrack
        \begin{array}{ccc}
            &   & \\
            & A & \\
            &   &
        \end{array}
    \right\rbrack &=
    \left\lbrack
        \begin{array}{ccc}
            0 & 2 &   4 \\
            8 & 4 & -20 \\
            0 & 0 & 1
        \end{array}
    \right\rbrack\\
    \end{split}\end{equation}

    b. A general 2d homography is 9 degrees of freedom. Each point gives 2 equations (x/y correspondence), so we need 5 points.  
        A rigid 2d transformation is 3 degrees of freedom (rotation / translation/ flip). Each point gives 2 equations, so we need 2 points.

    c.  i. The centroid of a triangle Is preserved through any affine transformation. Affine transformations maintain the ratio of sizes of colinear lines, so if we construct the following lines through the centroid of triangle $\Delta abc$,
            \begin{figure}[!h]
            \centering
            \begin{tikzpicture}
                \draw(0,0)     node[name=a, label=left:{$a$}] {};
                \draw(2,0)     node[name=b, label=right:{$b$}] {};
                \draw(1, 1.73) node[name=c, label=above:{$c$}] {};

                \draw(1, 0.865) node[name=k,  label=below:{$k$}] {};

                \draw(1.5, 0.866) 
                    node[name=am, label={[xshift=0.2cm, yshift=0cm]{$a'$}}] {};
                \draw(0.5, 0.866) 
                    node[name=bm, label={[xshift=-0.2cm, yshift=0cm]{$b'$}}] {};
                \draw(1, 0) node[name=cm,  label=below:{$c'$}] {};

                \draw[-](a)--(b);
                \draw[-](b)--(c);
                \draw[-](c)--(a);

                \draw[dotted](a)--(am);
                \draw[dotted](b)--(bm);
                \draw[dotted](c)--(cm);

                \fill (a) circle [radius=1pt];
                \fill (b) circle [radius=1pt];
                \fill (c) circle [radius=1pt];
                \fill (am)  circle [radius=1pt];
                \fill (bm)  circle [radius=1pt];
                \fill (cm)  circle [radius=1pt];
            \end{tikzpicture}
            \end{figure}
            Note that $a', b', c'$ will always be at the midpoints of $\overline{bc}, 
            \overline{ac}, \overline{bc}$, respectively. After we transform this triangle, we can expect this property to hold,. Therefore, the centroid of the transformed triangle will be the same as the transform of the centoid of the original triangle.

        ii. The same does not hold for the orthocenter of a triangle. 
            Take the equilateral triangle

            $\Delta A=(0,0), B=(0,1), C=(0.5, \sqrt{3})$.
            
            Since it's an equilteral triangle, we know that we can construct a right triangle by drawing a line from the midpoint of one side to the opposite point, so the orthocenter is at the center of the triangle, $(0.5, \frac{\sqrt{3}}{3})$.

            If we scale this triangle by $(0,\frac{3}{\sqrt{3}})$ vertically, we get the triangle 
            $\Delta A'=(0,0), B'=(0,1), C'=(0.5,1)$. 

            First we calculate the inward facing normals of each of the lines
            \begin{equation}
            \begin{split}
            N_{AB} = N_{(0, 1)} = (0,1)\\
            N_{AC} = N_{(0.5, 1)} = (-1,0.5)\\
            N_{BC} = N_{(-0.5, 1)} = (1, 0.5)\\
            \end{split}
            \end{equation}

            Add each of these vectors to the remaining point and find the intersection to find the orthocenter:
            \begin{equation}
            \begin{split}
            C' + c(0,1) &= B' + b(0.5,1) = A' + a(-0.5, 1)\\
            (0.5, 1) + (0,c) &= (1,0) + (\frac{b}{2}. b) = (-\frac{a}{2}, a)
            \end{split}
            \end{equation}

            Solving this system of equations for their intersection gives us the point $(0,5, -1)$, which does not equal $(0.5, 1)$, the transform of the orthocenter of the original triangle.



2.  a. i. The lens moves light over a large oening to the corresponding points on an image plane in a camera.

        ii. The aperature of a camera is the size of the opening through which light is allowed to enter. Increasing its size allows more light to enter, which causes the photosensitive material on the image plane to react more than it would to less light. this allows for equivalently bright images to be captured over smaller time intervals, and so is useful for taking pictures of quick moving actions.  

        iii. The focal length determines the distance from the camera lens at which the incoming light rays to the lens will be properly redirected to the image plane. 

    b. \includegraphics[width=.5\textwidth]{lenses.png}

    \clearpage
    \newpage

    c. Given $c = (0,0,0), d = (0,0,1), p=(p_x, p_y, p_z)$. Using similar triangles to project p back on to d (assume that p is beyond the rendering plane, otherwise it should have been discarded earlier in the pipeline)...
        \begin{figure}[!h]
        \centering
        \begin{tikzpicture}
            \draw(0,0)     node[name=c, label=left:{$c$}] {};
            \draw(4,0)     node[name=t2] {};
            \draw(4, -2) node[name=p, label=right:{$p$}] {};

            \draw(2,1)     node[name=d1] {};
            \draw(2,-1.5)     node[name=d2, label=right:{$d$}] {};

            \draw[dotted](c)--(t2);
            \draw[dotted](c)--(p);
            \draw[dotted](t2)--(p);

            \draw[-](d1)--(d2);
            \fill (p) circle [radius=1pt];
            \fill (c) circle [radius=1pt];
        \end{tikzpicture}
        \end{figure}
        projected point $p \rightarrow q$ will have
        $q_x = p_x * d / p_z$,
        $q_y = p_y * d / p_z$

    d.  i. Parallel lines will remain parallel if they are on a plane perpendicualar to the viewing axis (or parallel to the projection surface)
        ii. 2 parallel lines can be expressed as
            $l0(t) = p_0 +vt$ and $l1(t) = p_1 +vt$, where $p0$ is some point on line 0 and $p1$ is some point on l1. v is the slope vector of the lines, which is shared (because they are parallel), and assumped to be pointed away from the camera (positive z).

            $$\text{perspective}(l0(t)) = (
                \frac{P_{0,x} + V_x t}{P_{0,z} + V_z t},
                \frac{P_{0,y} + V_xyt}{P_{0,z} + V_z t})$$

            $$\text{perspective}(l1(t)) = (
                \frac{P_{1,x} + V_x t}{P_{1,z} + V_z t},
                \frac{P_{1,y} + V_xyt}{P_{1,z} + V_z t})$$
            
            as t approaches infinity, this approaches

            $$\text{perspective}(l1(t)) = \text{perspective}(l1(t)) = 
                (\frac{V_x}{V_z}, \frac{V_y}{V_z})$$


3.  a.  The normal to an implicit surface is the gradient w/ respect to each of its parameters
    \begin{equation}
    \begin{split}
    \frac{\delta}{\delta x} f(x,y,z)_x &= 
    \frac{\delta}{\delta x}[(r-(x^2+y^2)^{1/2})^2 + z^2 - r^2]\\
    &=2(R-(x^2 + y^2)^{1/2}) * (-1/2(x^2 + y^2)) * 2x\\
    \frac{\delta}{\delta y} f(x,y,z)_y &= 
    \frac{\delta}{\delta y}[(r-(x^2+y^2)^{1/2})^2 + z^2 - r^2]\\
    &=2(R-(x^2 + y^2)^{1/2}) * (-1/2(x^2 + y^2)) * 2y\\
    \frac{\delta}{\delta x} f(x,y,z)_z &= 2z
    \end{split}
    \end{equation}

    b. We want the vector $p \rightarrow$ (some point on the plan) to be perpendicular to the normal, so.. \\
        $0 = N \cdot ((x,y,z) - p)$
        where N is the Normal to the plane at point p ($\nabla f(p)$).
    c. For any $\lambda$, $f(q(\lambda)) = 0$, so $q(\lambda)$ is on the surface 
        \begin{equation}
        \begin{split}
        q(\lambda = (R\cos \lambda, R\sin \lambda, r) &\\
        f(R\cos \lambda, R\sin \lambda, r) &= 
            (R - \sqrt{R\cos^2 \lambda + R\sin ^2 \lambda})^2 + r^2 - r^2\\
        &= (R - \sqrt{R^2 * \cos^2\lambda + \sin^2\lambda})\\
        &= (R - R)\\
        &= 0
        \end{split}
        \end{equation}
    d.  The tangent is equal to the derivative of component of the surface
        \begin{equation}
        \begin{split}
        q(\lambda) & = (R\cos \lambda, R\sin \lambda, r)\\
        \frac{d}{dx} q(\lambda)_x &= R\sin\lambda\\
        \frac{d}{dy} q(\lambda)_y &= -R\cos\lambda\\
        \frac{d}{dz} q(\lambda)_z &= 0\\
        \end{split}
        \end{equation}
    e. the point is given by $q(\lambda)$ and the corresponding tangeint is  given by $q'(\lambda)$
        \begin{equation}
        \begin{split}
        N_x * q'(\lambda)_x
            &= 2(R-(x^2 + y^2)^{1/2}) * (-1/2(x^2 + y^2)) * 2x * R\sin\lambda\\
            &= 2(R-(R\cos^2\lambda + R\sin^2\lambda)^{1/2}) 
                * -1/2(R\cos^2\lambda + R\sin^2\lambda)
                * 2\cos\lambda
                * R\sin\lambda \\
            &= 2(R-1)
                * -1/2
                * 2\cos\lambda
                * R\sin\lambda \\
            &= 2R * (R-1)
                * \cos\lambda \sin\lambda \\
        N_y * q'(\lambda)_y
            &= 2(R-(x^2 + y^2)^{1/2}) * (-1/2(x^2 + y^2)) * -2R\cos\lambda * R\cos\lambda\\
            &= -2R * (R-1)
                * \sin\lambda \cos\lambda \\
        N_z * q'(lambda)_z &= .... * 0
        N_x * q'(\lambda)_x + N_y * q'(\lambda)_y + = 0
        N \cdot q'(lambda) = 0
        \end{split}
        \end{equation}
        So Then it falls on the plane

4.  a. Yes, $b, i, g, h,$ and $d can all be ignored through backface culling (they face away from the eye)
    b. In the below tree, the left child of any node is the spacee behind the face, and the right child is the space in front of the face. Face h is crossed twice, once by the plane of $b$ and once by the plane of $a$.

        \begin{multicols}{2}
            \includegraphics[width=.5\textwidth]{btree.png}
            \vfill\columnbreak

            \begin{tikzpicture}
              \SetGraphUnit{1}
              \Vertex{a}
              \SOEA(a){b}
              \SOWE(a){h3}
              \SOEA(b){f}
              \SOEA(f){h1}
              \SOWE(b){c}
              \SOWE(c){d}
              \SOWE(d){e}
              \SOEA(c){g}
              \SOEA(g){i}
              \SOWE(g){h2}

              \Edge(a)(b)
              \Edge(a)(h3)
              \Edge(b)(f)
              \Edge(b)(c)
              \Edge(f)(h1)
              \Edge(c)(d)
              \Edge(c)(g)
              \Edge(d)(e)
              \Edge(g)(h2)
              \Edge(g)(i)
            \end{tikzpicture}
            
        \end{multicols}
    c. The step by step expansion is...
        \begin{equation}
        \begin{split}
            & \{a_{back}, a, a_{front}\}\\
            & \{h3, a, b_{front}, b, b_{back}\}\\
            & \{h3, a, b_{back}, f, f_{front}, b, c_{back}, c, c_{front}\}\\
            & \{h3, a, f, h, b, d_{front}, d, d_{back}, c, g_{front}, g, g_{back} \}\\
            & \{h3, a, f, h1, b, d, el, c, i, g, h2\}\\
        \end{split}
        \end{equation}
