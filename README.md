# cubes

This is a simple C program demonstrating how to render cubes in 3d using OpenGL and libsdl.

The code for this was written with help from:

- OpenAI ChatGPT
- Github Copilot

### motivation

I've always wanted to mess with 3d programming, but digging into something real quick, I found there to be a lack of good tutorials online. I knew what I wanted to do in the beginning, but lacked the fundamental 3d programming background (and patience). 

Luckily, I've been messing with libsdl and C for long enough that getting ChatGPT to spit out a usable code stub was very easy. 

Once I got the initial code working, I began modifying it so that it not only rotated the cube across all 3 axes, but rendered multiple cubes as well. 

Playing around with being able to individually color each cube requires storing the color channel data. I chose to malloc an array of ints for this purpose. 

### examples

Every so often, I might write a comment in a new file asking copilot to generate some code in order to "do" something and we observe what copilot generates.

One example is the mandlebrot.c file, where the comment `// draw the mandlebrot fractal` yields:

```
         glBegin(GL_TRIANGLES);    
         // draw the mandlebrot fractal
         for (int i=0; i < 100; i++) {
             for (int j=0; j < 100; j++) {
                 float x = (float)i / 100.0;
                 float y = (float)j / 100.0;
                 float z = 0.0;
                 float r = 0.0;
                 float g = 0.0;
                 float b = 0.0;
                 float a = 0.0;
                 float x0 = x;
                 float y0 = y;
                 int iterations = 0;
                 while (x*x + y*y < 2*2 && iterations < 100) {
                     float xtemp = x*x - y*y + x0;
                     y = 2*x*y + y0;
                     x = xtemp;
                     iterations++;
                 }
                 if (iterations < 100) {
                     r = 1.0;
                     g = 1.0;
                     b = 1.0;
                 } else {
                     r = 0.0;
                     g = 0.0;
                     b = 0.0;
                 }
                 a = (float)iterations / 100.0;
                 glColor4f(r, g, b, a);
                 glVertex3f(x, y, z);
             }   
         }       
         glEnd();
         glFlush();
```

In this most basic of senses, we can say that we are "playing" with "AI-generated graphics", albeit on a primitive scale ;)

### building

To build, simply type `make` in this root folder (assuming you have basic dependencies installed).

> You: What do I need to apt-get install to get GL/gl.h and GL/glu.h on my Ubuntu system?
> ChatGPT: To install the necessary packages to get GL/gl.h and GL/glu.h on your Ubuntu system, you would need to run the following command in your terminal:

```
sudo apt-get install mesa-common-dev libglu1-mesa-dev freeglut3-dev
```

> You: What about SDL2?
> ChatGPT: To install SDL2 on your Ubuntu system, you would need to run the following command in 
your terminal:

```
sudo apt-get install libsdl2-dev
```

When you go to build, your output should look something like this:

```
14:23木[murasame]/cubes$ make
gcc main.c -lSDL2 -lGL -lGLU -lm -o main
gcc colored-cubes.c -lSDL2 -lGL -lGLU -lm -o colored-cubes
gcc triangles.c -lSDL2 -lGL -lGLU -lm -o triangles
gcc triangles2.c -lSDL2 -lGL -lGLU -lm -o triangles2
gcc mandlebrot.c -lSDL2 -lGL -lGLU -lm -o mandlebrot
gcc golden-spiral.c -lSDL2 -lGL -lGLU -lm -o golden-spiral
gcc shader_toy.c -lSDL2 -lGL -lGLU -lm -o shader_toy
shader_toy.c: In function ‘main’:
shader_toy.c:82:27: warning: implicit declaration of function ‘glCreateShader’ [-Wimplicit-function-declaration]
   82 |     GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
      |                           ^~~~~~~~~~~~~~
shader_toy.c:83:5: warning: implicit declaration of function ‘glShaderSource’ [-Wimplicit-function-declaration]
   83 |     glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
      |     ^~~~~~~~~~~~~~
shader_toy.c:84:5: warning: implicit declaration of function ‘glCompileShader’ [-Wimplicit-function-declaration]
   84 |     glCompileShader(vertexShader);
      |     ^~~~~~~~~~~~~~~
shader_toy.c:90:28: warning: implicit declaration of function ‘glCreateProgram’ [-Wimplicit-function-declaration]
   90 |     GLuint shaderProgram = glCreateProgram();
      |                            ^~~~~~~~~~~~~~~
shader_toy.c:91:5: warning: implicit declaration of function ‘glAttachShader’ [-Wimplicit-function-declaration]
   91 |     glAttachShader(shaderProgram, vertexShader);
      |     ^~~~~~~~~~~~~~
shader_toy.c:93:5: warning: implicit declaration of function ‘glLinkProgram’; did you mean ‘glHistogram’? [-Wimplicit-function-declaration]
   93 |     glLinkProgram(shaderProgram);
      |     ^~~~~~~~~~~~~
      |     glHistogram
shader_toy.c:95:5: warning: implicit declaration of function ‘glUseProgram’ [-Wimplicit-function-declaration]
   95 |     glUseProgram(shaderProgram);
      |     ^~~~~~~~~~~~
shader_toy.c:110:5: warning: implicit declaration of function ‘glGenVertexArrays’ [-Wimplicit-function-declaration]
  110 |     glGenVertexArrays(1, &VAO);
      |     ^~~~~~~~~~~~~~~~~
shader_toy.c:111:5: warning: implicit declaration of function ‘glGenBuffers’; did you mean ‘glReadBuffer’? [-Wimplicit-function-declaration]
  111 |     glGenBuffers(1, &VBO);
      |     ^~~~~~~~~~~~
      |     glReadBuffer
shader_toy.c:114:5: warning: implicit declaration of function ‘glBindVertexArray’ [-Wimplicit-function-declaration]
  114 |     glBindVertexArray(VAO);
      |     ^~~~~~~~~~~~~~~~~
shader_toy.c:116:5: warning: implicit declaration of function ‘glBindBuffer’; did you mean ‘glReadBuffer’? [-Wimplicit-function-declaration]
  116 |     glBindBuffer(GL_ARRAY_BUFFER, VBO);
      |     ^~~~~~~~~~~~
      |     glReadBuffer
shader_toy.c:117:5: warning: implicit declaration of function ‘glBufferData’ [-Wimplicit-function-declaration]
  117 |     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
      |     ^~~~~~~~~~~~
shader_toy.c:122:5: warning: implicit declaration of function ‘glVertexAttribPointer’; did you mean ‘glVertexPointer’? [-Wimplicit-function-declaration]
  122 |     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
      |     ^~~~~~~~~~~~~~~~~~~~~
      |     glVertexPointer
shader_toy.c:123:5: warning: implicit declaration of function ‘glEnableVertexAttribArray’ [-Wimplicit-function-declaration]
  123 |     glEnableVertexAttribArray(0);
      |     ^~~~~~~~~~~~~~~~~~~~~~~~~
```

-----

### Notes:

- As of 03/10/2023, the `shader_toy` example is broken.


