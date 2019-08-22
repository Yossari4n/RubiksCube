# Rubiks Cube
Simulator of Rubik's Cube made in C++ and modern OpenGL. All rotation are described in accordance with the official notation
ie. clockwise rotations are described as (F)ront, (B)ack, (U)p, (D)own, (L)eft and (R)ight; counter-clockwise rotations determines postfix '.
Front correspond to the face with blue center cubie and Up to the face with white center cubie.

![Screenshot](Photo.png?raw=true "Rubiks Cube")

## Controlls
To rotate Front, Back, Up, Down, Left or Right face clockwise press respectively F, B, U, D, L or R key. 
For counter counter-clockwise rotation simply hold shift when rotating face.

You can move camera by holding left mouse botton or by direction keys on numpad 
alternatively camera can be set to look directly at cube's Front, Right or Up face by pressing 1, 3 or 7 on numpad.

## Dependencies
* GLFW
* GLAD
* GLM
* Assimp
* STB
* imgui