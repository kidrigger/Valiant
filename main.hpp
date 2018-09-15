
#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <iostream>

#include <shader/shader.hpp>

class MainApp {

	GLFWwindow* m_Window;

	void InitWindow();
	void LoadOpenGL();
	void MainLoop();
	void Cleanup();

public:
	static const int WIDTH  = 800;
	static const int HEIGHT = 600;

	void run() {
		InitWindow();
		LoadOpenGL();
		MainLoop();
		Cleanup();
	}
};

void MainApp::InitWindow() {

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	m_Window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Workbench", nullptr, nullptr);
	if (!m_Window) {
		throw std::runtime_error("GLFW::WINDOW_INIT_ERR");
	}

	glfwMakeContextCurrent(m_Window);
}

void MainApp::LoadOpenGL() {

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("GLAD::FAILED_OPENGL_LOAD");
	}
}

void MainApp::MainLoop() {

	while (!glfwWindowShouldClose(m_Window)) {
		glfwPollEvents();
	}
}

void MainApp::Cleanup() {

	glfwDestroyWindow(m_Window);
	glfwTerminate();
}