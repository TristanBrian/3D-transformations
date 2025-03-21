# Transformations Playground

This project demonstrates **translation, rotation, scaling, shearing, and reflection** in 3D computer graphics using **OpenGL** and **FreeGLUT**. It provides an interactive environment to visualize and manipulate 3D objects in real-time.

## Features
- **Interactive Controls**:
  - Translate, rotate, scale, shear, and reflect objects using keyboard inputs.
  - Switch between a cube and a pyramid.
  - Rotate the camera around the scene.
- **Real-Time Updates**:
  - All transformations are applied dynamically and displayed in real-time.
- **Coordinate Axes**:
  - Visualize the X, Y, and Z axes to understand transformations better.

## Controls
- **Translation**:
  - `t`: Move object along +X axis.
  - `T`: Move object along -X axis.
- **Rotation**:
  - `r`: Rotate object around Y axis.
- **Scaling**:
  - `s`: Scale object up.
  - `S`: Scale object down.
- **Shearing**:
  - `h`: Shear along X axis.
  - `H`: Shear along Y axis.
- **Reflection**:
  - `x`: Toggle reflection across X axis.
  - `y`: Toggle reflection across Y axis.
  - `z`: Toggle reflection across Z axis.
- **Object Selection**:
  - `o`: Switch between cube and pyramid.
- **Camera Rotation**:
  - `a`: Rotate camera counterclockwise.
  - `d`: Rotate camera clockwise.

## Build and Run
1. Install dependencies:
   - FreeGLUT
   - OpenGL
2. Compile the program:
   ```bash
   g++ main.cpp -o main -lGL -lGLU -lglut ./main