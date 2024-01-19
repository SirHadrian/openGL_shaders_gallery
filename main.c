#include <stdio.h>

#include "main.h"
#include "include/shader.h"
#include "include/stb_image.h"

// Cursor state
GLfloat xMousePos = 0.f, yMousePos = 0.f;
Bool inside_window = False;

int
main(void)
{
        if (!glfwInit())
                die("Could not initialize GLFW");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MAJOR_VERS);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MINOR_VERS);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        void * start_fullscreen = NULL;
        // void * start_fullscreen = glfwGetPrimaryMonitor();
        GLFWwindow * window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, start_fullscreen, NULL);
        if (!window) {
                glfwTerminate();
                die("Failed to create GLFW window");
        }

        // Make the GLFW window the current rendering context
        glfwMakeContextCurrent(window);

        // Load glad
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                glfwDestroyWindow(window);
                glfwTerminate();
                die("Failed to initialize GLAD");
        }

        // Area of the window for openGL to render
        glViewport(0, 0, WIDTH, HEIGHT);

        // Window resize events
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // Mouse window events
        glfwSetCursorPosCallback(window, cursor_position_callback);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwSetCursorEnterCallback(window, cursor_enter_callback);

        GLfloat vertices[] = {
                //     COORDINATES     /        COLORS      /   TexCoord  //
                1.0f,  1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Lower left corner
                1.0f,  -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // Upper left corner
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Upper right corner
                -1.0f, 1.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f  // Lower right corner
        };

        GLuint indices[] = {
                // note that we start from 0!
                0, 1, 3, // first triangle
                1, 2, 3  // second triangle
        };

        GLuint VAO, VBO, EBO;

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof indices, indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(6 * sizeof(GLfloat)));

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // Shader program
        GLuint shader_program = glCreateProgram();
        compile_shaders(&shader_program);

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // Texture
        GLint imgWidth, imgHeigth, numColCh;
        // Flip image
        // stbi_set_flip_vertically_on_load(True);
        uchar * bytes = stbi_load(TEXTURE_PATH, &imgWidth, &imgHeigth, &numColCh, 0);
        GLuint texture;

        glGenTextures(1, &texture);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // For images with an alpha channel use GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeigth, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);

        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(bytes);

        glBindTexture(GL_TEXTURE_2D, 0);

        // Uniforms
        // u_time uniform
        GLint u_time_location = glGetUniformLocation(shader_program, UNIFORM_TIME);
        // u_resolution uniform
        GLint u_resolution_location = glGetUniformLocation(shader_program, UNIFORM_RESOLUTION);
        // u_mouse uniform
        GLint u_mouse_location = glGetUniformLocation(shader_program, UNIFORM_MOUSE);
        // texture uniform
        GLint tex0Uni = glGetUniformLocation(shader_program, UNIFORM_TEXTURE);

        // Render loop
        while (!glfwWindowShouldClose(window)) {
                // Input
                process_input(window, &shader_program);

                // Render background color
                glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
                // Clear the back buffer
                glClear(GL_COLOR_BUFFER_BIT);

                GLfloat time = (GLfloat)glfwGetTime();

                glUseProgram(shader_program);

                glUniform1f(u_time_location, time);
                glUniform2f(u_resolution_location, WIDTH, HEIGHT);
                glUniform2f(u_mouse_location, xMousePos, yMousePos);
                glUniform1i(tex0Uni, 0);

                glBindTexture(GL_TEXTURE_2D, texture);

                glBindVertexArray(VAO);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                // glDrawArrays(GL_TRIANGLES, 0, 3);

                // Swap buffers and pull IO events
                glfwSwapBuffers(window);
                glfwPollEvents();
        }

        // Dealocate resources
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);

        // Delete Textures
        glDeleteTextures(1, &texture);

        glDeleteProgram(shader_program);

        // Destroy current window and terminate GLFW
        glfwDestroyWindow(window);
        glfwTerminate();

        return EXIT_SUCCESS;
}

void
process_input(GLFWwindow * const window, GLuint * const shader_program)
{
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) || glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
                glfwSetWindowShouldClose(window, GLFW_TRUE);
        } else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
                glDeleteProgram(*shader_program);
                *shader_program = glCreateProgram();
                compile_shaders(shader_program);
        }
        // Not working for some reason
        // else if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        //   GLFWmonitor *monitor = glfwGetWindowMonitor(window);
        //   if(monitor == NULL) {
        //     const GLFWvidmode *mode = glfwGetVideoMode(monitor);
        //     glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height,
        //                          mode->refreshRate);
        //   } else {
        //     glfwSetWindowMonitor(window, NULL, 0, 0, WIDTH, HEIGHT, 0);
        //   }
        // }
}

void
die(char const * const error)
{
        fprintf(stderr, "ERROR: %s\n", error);
        exit(EXIT_FAILURE);
}

static void
cursor_position_callback(ALLOW_UNUSED GLFWwindow * window, double xPos, double yPos)
{
        if (inside_window) {
                xMousePos = (GLfloat)xPos;
                yMousePos = (GLfloat)yPos;
        }
}

void
cursor_enter_callback(ALLOW_UNUSED GLFWwindow * window, int inside)
{
        inside_window = inside ? True : False;
}

void
framebuffer_size_callback(ALLOW_UNUSED GLFWwindow * window, int width, int height)
{
        glViewport(0, 0, width, height);
}
