#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <time.h>


// Cube vertex data
GLfloat vertices[] = {
    // Front face
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    // Back face
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f
};

// Cube index data
GLushort indices[] = {
    0, 1, 2, 2, 3, 0,  // Front face
    4, 5, 6, 6, 7, 4,  // Back face
    3, 2, 6, 6, 7, 3,  // Top face
    0, 1, 5, 5, 4, 0,  // Bottom face
    1, 5, 6, 6, 2, 1,  // Right face
    0, 4, 7, 7, 3, 0   // Left face
};


void reset_vertices() {
    vertices[0] = -0.5f;
    vertices[1] = -0.5f;
    vertices[2] = 0.5f;
    vertices[3] = 0.5f;
    vertices[4] = -0.5f;
    vertices[5] = 0.5f;
    vertices[6] = 0.5f;
    vertices[7] = 0.5f;
    vertices[8] = 0.5f;
    vertices[9] = -0.5f;
    vertices[10] = 0.5f;
    vertices[11] = 0.5f;
    vertices[12] = -0.5f;
    vertices[13] = -0.5f;
    vertices[14] = -0.5f;
    vertices[15] = 0.5f;
    vertices[16] = -0.5f;
    vertices[17] = -0.5f;
    vertices[18] = 0.5f;
    vertices[19] = 0.5f;
    vertices[20] = -0.5f;
    vertices[21] = -0.5f;
    vertices[22] = 0.5f;
    vertices[23] = -0.5f;
}


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
    int dir_flag = 0;
    int current_frame = 0;

    float max_zoom = -50.0;
    float min_zoom = 0.0;
    float current_zoom = -20.0;
    float zoom_direction = -0.25;
    float angle_speed = 0.25;
    float angle_speed_direction = 0.1;

    int num_cubes = 5;
    int starting_offset = -2 * (num_cubes / 2);
    static int r0 = 1;
    static int g0 = 1;
    static int b0 = 1;
    static int r1 = 1;
    static int g1 = 1;
    static int b1 = 1;
    static int r2 = 1;
    static int g2 = 1;
    static int b2 = 1;


    int total_cubes = num_cubes * num_cubes * num_cubes;
    int colors_length = total_cubes * 3;
    int *colors = malloc(sizeof(int) * colors_length);
    randomize_colors(colors, colors_length);

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
        static float angle = 0.0;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glTranslatef(0.0, 0.0, current_zoom);
        
        glRotatef(angle, 1, 1, 1); // Rotate around all axes

        if (current_frame > 15) {
            current_frame = 0;
            randomize_colors(colors, colors_length);
        }
        

        glColor3f(1, 0, 0);
        for (int i = 0; i < num_cubes; i++) {
            //reset_vertices();
            //offset_vertices_by(0, starting_offset + i*2);
            //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, indices);
            for (int j=num_cubes-1; j >= 0; j--) {
                for (int k=num_cubes-1; k >= 0; k--) {
                //for (int k=0; k < num_cubes; k++) {
                    int color_index = (i*num_cubes*num_cubes) + (j*num_cubes) + k;
                    int r = colors[color_index*3];
                    int g = colors[color_index*3+1];
                    int b = colors[color_index*3+2];
                    glColor3f(r, g, b);

                    reset_vertices();
                    offset_vertices_by(0, starting_offset + i*2);
                    offset_vertices_by(1, starting_offset + j*2);
                    offset_vertices_by(2, starting_offset + k*2);
                    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, indices);
                }
            }
        }

                
        SDL_GL_SwapWindow(window);
        angle += angle_speed;
        //angle_speed += angle_speed_direction;
        //if (angle_speed >= 10 || angle_speed <= 0) {
        //    angle_speed_direction *= -1;
        //}
        
        //current_zoom += zoom_direction;
        //if (current_zoom <= max_zoom || current_zoom >= min_zoom) {
        //    zoom_direction *= -1;
        //}

        current_frame++;
    }

    glDisableClientState(GL_VERTEX_ARRAY);

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

