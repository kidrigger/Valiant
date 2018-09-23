
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

#include "main.hpp"
#include <cstdlib>

int main() {

	MainApp app;

	try {
		app.run();
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

Material* mat;
Mesh*	 mesh;
// Set up the scene and object
void MainApp::Setup() {
	auto shdr = m_ShaderLoader.Load("default", "assets/shaders/vshader.vs", "assets/shaders/fshader.fs");
	mesh	  = m_MeshLoader.Load("tet");
	mat		  = new Material(shdr);
	auto tex  = m_TextureLoader.Load("text2d", "assets/models/skybox/front.jpg", {});
	mat->SetTexture("text2d", tex, 2);
	mat->Attach();
}

// Update function
void MainApp::Update(float deltaTime) {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glBindVertexArray(mesh->m_VAO);
	glDrawElements(mesh->m_Mode, mesh->m_Count, GL_UNSIGNED_INT, 0);
}

// Delete whatever is not important.
void MainApp::Teardown() {
	delete mat;
}