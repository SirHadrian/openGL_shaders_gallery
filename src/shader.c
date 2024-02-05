#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>

#include "shader.h"
#include "utils.h"

GLchar *const get_shader(char *shader_file)
{
        FILE *file = fopen(shader_file, "r");
        if (!file)
                ERROR_N_DIE(errno, shader_file);

        fseek(file, 0, SEEK_END);
        ulint length = (ulint)ftell(file);
        fseek(file, 0, SEEK_SET);

        GLchar *shader_string = malloc((sizeof *shader_string) * (length + 1));
        if (!shader_string)
                ERROR_N_DIE(errno, "");

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

void compile_shaders(GLuint const *const shader_program)
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
                return;
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
                return;
        }

        free(fragment_shader_source);

        glAttachShader(*shader_program, vertex_shader);
        glAttachShader(*shader_program, fragment_shader);
        glLinkProgram(*shader_program);

        glGetProgramiv(*shader_program, GL_LINK_STATUS, &success);
        if (!success) {
                glGetProgramInfoLog(*shader_program, 512, NULL, info_log);
                fprintf(stderr, "Shader program linking error: %s\n", info_log);
                return;
        }

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
}

