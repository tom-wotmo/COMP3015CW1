# COMP3015-CW1 OpenGL Living Room Scene 
This is an OpenGL project that uses GLSL custom shaders to render and show off a scene. This scene shows a small cat sat on a sofa infront of a table, my overall project aim is to have a fully decorated living room scene that has multiple shader techniques to show off.
This particular scene uses Blinn-Phong and some fog shading. The scene contains one light and then the blinn phong shader to shade the Sofa, Table and the Cat.

## How to navigate the code base
The code is relatively straight forward the BlinnPhong shading is done via the fragment shader as well as the fog calculations, the fragment shader also shows off the uniform structures for material, lights and fog. The vertex shader just computes the coordinates of the rendered objects, like the texture co-ordinates for our textures. You can find the main body of coding in the scenebasic uniform where we render the objects and define the values for each constructor.

## Inspiration
I would like the project to be set in 90's living room, with neutral colours and monotone furniture and lighting, it shall have all the basic house hold items and my final project will depict multiple shaders that you can control through IMGUI.

## Running the program
You can download the zip and run it through visual studio, but I've also set it up to run through an .exe that can be found in the x64/Debug/Project_Template.exe

## Youtube Link 
https://www.youtube.com/watch?v=567eWpFDSbw

## Asset Creditation 
Table - https://www.cgtrader.com/free-3d-models/furniture/table/table-for-ar-application-1daace94-e189-42bc-b059-909a46314ec0
Sofa - https://www.cgtrader.com/free-3d-models/furniture/sofa/old-leather-couch-pbr-low-poly-sofa
Cat - https://free3d.com/3d-model/low-poly-cat-46138.html


![catsofasc1](https://user-images.githubusercontent.com/57358973/161385470-c29471e0-951e-45a8-a984-e75c441c8fc9.png)

![catsofasc2](https://user-images.githubusercontent.com/57358973/161385486-4039be03-7c52-4172-a348-caacb5d6fc84.png)

![catsofasc3](https://user-images.githubusercontent.com/57358973/161385505-a99f04d1-f5ed-4d1d-967f-37cfd34eab6f.png)


