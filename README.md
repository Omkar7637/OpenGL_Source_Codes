# OpenGL_Source_Codes

A collection of OpenGL source codes showcasing various real-time rendering techniques, camera controls, texture mapping, and interactive graphics. The project demonstrates a rotating 3D earth model, an inner and outer orbit with small objects, and colorful rings, implemented using OpenGL and GLUT.

---

## Supported Features

### Core OpenGL Features
- **3D Sphere Drawing**: Custom sphere function using quad strips to represent the Earth and smaller objects.
- **Texture Mapping**: Applied texture mapping to simulate realistic surfaces.
- **Dynamic Lighting**: Configurable ambient and diffuse lighting.
- **Camera Control**: Mouse-controlled camera navigation for immersive viewing.
- **Orbit Animation**: Animated inner and outer orbit paths with configurable object counts.

### Interactive Controls
- **Keyboard Controls**: Toggle fullscreen with `F` or `f` key, and exit with `ESC`.
- **Mouse Motion Control**: Adjust the camera position using mouse movements.
- **Animation Update**: Real-time animation with an adjustable frame rate.

---

## Project Structure

### Source Code
- **main.cpp**: Contains the main application logic, including OpenGL setup, rendering, and user input handling.

### Functions Overview
- **initialize**: Sets up OpenGL configurations, texture loading, and lighting.
- **display**: Main display function to render 3D objects and effects.
- **drawSphere**: Custom function for drawing a textured sphere using latitude and longitude divisions.
- **drawSmallTexturedObjects**: Draws small, textured objects along an inner orbit.
- **drawOuterObjects**: Adds outer orbit objects to simulate a layered effect.
- **drawColoredRings**: Creates colorful rings with customizable radius and thickness.
- **keyboard**: Handles keyboard input for fullscreen toggle and exit.
- **mouseMotion**: Controls camera orientation based on mouse movement.
- **update**: Animation update function that incrementally changes rotation angles.

---

## Dependencies
- **GLUT**: Required for window and input handling.
- **OpenGL**: Core OpenGL library for rendering.

### Additional Files
- **earth_texture.bmp**: Placeholder for Earth texture (replace with actual texture file).
- **small_texture.bmp**: Placeholder for smaller object textures.

---

## Future Enhancements
- **Additional Textures**: More realistic textures for enhanced visual appeal.
- **Lighting Variations**: Dynamic light positioning and additional light sources.
- **Object Customization**: Configurable shapes and colors for inner and outer orbit objects.

---
