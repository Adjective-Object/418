---
title: CSC418 (Computer Graphics) Assignment 1
author: Maxwell Huang-Hobbs
date: Monday October 5, 2015
bibliography: writeup-library.bib
csl: chicago.csl
---

# Part A: Questions

1.  a. \textbf{Find the tangent vector to the wiggly-ellipse as a function of the time.}

        \begin{equation}
        \begin{split}
        v_x(t) &= 4 \text{cos}(2\pi t) + \frac{1}{16} \text{cos}(32\pi t) \\
        v_y(t) &= 2 \text{sin}(2\pi t) + \frac{1}{16} \text{sin}(32\pi t) \\
        \text{with } u &= \frac{dv}{dt} \\
        u_x(t) &= -8\pi \text{sin}(2\pi t) - 2\pi sin(32 \pi t) \\
        u_y(t) &= 4\pi \text{cos}(2\pi t) + 2\pi cos(32 \pi t)  \\
        \end{split}
        \end{equation}

        Since the derivative of a parametric curve is the same as the derivative of its components, $u$ is the tangent to $v$ at time $t$.

    b. \textbf{Find the normal vector}

        in 2d space, the normal vector to a line has slope equal to $m_n = \frac{-1}{m_v}$ $u = \frac{dv}{dt}$, so $n$, the normal vector to $v$ at any point in time has

        $$n_x(t) = u_y(t)  = 4\pi \text{cos}(2\pi t) + 2\pi cos(32 \pi t)$$
        $$n_x(t) = -u_x(t) = 8\pi \text{sin}(2\pi t) + 2\pi sin(32 \pi t)$$

    c. \textbf{Is the curve symmetric around the X-axis? Y-axis?}

        $v$ can be thought of as the sum of two ellipses with different periods,
        \begin{equation}
        \begin{split}
        a_x(t) &= 4 \text{cos}(2\pi t) \\
        a_y(t) &= 2 \text{sin}(2\pi t) \\
        b_x(t) &= \frac{1}{16} \text{cos}(32\pi t) \\
        b_y(t) &= \frac{1}{16} \text{sin}(32\pi t) \\
        \end{split}
        \end{equation}

        An ellipse is symmetric about both the x and the y axies, so we know that $a_x$ is symmetric about the x and y axies. If we trace the value of $a$ over the ranges $t=(0 .. 0.5)$ and $t=(0 .. -0.5)$, we see that $v$ is symmetrical about the x axis, because the following relationships hold between a at $t$ and $-t$.

        \clearpage
        \newpage


        \begin{figure}[!h]
        \centering
        \begin{minipage}{.2\textwidth}
        \begin{tikzpicture}
        \draw[->](0,0) arc (0:-178:1);
        \draw[->](0,0) arc (0:178:1);
        \fill(0,0) circle [radius=2pt];
        \end{tikzpicture}
        \end{minipage}%
        \begin{minipage}{.2\textwidth}
        \begin{equation}
        \begin{split}
        a_x(t) & =  a_t(0.5 - t) \\
        a_y(t) & = -a_x(0.5 - t) \\
        \end{split}
        \end{equation}
        \end{minipage}
        \caption{paths of corresponding points traced from left to right of the ellipse}
        \end{figure}

        Since $v(t) = a(t) + b(t)$, x will only be symmetric about a given axis if the same property holds for $b$ over the same ranges.

        \begin{align*}
            b_x(t) &= b_x(-t) &&\text{(assert that $b_x$ symmetric in the x axis)} \\
            \text{cos}(32 \pi t) &= \frac{1}{16} \text{cos}(32 \pi (-t)) \\
            \text{cos}(32 \pi t) &= \text{cos}(-32 \pi t) \\
            \text{cos}(t) &= \text{cos}(-t)  && \text{(known true)}\\\\
            b_y(t) &= -b_y(-t) &&\text{(assert that $b_y$ symmetric in the y axis)} \\
            \frac{1}{16}\text{sin}(32 \pi t) &= -\frac{1}{16} \text{sin}(32 \pi (-t)) \\
            \text{sin}(32 \pi t) &= -\text{sin}(-32 \pi t) \\
            \text{sin}(t) &= -\text{sin}(-t)  && \text{(known true)}
        \end{align*}

        so $v$ is symmetric about the x axis

        \begin{figure}[!h]
        \centering
        \begin{minipage}{.2\textwidth}
        \begin{tikzpicture}
        \draw[->](0,0) arc (90:-88:1);
        \draw[->](0,0) arc (90:268:1);
        \fill(0,0) circle [radius=2pt];
        \end{tikzpicture}
        \end{minipage}%
        \begin{minipage}{.2\textwidth}
        \begin{equation}
        \begin{split}
        a_x(t) & = -a_x(0.5-t), t \in [0.25,0.75]\\
        a_y(t) & = a_y(0.5-t), t \in [0.25,0.75] \\
        \end{split}
        \end{equation}
        \end{minipage}
        \caption{paths of equal points traced from top to bottom of the ellipse}
        \end{figure}

        \begin{align*}
            b_x(t) &= -b_x(0.5-t), & t\in(0,25, 0.75) &&\text{(assert that $b_y$ symmetric about the y axis)} \\
            \frac{1}{16}\text{cos}(32 \pi t) &= \frac{1}{16} \text{cos}(32 \pi (0.5-t)), &t\in[0.25, 0.75] \\
            \text{cos}(2\pi t) &= \text{cos}(\pi - 2 \pi t), &t\in[0.25, 0.75] \\
            \text{cos}(t) &= \text{cos}(\pi - t), & t\in[\frac{\pi}{2}, \frac{3}{2}\pi] \\
            \text{cos}(\frac{\pi}{2} + t) &= \text{cos}(\frac{\pi}{2} - t), & t\in[0, \pi]\\
            1 &= 0 & \text{(for $t=\pi$)} && \text{(contradiction)}
        \end{align*}

        Therefore v not symmetric about the y axis.

    d. \textbf{What is the formula to compute this curve’s perimeter?}

        The curve intersects itself at $t=1$, so the perimeter is the sum of the changes in position from $t=0$ to $t=1$
        $$\int_0^1 (u_x(t)^2( + u_y(t)^2)^2dt$$

    e. \textbf{How can one piecewise approximate this perimeter?}

        walk along the curve in $n$ discrete time steps, summing the resulting differences

        $$\sum_{n=1}^N( [v_x(n/N) - v_x((n-1)/N] ^2 +
                          [v_y(n/N) - v_y((n-1)/N] ^2 )$$

2. Given the following doughnut:
    \begin{figure}[!h]
    \centering
    \begin{tikzpicture}

        \draw(0,0) circle (1cm);
        \draw(0,0) circle (2cm);
        \draw(0,0) node[label=left:{$p_1$}, name=center] {};

        \draw[-](0,0)--(0,1) node[label=above:{$r_0$}, name=r1] {};
        \draw[-](0,0)--(1.41, 1.41) node[label=right:{$r_1$}, name=r2] {};

        \draw[<->](-2,-2)--(4,1)
            node[label=above:{$\lambda d$}, name = line] {};
        \draw(-2,-2) node[label=above:{$p_0$}, name=control] {};

        \fill (center) circle [radius=2pt];
        \fill (r1) circle [radius=2pt];
        \fill (r2) circle [radius=2pt];

        \fill (control) circle [radius=2pt];

    \end{tikzpicture}
    \end{figure}

    a. \textbf{What is the area of the doughnut?}

        $2 \pi {r_1} ^ 2 - 2 \pi {r_0} ^ 2$

    b. \textbf{How many intersections between the line and the boundary of the doughnut can you have?}

        you can have between 0 & 4 intersections between a line and a doughnut's surface (no intersections, tangent to the outside circle, intersecting the outside circle twice but not the inner circle, tangent to the inner circle, or intersecting both circles twice)

    c. \textbf{Describe an algorithm to determine the number of intersections between the surface of a doughnut and a line}

        project vector $\overrightarrow{p_0,p_1}$ onto $d$ by taking the cross product $\overrightarrow{p_0p_1} \times d$. This is the point on line $p_0 + \lambda d$ closest to $p_1$. Then, switch on the distance

    $$\text{numCollissions}(d) = \left\{
        \begin{array}{ll}
              4   & d < r_0 \\
              3   & d = r_0 \\
              2   & r_0 < d < r_2 \\
              1   & d = r_2 \\
              0   & r_2 < d \\
        \end{array}
    \right.
    $$

    d. \textbf{Describe an algorithm to determine the locations of intersections between the surface of a doughnut and a line}

        as in part (c.), project vector $\overrightarrow{p_0,p_1}$ onto $d$ to get the point on $d$ closest to $p_1$. Call this point $m$. let $d = \norm{\overrightarrow{m,p_0}}$ Construct the following right triangle and solve for the length of e

        \begin{figure}[!h]
        \centering
        \begin{tikzpicture}
            \draw(-1,-1)     node[name=a] {};
            \draw[-](1,-1)   node[name=b] {};
            \draw[-](1, 0.5) node[name=c] {};

            \draw[-](a)--(b) node[midway,below] {$e$};
            \draw[-](b)--(c) node[midway,right] {$d$};
            \draw[-](a)--(c) node[midway,left] {$r_0$};

            \fill (a) circle [radius=2pt];
            \fill (b) circle [radius=2pt];
            \fill (c) circle [radius=2pt];

        \end{tikzpicture}
        \end{figure}

        \begin{equation} \label{eq1}
        \begin{split}
        e^2 + d^2 & = {r_0}^2 \\
        e & = \sqrt{{r_0}^2 - d^2}
        \end{split}
        \end{equation}

        repeat this process substituting $r_1$ for $r_0$.

    e. \textbf{If the line and donut are both transformed by a non-uniform scale $(S_x, S_y)$ around the origin, how do the number of intersections and their locations change?}

        There is no change in the number of intersections. Their locations are changed by scaling by a factor of $(S_x, S_y)$

    f. \textbf{How do the number of intersection(s) and their location(s) change if this transformation is only applied to the donut?}

        Scaling the doughnut by the nonuniform factor $S_x, S_y$ is the same as scaling the line by $(\frac{1}{S_x}, {\frac{1}{S_y}})$ in the reference frame of the doughnut. We can therefore maintain the assumption of a uniform circle and recompute the number / location of intersections using the algorithms from parts (c.) and (d.) with the original circle and the new line $p(\lambda) = \left\lbrack
            \begin{array}{c}
                \frac{1}{S_x} p_{0,x}\\
                \frac{1}{S_y} p_{0,y}\\
            \end{array}
        \right\rbrack + \lambda \left\lbrack
            \begin{array}{c}
                \frac{1}{S_x} d_x\\
                \frac{1}{S_y} d_y\\
            \end{array}
        \right\rbrack$

3.  \textbf{Prove / disprove the commutativity of the following transforms:}

    a. \textbf{Translation and Uniform Scale})

        Translation and uniform scale do not commute

        Take some point $p=(0,3), a translation $(0,1)$ and a scale by $(2,2)$.
        If the translation is applied first, the result is
            $$(0,3) \overset{translate}\rightarrow (0,4) \overset{scale}\rightarrow (0, 8)$$
        However, if the scale is applied first, the result is
            $$(0,3) \overset{scale}\rightarrow (0,6) \overset{translate}\rightarrow (0, 7)$$

    b. \textbf{Translation and Nonuniform Scale}

        Translation and nonuniform scale do not commute

        Take some point $p=(0,3), a translation $(0,1)$ and a scale by $(1,2)$.
        If the translation is applied first, the result is
            $$(0,3) \overset{translate}\rightarrow (0,4) \overset{scale}\rightarrow (0, 8)$$
        However, if the scale is applied first, the result is
            $$(0,3) \overset{scale}\rightarrow (0,6) \overset{translate}\rightarrow (0, 7)$$

    c. \textbf{Scaling and Rotation}

        Scaling and rotation do not commute.

        Take some point $p=(0, 3), a rotation by $90\deg$ and a scale by $(1, 2)$.
        If the rotation is applied first, the result is
            $$(0, 3) \overset{rotation}\rightarrow (3, 0) \overset{scale}\rightarrow (3, 0)$$
        However, if the scale is applied first, the result is
            $$(0, 3) \overset{scale}\rightarrow (0, 6) \overset{rotation}\rightarrow (6, 0)$$


    d. \textbf{Scaling and Scaling, not sharing the same fixed points}

        Scaling and scaling always commute, so scaling will always commute with scaling even if they have different fixed points. take the following two scale operations

        $$
        \left\lbrack
            \begin{array}{cccc}
                S_{2,1} & 0 & .. & 0 \\
                0 & S_{2,2} & .. & 0 \\
                .. & .. & .. & .. \\
                0 & 0 & .. & S_{2,n} \\
            \end{array}
        \right\rbrack
        \left(
        \left\lbrack
            \begin{array}{cccc}
                S_{1,1} & 0 & .. & 0 \\
                0 & S_{1,2} & .. & 0 \\
                .. & .. & .. & .. \\
                0 & 0 & .. & S_{2,n} \\
            \end{array}
        \right\rbrack
        \left\lbrack
            \begin{array}{cccc}
                P_1 \\
                P_2 \\
                .. \\
                P_n \\
            \end{array}
        \right\rbrack
        \right)
        $$

        The result of this product is $\left\lbrack
            \begin{array}{cccc}
                S_{1,1} * S_{2,1} * P_1 \\
                S_{1,2} * S_{2,2} * P_1 \\
                .. \\
                S_{1,n} * S_{2,n} * P_n \\
            \end{array}
        \right\rbrack$

        The $i$th entry in the resulting vector is $S_{1,i} * S_{2,1} P_i$. If you were to invert the order of the scale operations, the result would be  $S_{2,i} * S_{1,1} P_i = S_{1,i} * S_{2,1} P_i$. Since multiplication commutes, scaling therefore also commutes.

    e. \textbf{Translation and Shearing}

        Translation and shear do not commute. Take the translation and shear matrices

        $$T = \left\lbrack
            \begin{array}{ccc}
                1 & 0 & 1 \\
                0 & 1 & 1 \\
                0 & 0 & 1 \\
            \end{array}
        \right\rbrack
        ,
        S =  \left\lbrack
            \begin{array}{ccc}
                1 & 2 & 0 \\
                0 & 1 & 0 \\
                0 & 0 & 1 \\
            \end{array}
        \right\rbrack
        \text{ and the point }P=\left\lbrack
            \begin{array}{c}
                0 \\
                0 \\
                1 \\
            \end{array}
        \right\rbrack$$

        $$T(SP) = T
        \left\lbrack
            \begin{array}{c}
                0 \\
                0 \\
                1 \\
            \end{array}
        \right\rbrack
        =
        \left\lbrack
            \begin{array}{c}
                1 \\
                1 \\
                1 \\
            \end{array}
        \right\rbrack
        $$

        $$S(TP) = S
        \left\lbrack
            \begin{array}{c}
                1 \\
                1 \\
                1 \\
            \end{array}
        \right\rbrack
        =
        \left\lbrack
            \begin{array}{c}
                1 \\
                3 \\
                1 \\
            \end{array}
        \right\rbrack$$

    4. Take some triangle $<v_1, v_2, v_3>$ and a point $p$
        \begin{figure}[!h]
        \centering
        \begin{tikzpicture}
            \draw(-1,-1)  node[name=v0, label=left:{$v_0$}] {};
            \draw(1,-1)   node[name=v1, label=right:{$v_1$}] {};
            \draw(0, 0.6) node[name=v2, label=above:{$v_2$}] {};

            \draw(0, -0.3) node[name=c,  label=below:{$c$}] {};
            \draw(2, 1.3) node[name=p,  label=below:{$p$}] {};

            \draw[-](v0)--(v1);
            \draw[-](v1)--(v2);
            \draw[-](v2)--(v0);
            \draw[densely dotted](c)--(p);

            \fill (v0) circle [radius=1pt];
            \fill (v1) circle [radius=1pt];
            \fill (v2) circle [radius=1pt];
            \fill (c)  circle [radius=1pt];
            \fill (p)  circle [radius=1pt];
        \end{tikzpicture}
        \end{figure}

        a. \textbf{Write a procedure for determining if a point p is inside / outside the triangle.}

            i. to begin, find some point $c$ inside the triangle by averaging the locations of $v_1$, $v_2$, and $v_3$
            ii. let $p', v_{1-3}'$ be $p, v_{1-3}$ translated by $- c$. (translate the system s.t. c is at the origin)
            iii. rewrite each
                $\overrightarrow{v_0v_1}$,
                $\overrightarrow{v_1v_2}$,
                $\overrightarrow{v_2v_0}$
                as a function of the form
                $\overrightarrow{v_av_b} \rightarrow
                    f(\lambda) = v_a + \lambda (v_b - v_a)$
            iv. find the values of $t_1$ and $t_2$ s.t. $f(t_1) = t_2 * d$

            for each $f(t_1) = \overline{b} + t_1 * \overrightarrow{l}$

            \begin{equation} \label{eq1}
            \begin{split}
                f(t_1) &= \overline{b} + t_2 * \overrightarrow{d}\\
                \overline{b} + t_1 * \overrightarrow{l}
                    &= \overline{b} + t_2 * \overrightarrow{d}\\
                \overrightarrow{l}t_2 - \overrightarrow{d}t_1
                    & = \overline{b}
            \end{split}
            \end{equation}

            This yields a system of equations with two unknowns($t_1$ and $t_2$) and two equations (the x and y dimensions). The $t$ values can therefore be expressed in terms of known constants $\overrightarrow{l}$, $\overrightarrow{d}$, and $\overline{b}$ \footnote{full explanation at end of writeup}.

            \begin{equation}
            \begin{split}
            t_1 &= \frac{b_y - l_y \frac{b_x}{l_x}}
                           {d_y - l_x \frac{-d_x}{l_x}}\\
            t_2 &= \frac{b_x}{l_x} - \frac{-d_x}{l_x}
                        \frac{b_y - l_y \frac{b_x}{l_x}}
                             {d_y - l_x \frac{-d_x}{l_x}}\\
            \end{split}
            \end{equation}

            if t_1 and t_2 are both $\in[0,1)$ for any $f$, then $\overrightarrow{c,p}$ intersects with one of the edges of the triangle, and $p$ is outside the triangle.

        b. \textbf{Write a procedure for determining if a point q is on the edge of a triangle}

            use the algorithm in part (a.)

        c. \textbf{How can one triangulate a quadrilateral such that it is the union of two triangles}

            pick two opposite sides of the quadrilateral and draw a line between them. Construct two triangles, each with one of the remaining points in the quadrilateral and the line.

        d. \textbf{Give a procedure that can triangulate any n-sided convex polygon}

            given the points of an N sided convex polygon as an array `points`

            ```
                for n in [1..N-2]:
                    triangle(points[0], points[N], points[N+1])
            ```

            This works because for any convex polygon, a straight line can be drawn between any two nonconsecutive points without crossing the boundary of the polygon.

        e. \textbf{the procedure will not work in general for concave polygons provide a counterexample}

            This procedure will fail on some concave polygons

            \begin{figure}[!h]
            \centering
            \begin{tikzpicture}
                \draw[-](1,0)              node[label=right:{$1$}] {}
                        --(0,0)            node[label=left:{$2$}] {}
                        --(0.309, 0.950)   node[label=above:{$3$}] {}
                        --(-0.80, 0.588)   node[label=left:{$4$}] {}
                        --(-0.810, -0.586) node[label=left:{$5$}] {}
                        --(0.307, -0.952)  node[label=below:{$0$}] {}
                        --(1,0) {};

                \node[minimum width] at (0,-2) {Input Polygon};

            \end{tikzpicture}
            \hspace{20pt}
            \begin{tikzpicture}
                \draw (0.307, -0.952)  node [inner sep=0pt, name=a] {};
                \draw (1,0)            node [inner sep=0pt, name=b] {};
                \draw (0,0)            node [inner sep=0pt, name=c] {};
                \draw (0.309, 0.950)   node [inner sep=0pt, name=d] {};
                \draw (-0.80, 0.588)   node [inner sep=0pt, name=e] {};
                \draw (-0.810, -0.586) node [inner sep=0pt, name=f] {};

                \draw[-](a)--(b)--(c)--(d)--(e)--(f)--(a) {};

                \draw[dotted](a)--(b)--(c)--(a) {};
                \draw[dotted](a)--(c)--(d)--(a) {};
                \draw[dotted](a)--(d)--(e)--(a) {};
                \draw[dotted](a)--(e)--(f)--(a) {};

                \node[minimum width] at (0,-2) {Failed Tessellation };
            \end{tikzpicture}
            \end{figure}

    f. \textbf{How can one use the point in/out/on a triangle procedure (or the idea behind it) to perform a point in/out/on a convex polygon test}

        Use the same procedure used in (a.) and (b.) (finding an intersection between an interior point on the polygon and a side of the polygon), but test against each side of the polygon instead of just against the 3 sides of the triangle.

\clearpage
\newpage

#Math at the End

\begin{equation}
\begin{split}
\begin{blockarray}{ccc}
t_2 & t_1 &  \\
    \begin{block}{[cc|c]}
        \text{  } l_x & - d_x & b_x  \text{  } \\
        \text{  } l_y & - d_y & b_y  \text{  } \\
    \end{block}\\
\end{blockarray}\\
r_1 = r_1 / l_x\\
\left\lbrack
    \begin{array}{cc|c}
        1 & -\frac{-d_x}{l_x} & \frac{b_x}{l_x}   \\
        l_y & -d_y & b_y   \\
    \end{array}
\right\rbrack\\
r_2 = r_2 - l_y r_1\\
\left\lbrack
    \begin{array}{cc|c}
        1
            & -\frac{-d_x}{l_x}
            & \frac{b_x}{l_x}   \\
        0
            & -d_y - l_y\frac{-d_x}{l_x}
            & b_y - l_y \frac{b_x}{l_x}  \\
    \end{array}
\right\rbrack\\
r2 = r2 /(d_y - l_x \frac{-d_x}{l_x})\\
\left\lbrack
    \begin{array}{cc|c}
        1
            & -\frac{-d_x}{l_x}
            & \frac{b_x}{l_x}   \\
        0
            & 1
            & \frac{b_y - l_y \frac{b_x}{l_x}}
                    {d_y - l_x \frac{-d_x}{l_x}}  \\
    \end{array}
\right\rbrack\\
r_1 = r_1 + -\frac{-d_x}{l_x} r_2\\
\left\lbrack
    \begin{array}{cc|c}
        1
            & 1
            & \frac{b_x}{l_x} - \frac{-d_x}{l_x}
                \frac{b_y - l_y \frac{b_x}{l_x}}
                     {d_y - l_x \frac{-d_x}{l_x}}\\
        0
            & 1
            & \frac{b_y - l_y \frac{b_x}{l_x}}
                   {d_y - l_x \frac{-d_x}{l_x}}  \\
    \end{array}
\right\rbrack\\
t_1 &= \frac{b_y - l_y \frac{b_x}{l_x}}
                           {d_y - l_x \frac{-d_x}{l_x}}\\
t_2 &= \frac{b_x}{l_x} - \frac{-d_x}{l_x}
            \frac{b_y - l_y \frac{b_x}{l_x}}
                 {d_y - l_x \frac{-d_x}{l_x}}\\
\end{split}
\end{equation}
