#include <glad/glad.h>
#include <GLFW/glfw3.h>

extern int errno;

#define DBG

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif

#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif

#define ERROR_N_DIE(errno, msg) \
        do { \
                fprintf(stderr, "ERROR: %s:%d - %s | %s\n", __FILE__, __LINE__, \
                                strerror(errno), msg); \
                exit(EXIT_FAILURE); \
        } while(0)

#define ALLOW_UNUSED __attribute__((unused))
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define WIDTH                   1920.0f
#define HEIGHT                  1080.0f

// #define WIDTH                800.0f
// #define HEIGHT               600.0f

#define TITLE                   "OpenGL Gallery"

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
void framebuffer_size_callback(ALLOW_UNUSED GLFWwindow * window, int width, int height);
static void cursor_position_callback(ALLOW_UNUSED GLFWwindow * window, double xPos, double yPos);
void cursor_enter_callback(ALLOW_UNUSED GLFWwindow * window, int inside);

void process_input(GLFWwindow * window, GLuint * shader_program);
char * get_shader(char * shader_file);
void compile_shaders(GLuint const * const shader_program);

void die(char const * error);
