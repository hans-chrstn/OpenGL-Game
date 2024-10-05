#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class GlApp {
public:
  void run() {
    initWindow();
    registerCallback();
    mainLoop();
  }
private:
  GLFWwindow* window;
  const int width = 800;
  const int height = 600;
  const char* APPNAME = "OPENGL APP";

  void initWindow() {
    if(!glfwInit()) {
      throw std::runtime_error("Failed to initialize GLFW!");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, APPNAME, NULL, NULL);

    if(window == NULL) {
      glfwTerminate();
      throw std::runtime_error("Failed to create GLFW window!");
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      glfwTerminate();
      std::runtime_error("Failed to initialize GLAD!");
    }
  }

  void registerCallback() {
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  }

  void processInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, true);
    }
  }

  static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
  }

  void mainLoop() {
    while (!glfwWindowShouldClose(window)) {
      processInput(window);

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      glfwSwapBuffers(window);
      glfwPollEvents();
    }
  }
};

int main() {
  try {
    GlApp app;
    app.run();
  } catch (std::exception& e) {
      std::cerr << "Error: " << e.what() << std::endl; 
      return EXIT_FAILURE;
  }
    glfwTerminate();
    return EXIT_SUCCESS;
}

