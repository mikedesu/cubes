#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <time.h>


// triangle vertex data
float vertices[] = {
    // front
    -1.0, -1.0, 1.0,
    1.0, -1.0, 1.0,
    1.0, 1.0, 1.0
};

int num_vertices = 3;


void offset_vertices_by(int axis, float offset) {
    if (axis < 0 || axis > 2) {
        return;
    }
    vertices[axis+0] += offset;
    vertices[axis+3] += offset;
    vertices[axis+6] += offset;
    vertices[axis+9] += offset;
    vertices[axis+12] += offset;
    vertices[axis+15] += offset;
    vertices[axis+18] += offset;
    vertices[axis+21] += offset;
}


void random_color() {
    //glColor3f((float)random()/RAND_MAX, (float)random()/RAND_MAX, (float)random()/RAND_MAX);

    int r = rand() % 3;

    if (r == 0) {
        glColor3f(1.0, 0.0, 0.0);
    } else if (r == 1) {
        glColor3f(0.0, 1.0, 0.0);
    } else {
        glColor3f(0.0, 0.0, 1.0);
    }
}

static int special_index = 0;
void randomize_colors(int *colors, int colors_length) {
    for (int i=0; i < colors_length; i++) {
        if (i < special_index) {
            colors[i] = 1;
        } else {
            colors[i] = 0;
        }
    //    colors[i] = random()%2;
    }
    special_index++;
    if (special_index >= colors_length) {
        special_index = 0;
    }
}


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
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    // Game loop
    SDL_Event event;
    int running = 1;
    
    //int dir_flag = 0;
    int current_frame = 0;
    float max_zoom = -200.0;
    float min_zoom = 0.0;
    float current_zoom = -100.0;
    //float zoom_direction = -1;
    float zoom_direction = 0.125;
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
        
        //glRotatef(angle, 1, 0, 0); // Rotate around all axes


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

        // draw the golden spiral
        float golden_angle = 137.5;
        float radius = 1.0;
        float x = 0.0;
        float y = 0.0;
        float z = 0.0;
        float myangle = 0.0;

        int total_runs = 5000;

        for (int i=0; i < total_runs; i++) {
            myangle = golden_angle * i;
            x = radius * cos(myangle);
            y = radius * sin(myangle);
            z = i * 0.01;
            float color_pixel = (float)i/total_runs;
            glColor3f(color_pixel, color_pixel, color_pixel);
            glVertex3f(x, y, z);
            radius += 0.01;
            //printf("x: %f, y: %f, z: %f
        //    ", x, y, z);
        //    //printf("angle: %f
        //    ", angle);
        //    //printf("radius: %f
        //    ", radius);
        //    //printf("i: %d
        //    ", i);
        //    //printf("
        //    ");
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

