#include "stdafx.h"

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <string>
#include <optional>

#include "util/asyncReadFile.h"


int main() {
	if (auto file = file_to_string("assets/data.txt")) {
		std::cout << file.value() << '\n';
	}

	// Init lib
	if (!glfwInit()) return -1;

	// Create window
	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello Window!", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	// Make the window's current context
	glfwMakeContextCurrent(window);
	gladLoadGL();

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		// Render here
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
