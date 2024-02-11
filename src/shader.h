#ifndef SHADER_H
#define SHADER_H

#include <GLFW/glfw3.h>

#define VERTEX_SHADER_PATH      "shaders/vertex_shader.c"
#define FRAGMENT_SHADER_PATH    "shaders/fragment_shader.c"

GLchar *const   get_shader(char *shader_file);
void            compile_shaders(GLuint const *const shader_program);

#endif /* SHADER_H */
