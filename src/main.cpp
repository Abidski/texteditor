#include <GL/glew.h>
#include <GL/glext.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>

static void ParseShader(const std::string &filepath) {

  std::ifstream stream(filepath);

  enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };

  std::string line;
  std::stringstream ss[2];
  while (getline(stream, line)) {
    if (line.find("#shader") != std::string::npos) {
      if (line.find("vertex") != std::string::npos)
        ;
      // set mode to vertex
      else if (line.find("fragment") != std::string::npos)
        ;
      // set mode to fragment
    }
  }
}
static unsigned int CompileShader(unsigned int type,
                                  const std::string &source) {

  unsigned int id = glCreateShader(type);
  const char *src = source.c_str();
  glShaderSource(id, 1, &src, NULL);
  glCompileShader(id);

  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char *message = (char *)(alloca(length * sizeof(char)));
    printf("%s", message);
    printf("%s", "Failed to compile");
    glDeleteShader(id);
    return 0;
  }

  return id;
}
static unsigned int CreateShader(const std::string &vertexShader,
                                 const std::string &fragmentShader) {

  unsigned int program = glCreateProgram();
  unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
  unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glValidateProgram(program);
  glDeleteShader(vs);
  glDeleteShader(fs);

  return program;
}
int main(void) {
  GLFWwindow *window;

  /* Initialize the library */
  if (!glfwInit())
    return -1;

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(640, 480, "Text Editor", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  if (glewInit() != GLEW_OK)
    std::cout << "Errorf!" << std::endl;

  float positions[6] = {-0.5f, -0.5f, 0.0f, 0.5f, 0.5f, -0.5f};

  unsigned int buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

  unsigned int shader = CreateShader(vertexShader, fragmentShader);
  glUseProgram(shader);
  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
