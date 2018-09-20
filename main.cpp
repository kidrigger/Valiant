
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

// Set up the scene and object
void MainApp::Setup() {
}

// Update function
void MainApp::Update(float deltaTime) {
}

// Delete whatever is not important.
void MainApp::Teardown() {
}