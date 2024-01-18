#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <math.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "include/stb_image.h"

extern int errno;

#define DEBUG

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif

#ifndef EXIT_FAILURE
#define EXIT_FAILURE -1
#endif

#define ERROR_N_DIE(errno, msg) \
do { \
  fprintf(stderr, "ERROR: %s:%d - %s | %s\n", __FILE__, __LINE__, \
      strerror(errno), msg); \
  exit(EXIT_FAILURE); \
} while(0)

#ifdef DEBUG
#define D(msg) \
  do { \
    fprintf(stderr, "DEBUG: %s:%d - %s\n", __FILE__, __LINE__, msg); \
  } while(0)
#else
#define D(x) \
  do {} while(0)
#endif

#define A_UNUSED __attribute__((unused))

#define WIDTH                   1920.0f
#define HEIGHT                  1080.0f

// #define WIDTH                800.0f
// #define HEIGHT               600.0f

#define TITLE                   "OpenGL Template"

#define UNIFORM_TIME            "u_time"
#define UNIFORM_MOUSE           "u_mouse"
#define UNIFORM_RESOLUTION      "u_resolution"
#define UNIFORM_TEXTURE         "tex0"

#define VERTEX_SHADER_PATH      "shaders/vertex_shader.c"
#define FRAGMENT_SHADER_PATH    "shaders/fragment_shader.c"

#define TEXTURE_PATH            "textures/orion.jpg"

#define MAJOR_VERS              4
#define MINOR_VERS              6

typedef enum { False = 0, True = 1 } Bool;

typedef unsigned int        uint;
typedef unsigned long int   ulint;
typedef unsigned char       uchar;

// Callbacks
void framebuffer_size_callback(A_UNUSED GLFWwindow * window, int width, int height);
static void cursor_position_callback(A_UNUSED GLFWwindow * window, double xPos, double yPos);
void cursor_enter_callback(A_UNUSED GLFWwindow * window, int inside);

void process_input(GLFWwindow * window, GLuint * shader_program);
char * get_shader(char * shader_file);
void compile_shaders(const GLuint * const shader_program);

void die(char const * error);
