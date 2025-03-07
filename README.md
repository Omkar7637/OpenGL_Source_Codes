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
---
---

### **1. Understanding OpenGL Coordinate System**
OpenGL uses a **Cartesian coordinate system** with the **origin (0,0,0)** at the center of the screen. The coordinates are:
- **X-axis** (left to right): -1.0 to 1.0
- **Y-axis** (bottom to top): -1.0 to 1.0
- **Z-axis** (into and out of the screen): -1.0 to 1.0 (for 3D)

**Example:**
```
(-1,  1)       (0,  1)       (1,  1)
      +-----------+-----------+
      |           |           |
(-1,  0) |  (0,0) | (1,  0)
      |           |           |
      +-----------+-----------+
(-1, -1)       (0, -1)      (1, -1)
```
- **(0, 1, 0)** → Top-center
- **(-1, -1, 0)** → Bottom-left
- **(1, -1, 0)** → Bottom-right

---

### **2. `display()` Function Breakdown**
Your `display()` function follows these steps:

#### **Step 1: Clear the Screen**
```cpp
glClear(GL_COLOR_BUFFER_BIT);
```
- **`glClear(GL_COLOR_BUFFER_BIT);`** → Clears the color buffer to prepare for new drawing.

#### **Step 2: Start Drawing a Triangle**
```cpp
glBegin(GL_TRIANGLES);
```
- **`glBegin(GL_TRIANGLES);`** → Tells OpenGL that we are drawing triangles.

#### **Step 3: Define the Triangle Vertices**
Each **`glVertex3f(x, y, z)`** defines a point in **3D space**.

```cpp
// Apex (Top)
glColor3f(1.0f, 0.0f, 0.0f);
glVertex3f(0.0, 1.0, 0.0);
```
- **`glColor3f(1.0, 0.0, 0.0);`** → Sets color to **Red**.
- **`glVertex3f(0.0, 1.0, 0.0);`** → Places a vertex at the top.

```cpp
// Left Bottom
glColor3f(0.0f, 1.0f, 0.0f);
glVertex3f(-1.0, -1.0, 0.0);
```
- **`glColor3f(0.0, 1.0, 0.0);`** → Sets color to **Green**.
- **`glVertex3f(-1.0, -1.0, 0.0);`** → Places a vertex at the **bottom-left**.

```cpp
// Right Bottom
glColor3f(0.0f, 0.0f, 1.0f);
glVertex3f(1.0, -1.0, 0.0);
```
- **`glColor3f(0.0, 0.0, 1.0);`** → Sets color to **Blue**.
- **`glVertex3f(1.0, -1.0, 0.0);`** → Places a vertex at the **bottom-right**.

#### **Step 4: End Drawing**
```cpp
glEnd();
```
- **`glEnd();`** → Tells OpenGL that we have finished defining the triangle.

#### **Step 5: Swap Buffers**
```cpp
SwapBuffers(ghdc);
```
- **`SwapBuffers(ghdc);`** → Swaps the back buffer with the front buffer to display the rendered image (Double Buffering).

---
---
---

## **1. OpenGL Coordinate System Recap**
OpenGL uses a **Cartesian coordinate system** where:  
- The **origin (0,0,0)** is in the center of the screen.  
- The **X-axis** goes **left (-1.0) to right (+1.0)**.  
- The **Y-axis** goes **bottom (-1.0) to top (+1.0)**.  
- The **Z-axis** goes **into (-1.0) and out (+1.0) of the screen** (used in 3D).  

---

## **2. Drawing Basic Shapes**
### **A) Drawing a Triangle**
#### **Vertices of a Triangle**
A **triangle** has **3 vertices**, and we define them in OpenGL using `glVertex3f(x, y, z)`.  

**Example:**  
Let's draw a triangle with these points:  
- **Top vertex:** (0.0, 1.0, 0.0) → Center-top  
- **Bottom-left vertex:** (-1.0, -1.0, 0.0) → Left-bottom  
- **Bottom-right vertex:** (1.0, -1.0, 0.0) → Right-bottom  

**Code:**
```cpp
glBegin(GL_TRIANGLES);  // Start drawing a triangle

// Top Vertex (Red)
glColor3f(1.0f, 0.0f, 0.0f);
glVertex3f(0.0, 1.0, 0.0);

// Bottom Left Vertex (Green)
glColor3f(0.0f, 1.0f, 0.0f);
glVertex3f(-1.0, -1.0, 0.0);

// Bottom Right Vertex (Blue)
glColor3f(0.0f, 0.0f, 1.0f);
glVertex3f(1.0, -1.0, 0.0);

glEnd();  // End drawing
```

### **B) Drawing a Square**
#### **Vertices of a Square**
A **square** has **4 vertices**, and we can draw it using `GL_QUADS`.  

**Example:**  
- **Top-left corner:** (-0.5, 0.5, 0.0)  
- **Top-right corner:** (0.5, 0.5, 0.0)  
- **Bottom-right corner:** (0.5, -0.5, 0.0)  
- **Bottom-left corner:** (-0.5, -0.5, 0.0)  

**Code:**
```cpp
glBegin(GL_QUADS);  // Start drawing a square

// Top Left (Red)
glColor3f(1.0f, 0.0f, 0.0f);
glVertex3f(-0.5, 0.5, 0.0);

// Top Right (Green)
glColor3f(0.0f, 1.0f, 0.0f);
glVertex3f(0.5, 0.5, 0.0);

// Bottom Right (Blue)
glColor3f(0.0f, 0.0f, 1.0f);
glVertex3f(0.5, -0.5, 0.0);

// Bottom Left (Yellow)
glColor3f(1.0f, 1.0f, 0.0f);
glVertex3f(-0.5, -0.5, 0.0);

glEnd();  // End drawing
```

### **C) Drawing a Rectangle**
A **rectangle** is similar to a **square** but with different width and height.  
- We use `GL_QUADS` to connect **4 vertices**.

**Example:**  
- **Top-left corner:** (-0.8, 0.5, 0.0)  
- **Top-right corner:** (0.8, 0.5, 0.0)  
- **Bottom-right corner:** (0.8, -0.5, 0.0)  
- **Bottom-left corner:** (-0.8, -0.5, 0.0)  

**Code:**
```cpp
glBegin(GL_QUADS);  // Start drawing a rectangle

// Top Left
glColor3f(1.0f, 0.0f, 0.0f);
glVertex3f(-0.8, 0.5, 0.0);

// Top Right
glColor3f(0.0f, 1.0f, 0.0f);
glVertex3f(0.8, 0.5, 0.0);

// Bottom Right
glColor3f(0.0f, 0.0f, 1.0f);
glVertex3f(0.8, -0.5, 0.0);

// Bottom Left
glColor3f(1.0f, 1.0f, 0.0f);
glVertex3f(-0.8, -0.5, 0.0);

glEnd();  // End drawing
```

### **D) Drawing a Pentagon (5-sided shape)**
A **pentagon** has **5 vertices**. We use `GL_POLYGON` to draw it.

**Example Coordinates:**
```
       (0, 0.8)   --> Top
 (-0.8, 0.3)  (0.8, 0.3) --> Top Left & Top Right
(-0.5, -0.5) (0.5, -0.5) --> Bottom Left & Bottom Right
```

**Code:**
```cpp
glBegin(GL_POLYGON);  // Start drawing a Pentagon

// Top Vertex
glColor3f(1.0f, 0.0f, 0.0f);
glVertex3f(0.0, 0.8, 0.0);

// Top Left
glColor3f(0.0f, 1.0f, 0.0f);
glVertex3f(-0.8, 0.3, 0.0);

// Bottom Left
glColor3f(0.0f, 0.0f, 1.0f);
glVertex3f(-0.5, -0.5, 0.0);

// Bottom Right
glColor3f(1.0f, 1.0f, 0.0f);
glVertex3f(0.5, -0.5, 0.0);

// Top Right
glColor3f(0.0f, 1.0f, 1.0f);
glVertex3f(0.8, 0.3, 0.0);

glEnd();  // End drawing
```

---

## **3. How to Assign Coordinates Correctly?**
### **Understanding the Screen Space**
1. **Keep the coordinates within (-1.0 to 1.0) for visibility.**
2. **X-axis increases → moves right, decreases → moves left.**
3. **Y-axis increases → moves up, decreases → moves down.**
4. **Z-axis (3D depth, later for 3D shapes).**

### **How to Decide Coordinates?**
- Divide the screen into a **grid** where (-1.0, -1.0) is the bottom-left and (1.0, 1.0) is the top-right.
- If you want a **larger shape**, increase the vertex values closer to -1 or 1.
- If you want a **smaller shape**, keep the values between -0.5 and 0.5.

---
---
---

# **1. Transformations in OpenGL**
Transformations allow us to **move (translate), rotate, and scale** objects in a 2D/3D space. OpenGL provides the following transformation functions:

| Transformation | Function | Description |
|--------------|----------------|----------------|
| **Translation** | `glTranslatef(x, y, z)` | Moves an object along X, Y, Z axes |
| **Rotation** | `glRotatef(angle, x, y, z)` | Rotates an object around an axis |
| **Scaling** | `glScalef(sx, sy, sz)` | Resizes an object |

These transformations modify the **model matrix**, affecting how objects are drawn.

---

# **2. Translation (Moving an Object)**
Translation moves an object to a different position.  
- `glTranslatef(x, y, z)`: Moves an object along the **X, Y, Z** axes.

### **Example: Move a Triangle**
```cpp
glPushMatrix();  // Save the current state
glTranslatef(0.5f, 0.5f, 0.0f);  // Move the triangle to (0.5, 0.5)
glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0, 1.0, 0.0);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0, -1.0, 0.0);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1.0, -1.0, 0.0);
glEnd();
glPopMatrix();  // Restore the previous state
```
🔹 The triangle moves **right (X=0.5) and up (Y=0.5)**.

---

# **3. Rotation (Rotating an Object)**
Rotation spins an object around a specified axis.  
- `glRotatef(angle, x, y, z)`: Rotates the object by `angle` degrees around the axis `(x, y, z)`.  
  - `(1,0,0)`: Rotate around X-axis  
  - `(0,1,0)`: Rotate around Y-axis  
  - `(0,0,1)`: Rotate around Z-axis  

### **Example: Rotate a Square**
```cpp
glPushMatrix();
glRotatef(45.0f, 0.0f, 0.0f, 1.0f);  // Rotate 45 degrees around Z-axis
glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5, 0.5, 0.0);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.5, 0.5, 0.0);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.5, -0.5, 0.0);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-0.5, -0.5, 0.0);
glEnd();
glPopMatrix();
```
🔹 The square rotates **45° around the Z-axis**.

---

# **4. Scaling (Resizing an Object)**
Scaling enlarges or shrinks an object.  
- `glScalef(sx, sy, sz)`: Scales the object along X, Y, Z axes.  

### **Example: Scale a Triangle**
```cpp
glPushMatrix();
glScalef(2.0f, 2.0f, 1.0f);  // Make the triangle 2x bigger
glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0, 1.0, 0.0);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0, -1.0, 0.0);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1.0, -1.0, 0.0);
glEnd();
glPopMatrix();
```
🔹 The triangle becomes **twice as large**.

---

# **5. Combining Transformations**
You can combine **translation, rotation, and scaling**.  
- **Order matters**:  
  - If you **scale before translating**, the object moves differently than if you **translate before scaling**.

### **Example: Move, Rotate & Scale a Square**
```cpp
glPushMatrix();
glTranslatef(0.5f, 0.5f, 0.0f);  // Move right & up
glRotatef(45.0f, 0.0f, 0.0f, 1.0f);  // Rotate 45 degrees
glScalef(1.5f, 1.5f, 1.0f);  // Make 1.5x bigger
glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5, 0.5, 0.0);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.5, 0.5, 0.0);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.5, -0.5, 0.0);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-0.5, -0.5, 0.0);
glEnd();
glPopMatrix();
```
🔹 The square **moves, rotates, and enlarges** in one step.

---

# **6. Animation with Transformations**
We can animate objects by updating transformations in a loop.

### **Example: Rotating Square Animation**
```cpp
static float angle = 0.0f;  // Rotation angle

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPushMatrix();
    glRotatef(angle, 0.0f, 0.0f, 1.0f);  // Rotate square
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-0.5, 0.5, 0.0);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.5, 0.5, 0.0);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.5, -0.5, 0.0);
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f(-0.5, -0.5, 0.0);
    glEnd();
    glPopMatrix();

    angle += 0.5f;  // Update angle for next frame
    glutPostRedisplay();  // Redraw screen
    glutSwapBuffers();
}
```
🔹 The square **rotates continuously**.

---

# **7. Summary**
- `glTranslatef(x, y, z)`: Moves an object.
- `glRotatef(angle, x, y, z)`: Rotates an object.
- `glScalef(sx, sy, sz)`: Resizes an object.
- **Order of transformations affects the result.**
- **Use `glPushMatrix()` and `glPopMatrix()` to keep transformations separate.**
- **Animating transformations** creates cool effects!

---



