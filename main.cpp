
#include "main.hpp"

int main() {

	MainApp app;

	try {
		app.run();
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}