#include "main.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

// Cursor state
GLfloat xMousePos, yMousePos = 0.f;
Bool inWindow = False;

int main() {

  if (!glfwInit()) {
    die("Could not initialize GLFW");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MAJOR_VERS);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MINOR_VERS);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  void *start_fullscreen = NULL;
  // void *start_fullscreen = glfwGetPrimaryMonitor();

  // Create GLFW window object
  GLFWwindow *window =
      glfwCreateWindow(WIDTH, HEIGHT, TITLE, start_fullscreen, NULL);

  if (!window) {
    glfwTerminate();
    die("Failed to create GLFW window");
  }

  // Make the GLFW window the current rendering context
  glfwMakeContextCurrent(window);

  // Load glad
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    die("Failed to initialize GLAD");
  }

  // Aria of the window for openGL to render
  glViewport(0, 0, WIDTH, HEIGHT);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Mouse
  glfwSetCursorPosCallback(window, cursor_position_callback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  glfwSetCursorEnterCallback(window, cursor_enter_callback);

  float vertices[] = {
      1.0f,  1.0f,  0.0f, // top right
      1.0f,  -1.0f, 0.0f, // bottom right
      -1.0f, -1.0f, 0.0f, // bottom left
      -1.0f, 1.0f,  0.0f  // top left
  };

  unsigned int indices[] = {
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
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
  //                       (void *)(3 * sizeof(float)));
  // glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);

  // Shader program
  GLuint shader_program = glCreateProgram();
  compile_shaders(&shader_program);

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // Render loop
  while (!glfwWindowShouldClose(window)) {

    // Input
    process_input(window, &shader_program);

    // Render background color
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    // Clear the back buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // u_time uniform
    GLfloat time = (GLfloat)glfwGetTime();
    GLint u_time_location = glGetUniformLocation(shader_program, UNIFORM_TIME);

    // u_resolution uniform
    GLint u_resolution_location =
        glGetUniformLocation(shader_program, UNIFORM_RESOLUTION);

    // u_mouse uniform
    GLint u_mouse_location =
        glGetUniformLocation(shader_program, UNIFORM_MOUSE);

    glUseProgram(shader_program);
    glUniform1f(u_time_location, time);
    glUniform2f(u_resolution_location, WIDTH, HEIGHT);
    glUniform2f(u_mouse_location, xMousePos, yMousePos);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    // glBindVertexArray(0);

    // Swap buffers and pull IO events
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Dealocate resources
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);

  glDeleteProgram(shader_program);

  // Destroy current window and terminate GLFW
  glfwTerminate();

  return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window, GLuint *shader_program) {

  if (glfwGetKey(window, GLFW_KEY_ESCAPE) ||
      glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, TRUE);
  else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {

    glDeleteProgram(*shader_program);
    *shader_program = glCreateProgram();

    compile_shaders(shader_program);
  }
  // Not working for some reason
  // else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
  //   GLFWmonitor *monitor = glfwGetWindowMonitor(window);
  //   if (monitor == NULL) {
  //     const GLFWvidmode *mode = glfwGetVideoMode(monitor);
  //     glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height,
  //                          mode->refreshRate);
  //   } else {
  //     glfwSetWindowMonitor(window, NULL, 0, 0, WIDTH, HEIGHT, 0);
  //   }
  // }
}

char *get_shader(char *shader_file) {

  FILE *file = fopen(shader_file, "r");
  if (!file) {
    die("Could not open the shader file");
  }

  fseek(file, 0, SEEK_END);
  unsigned long int length = (unsigned long int)ftell(file);
  fseek(file, 0, SEEK_SET);

  char *shader_string = (char *)malloc(sizeof(char) * (length + 1));
  if (!shader_string) {
    die("Could not alocate memory for file contents");
  }

  char cursor;
  unsigned int index = 0;

  while ((cursor = (char)fgetc(file)) != EOF) {
    shader_string[index] = cursor;
    index++;
  }

  shader_string[index] = '\0';

  fclose(file);

  return shader_string;
}

void die(const char *error) {
  fprintf(stderr, "%s\n", error);
  exit(EXIT_FAILURE);
}

void compile_shaders(const GLuint *const shader_program) {

  char *vertex_shader_source = get_shader(VERTEX_SHADER_PATH);

  GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, (char const *const *)&vertex_shader_source,
                 NULL);
  glCompileShader(vertex_shader);

  int success;
  char info_log[512];
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
    fprintf(stderr, "Vertex shader compilation error: %s\n", info_log);
    return;
  }

  free(vertex_shader_source);

  char *fragment_shader_source = get_shader(FRAGMENT_SHADER_PATH);

  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1,
                 (char const *const *)&fragment_shader_source, NULL);
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

static void cursor_position_callback(GLFWwindow *window, double xPos,
                                     double yPos) {
  if (inWindow) {
    xMousePos = (GLfloat)xPos;
    yMousePos = (GLfloat)yPos;
  }
}

void cursor_enter_callback(GLFWwindow *window, int inside) {
  if (inside) {
    inWindow = True;
  } else {
    inWindow = False;
  }
}
