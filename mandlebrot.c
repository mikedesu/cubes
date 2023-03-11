#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <time.h>


int main(int argc, char* argv[])
{
    srand(time(NULL));

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Cube Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL |
SDL_WINDOW_SHOWN);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)800 / (float)600, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);

    glShadeModel(GL_SMOOTH);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnableClientState(GL_VERTEX_ARRAY);
    //glVertexPointer(3, GL_FLOAT, 0, vertices);

    // Game loop
    SDL_Event event;
    int running = 1;
    
    //int dir_flag = 0;
    int current_frame = 0;
    float max_zoom = -50.0;
    float min_zoom = 0.0;
    float current_zoom = -20.0;
    float zoom_direction = -0.25;
    static float angle = 0.0;
    float angle_speed = 0.25;
    float angle_speed_direction = 0.1;
    //int num_cubes = 5;
    //int starting_offset = -2 * (num_cubes / 2);
    //static int r0 = 1;
    //static int g0 = 1;
    //static int b0 = 1;
    //static int r1 = 1;
    //static int g1 = 1;
    //static int b1 = 1;
    //static int r2 = 1;
    //static int g2 = 1;
    //static int b2 = 1;


    //int total_cubes = num_cubes * num_cubes * num_cubes;
    //int colors_length = total_cubes * 3;
    //int *colors = malloc(sizeof(int) * colors_length);
    //randomize_colors(colors, colors_length);

    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                running = 0;
                break;
            default:
                break;
            }
        }

        // Render the cube
        // Rotate the cube
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glTranslatef(0.0, 0.0, current_zoom);
        
        glRotatef(angle, 1, 1, 1); // Rotate around all axes

        glColor3f(1, 0, 0);


        // draw a triangle
        //glBegin(GL_TRIANGLES);
        //glColor3f(1, 0, 0);
        //glVertex3f(0, 0, 0);
        //glColor3f(0, 1, 0);
        //glVertex3f(1, 0, 0);
        //glColor3f(0, 0, 1);
        //glVertex3f(0, 1, 0);
        //glEnd();

        glBegin(GL_TRIANGLES);

        // draw the mandlebrot fractal
        for (int i=0; i < 100; i++) {
            for (int j=0; j < 100; j++) {
                float x = (float)i / 100.0;
                float y = (float)j / 100.0;
                float z = x;
                float r = (float)j/100.0;
                float g = (float)i/100.0;
                float b = 0.0;
                float a = 1;
                float x0 = x;
                float y0 = y;
                int iterations = 0;
                while (x*x + y*y < 2*2 && iterations < 100) {
                    float xtemp = x*x - y*y + x0;
                    y = 2*x*y + y0;
                    x = xtemp;
                    iterations++;
                }
                
                a = (float)iterations / 100.0;
                glColor4f(r, g, b, a);
                glVertex3f(x, y, z);
            }
        }

        glEnd();
        glFlush();

        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, indices);

                
        SDL_GL_SwapWindow(window);
        angle += angle_speed;
        //angle_speed += angle_speed_direction;
        //if (angle_speed >= 10 || angle_speed <= 0) {
        //    angle_speed_direction *= -1;
        //}
        
        current_zoom += zoom_direction;
        if (current_zoom <= max_zoom || current_zoom >= min_zoom) {
            zoom_direction *= -1;
        }

        current_frame++;
    }

    glDisableClientState(GL_VERTEX_ARRAY);

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

