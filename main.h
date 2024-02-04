#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "include/utils.h"

#define DBG

#define WIDTH                   1920.0f
#define HEIGHT                  1080.0f

// #define WIDTH                800.0f
// #define HEIGHT               600.0f

#define TITLE                   "OpenGL Gallery"

#define UNIFORM_TIME            "u_time"
#define UNIFORM_MOUSE           "u_mouse"
#define UNIFORM_RESOLUTION      "u_resolution"
#define UNIFORM_TEXTURE         "tex0"

#define TEXTURE_PATH            "textures/orion.jpg"

#define MAJOR_VERS              4
#define MINOR_VERS              6

// Callbacks
void framebuffer_size_callback(ALLOW_UNUSED GLFWwindow *window, int width, int height);
static void cursor_position_callback(ALLOW_UNUSED GLFWwindow *window, double xPos, double yPos);
void cursor_enter_callback(ALLOW_UNUSED GLFWwindow *window, int inside);

void process_input(GLFWwindow *const window, GLuint *const shader_program);
void die(char const *const error);
