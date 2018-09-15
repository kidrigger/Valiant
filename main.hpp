
#ifndef _MAIN_HPP
#define _MAIN_HPP

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <iostream>

#include <shader/shader.hpp>

/*
 * Main Application class
 * Basically an overarching class that defines the entire
 * configuration and usage of the application.
 */

class MainApp {

	GLFWwindow* m_Window;

	void InitWindow();
	void LoadOpenGL();
	void Setup();
	void MainLoop();
	void Teardown();
	void Cleanup();

public:
	static const int WIDTH  = 800;
	static const int HEIGHT = 600;

	void run() {
		InitWindow();
		LoadOpenGL();
		Setup();
		MainLoop();
		Teardown();
		Cleanup();
	}
};

// Initialize window in GLFW
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

// Load OpenGL using GLFW
void MainApp::LoadOpenGL() {

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("GLAD::FAILED_OPENGL_LOAD");
	}
}

// Main Gameloop
void MainApp::MainLoop() {

	while (!glfwWindowShouldClose(m_Window)) {
		glfwPollEvents();
	}
}

// Cleanup part to delete everythin what has been created.
void MainApp::Cleanup() {

	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

#endif /* _MAIN_HPP */
