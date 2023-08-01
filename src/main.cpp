#include "stdafx.h"

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


static void key_callback(
	GLFWwindow* window,
	int key,
	[[maybe_unused]] int scancode,
	[[maybe_unused]] int action,
	[[maybe_unused]] int mods
) {
	// Close on ESC press
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


static void error_callback(
	[[maybe_unused]] int error,
	const char* description
) {
	std::cerr << "Error: " << description << '\n';
}



int main() {
	// Init lib
	if (!glfwInit()) return -1;

	// Min version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	glfwSetErrorCallback(error_callback);

	// Create window
	GLFWwindow* window = glfwCreateWindow(640, 480, "Funny triangle", nullptr, nullptr);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	// Key callbacks
	glfwSetKeyCallback(window, key_callback);

	// Make the window's current context
	glfwMakeContextCurrent(window);
	gladLoadGL();

#ifndef NDEBUG
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << '\n';
#endif

	glfwSwapInterval(1);


	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		// Render hete
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
