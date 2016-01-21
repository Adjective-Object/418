---
title: CSC418 (Computer Graphics) Assignment 1
author: Maxwell Huang-Hobbs, 100675888, g4rbage
date: Monday October 5, 2015
bibliography: writeup-library.bib
csl: chicago.csl
---

# Part B: 3d Penguin

The penguin is constructed from a hierarchy of Scene Nodes, each one
having a transform function which applies a transform
based on the global state, a render function which draws theappropriate part of the penguin, and a series of children.The global state is controlled either through manually adjustingUI parameters, or through Catmull-Rom interpolation based onkeyframes (file io done through helper code).

Rendering style is controlled by adjusting OpenGL material and render mode parameters prior to traversing the scenegraph, as the renderfunctions along the scene graph only draw the geometry, and donot adjust the render parameters openGL uses. For the utlined style, the scene is traversed twice, rendering the second pass as a wireframe slightly closer to the camera than original model. Thisis done to take advantage of the opengl z buffer, but avoid z-fighting betweeen the flat color rendering and the wireframe.

\begin{multicols}{2}
\centering

\includegraphics[width=.2\textwidth]{wire.png} \\
Wireframe penguin at attention

\vfill
\columnbreak

\includegraphics[width=.2\textwidth]{metal.png} \\
"Metallic" penguin in motion. Note the reflectivity of the left shoulder and thigh.

\end{multicols}

Materials for the Matte and Metal rendering based on those listed at [http://www.it.hiof.no/~borres/j3d/explain/light/p-materials.html.](http://www.it.hiof.no/~borres/j3d/explain/light/p-materials.html.)

I suggest looking at the penguin in motion to see the specularity of the metallic rendering mode.
