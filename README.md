# 3D Polygon Visualization Using GLUT
[![fr](https://img.shields.io/badge/lang-fr-fr)](https://github.com/MattewCoding/3D-Polygon-Visualization-Using-GLUT/blob/main/README.fr.md)

Using GLUT (C++ based), I made a program that lets you visualize four different types of polygons.

## Table of Contents

- [3D Polygon Visualization Using GLUT](#project-name)
  - [Table of Contents](#table-of-contents)
  - [Description](#description)
  - [Features](#features)
  - [Getting Started](#getting-started)
    - [Prerequisites](#prerequisites)
    - [Installation](#installation)
  - [Usage](#usage)
  - [License](#license)
  - [Acknowledgments](#acknowledgments)

## Description

As part of my unviersity lessons, I was tasked with using GLUT to visualize a sphere, and to be able to modify it in the 3 different axes. As the project moved along, I was addtionally tasked to do the same for a superquadric, torus, and cylinder. So I did.

## Features

- Visualize 4 different polygons
-   A sphere
-   A superquadric
-   A torus
-   A cylinder
- Modify the different polygons via
-   Streching
-   Moving it around
-   Rotating it
- "Switch" between a triangle and rectangle mesh

## Getting Started

To get started with this project, follow these steps:

### Prerequisites

Before running the project, make sure you have the following prerequisites installed:

- [C++ Compiler](https://isocpp.org/get-started): Install a C++ compiler compatible with your platform.
- [GLUT Library](https://www.opengl.org/resources/libraries/glut/glut_downloads.php): Download and install the GLUT library for your operating system.

Alternatively, install an IDE capable of compiling C++/GLUT projects. I used CodeBlocks, so I'll recommend that one.
- [CodeBlocks](https://www.codeblocks.org/downloads/): An IDE

### Installation

1. Clone the repository to your local machine:

    ```bash
    git clone https://github.com/your-username/your-project.git
    ```

2. Navigate to the project directory:

    ```bash
    cd your-project
    ```

3. Build the project using the provided Makefile:

    ```bash
    make
    ```

4. Run the executable:

    ```bash
    ./main
    ```

Now you should have the project up and running on your local machine.

## Usage
- General commands
  - P: Next shape
  - O: Previous shape
  - M: Toggle between square mesh and triangular mesh
  - L: Des/activate rotation
- Moving the shape
  - Z: Upwards
  - Q: To the left
  - S: Downwards
  - D: To the right
  - A: Forward on the Z axis
  - E: Backward on the Z axis
- Rotation
  - W: Rotate left on the XY plane
  - X: Rotate right on the XY plane
  - C: Rotate forward on the YZ plane
  - V: Rotate backwards on the YZ plane
  - B: Rotate left on XZ plane
  - N: Rotate right on XZ plane
- Scaling (or, for the superquadric, modifying the exponents of its equation)
  - R: Increase polygon scale on X axis
  - F: Decrease polygon scale on X axis
  - T: Increase polygon scale on Y axis
  - G: Decrease polygon scale on Y axis
  - Y: Increase polygon scale on Z axis
  - H: Decrease polygon scale on Z axis
- Tore
  - U: Increase ratio
  - J: Decrease ratio

## License

This project license is distributed under the [MIT License](LICENSE). 

## Acknowledgments

Possible thanks to the Wikipedia pages, for providing the parametric equations for the shapes, my teacher, for suggesting this project topic, and naturally, to the GLUT library, for making this visualisaton possible.
