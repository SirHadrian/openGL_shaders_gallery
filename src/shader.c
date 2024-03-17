#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>

#include "shader.h"
#include "utils.h"
#include "alloc.h"

GLchar*
get_shader(char *shader_file)
{
        FILE *file = fopen(shader_file, "r");
        if (file == NULL) {
                ERROR_N_DIE(errno, shader_file);
        }

        fseek(file, 0, SEEK_END);
        ulint length = (ulint)ftell(file);
        fseek(file, 0, SEEK_SET);

        GLchar *shader_string = MALLOC(length + 1, *shader_string);

        int cursor;
        uint index = 0;

        while ((cursor = fgetc(file)) != EOF) {
                shader_string[index] = (char)cursor;
                index++;
        }
        shader_string[length] = '\0';

        fclose(file);
        return shader_string;
}

int
compile_shaders(GLuint const *const new_shader_program)
{
        GLchar *const vertex_shader_source = get_shader(VERTEX_SHADER_PATH);
        GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(vertex_shader, 1, (GLchar const **)&vertex_shader_source, NULL);
        glCompileShader(vertex_shader);

        GLint success;
        char info_log[512];

        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
        if (!success) {
                glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
                fprintf(stderr, "Vertex shader compilation error: %s\n", info_log);
                free(vertex_shader_source);
                return 1;
        }

        free(vertex_shader_source);

        GLchar *const fragment_shader_source = get_shader(FRAGMENT_SHADER_PATH);
        GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(fragment_shader, 1, (GLchar const **)&fragment_shader_source, NULL);
        glCompileShader(fragment_shader);

        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
        if (!success) {
                glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
                fprintf(stderr, "Fragment shader compilation error: %s\n", info_log);
                free(fragment_shader_source);
                return 1;
        }

        free(fragment_shader_source);

        glAttachShader(*new_shader_program, vertex_shader);
        glAttachShader(*new_shader_program, fragment_shader);
        glLinkProgram(*new_shader_program);

        glGetProgramiv(*new_shader_program, GL_LINK_STATUS, &success);
        if (!success) {
                glGetProgramInfoLog(*new_shader_program, 512, NULL, info_log);
                fprintf(stderr, "Shader program linking error: %s\n", info_log);
                return 1;
        }

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        return 0;
}

