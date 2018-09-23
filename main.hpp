
/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2017-2018 Anish Bhobe
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef _MAIN_HPP
#define _MAIN_HPP

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <iostream>

#include <chrono>
#include <material/material.hpp>
#include <model/mesh.hpp>
#include <shader/shader.hpp>
#include <texture/texture.hpp>

/*
 * Main Application class
 * Basically an overarching class that defines the entire
 * configuration and usage of the application.
 */

class Time {
	using hr_clock = std::chrono::high_resolution_clock;

public:
	uint64_t prevFrame;
	uint64_t currFrame;
	float	deltaTime;

	void Init() {
		currFrame = hr_clock::now().time_since_epoch().count();
	}

	void Update() {
		prevFrame = currFrame;
		currFrame = hr_clock::now().time_since_epoch().count();
		deltaTime = static_cast<float>((currFrame - prevFrame) / 1000000000.0f);
		if (deltaTime > 1.0f) {
			deltaTime = 1.0f / 60.0f;
		}
	}
};

class MainApp {

	GLFWwindow*   m_Window;
	Time		  m_Timer;
	ShaderLoader  m_ShaderLoader;
	TextureLoader m_TextureLoader;
	MeshLoader	m_MeshLoader;

	void
	InitWindow();
	void LoadOpenGL();
	void Setup();
	void MainLoop();
	void Update(float deltaTime);
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

	glViewport(0, 0, WIDTH, HEIGHT);
}

// Main Gameloop
void MainApp::MainLoop() {

	m_Timer.Init();
	while (!glfwWindowShouldClose(m_Window)) {
		m_Timer.Update();
		glfwPollEvents();

		Update(m_Timer.deltaTime);

		glfwSwapBuffers(m_Window);
	}
}

// Cleanup part to delete everythin what has been created.
void MainApp::Cleanup() {

	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

#endif /* _MAIN_HPP */
