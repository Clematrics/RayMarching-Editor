# Node description

Each node is described by :
- a name
- a list of inputs
- a list of outputs

Each input has a name and a type. The name can be written as `name#id`. The name part will be displayed on the node, while the id, if specified, is the part used inside the code to reference the input value;
Each output has a name, a type and the code associated with the output. The code is separated in two parts : an optional part describing functions that will be used for the computation of the result, and the expression of the result itself, which depends on the inputs.

# Kernels specification

Kernels are implemented as json files, that the editor will parse to load all kernels described. There is a `core.json` that contains all core kernels needed.
The world output and the constant value nodes are hard coded and cannot be described in a kernel file ?
Also, the function node (on which you can double-click to change their logic and customize their inputs and outputs) are also hard coded.
Each file contains a list of kernel. The program while automatically load all files available with a `.json` extension and integrate them if they are valid.

# Data types

# Code

Based on GLSL shader language. Knowing the inputs name (or id if specified), you can include them as `#input` in the code.

# Available nodes

## Constant nodes

### Float

Return a single float

### Float3

Return a vector of 3 floats

### Float4

Return a vector of 4 floats

## Break and make nodes

### Break Float3

Return the x, the y and the z component of the input vector.

### Make Float3

Return a vector from 3 floats.

## Transformations

They allow to transform a vector into another vector

### Translation

### Rotation (around origin ?)

### Scale (from origin ?)

### Transform

Apply a scale, then a rotation and then a translation.

### Project

Project a 3d vector to a 2d plane base on its normal.

## 2D primitives

They allow to return a distance to a primitive from a 2D position

## 3D primitives

They allow to return a distance to a primitive from a 3D position

## Operations / modifiers

They allow to modify distances to make operations to or between shapes
