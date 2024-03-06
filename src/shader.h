#ifndef SHADER_H
#define SHADER_H

#include <GLFW/glfw3.h>

#define VERTEX_SHADER_PATH      "shaders/vertex_shader.glsl"
#define FRAGMENT_SHADER_PATH    "shaders/fragment_shader.glsl"

GLchar*         get_shader(char *shader_file);
int             compile_shaders(GLuint const *const new_shader_program);

#endif /* SHADER_H */
