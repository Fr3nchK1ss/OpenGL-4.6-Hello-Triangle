# OpenGL-4.6-Hello-Triangle

The famous OpenGL "Hello triangle" using shaders. It uses the OpenGL 4.5 functionality called [Direct State Access](https://www.khronos.org/opengl/wiki/Direct_State_Access). Be aware, not-that-old hardware may not be compatible with this functionality. 

As of November 2020, it is the most up-to-date "hello triangle" example I could piece together.

## Build and run

I work on GNU/Linux Ubuntu 20. Obviously you need to install a compiler (g++), make, opengl and glfw3.

`sudo apt install g++ build-essential libopengl0 libopengl-dev libglfw3 libglfw3-dev`

Run `make` in the directory of the project.

## Glad 

This code uses Glad as its openGL extensions loader. Glew would work fine too. 
The directories include/glad, include/KHR, and the files glad.h, glad.c and khrplatform.h were generated from [Glad website](https://glad.dav1d.de/)

## Greetings

I copied/modified code from [Anton Gerdelan](https://antongerdelan.net/opengl/index.html) and [Joey De Vries / Learnopengl](https://learnopengl.com/Getting-started/Shaders). See Licence file for more info. Also check [Fendevel repos about modern OpenGL](https://github.com/fendevel). 



