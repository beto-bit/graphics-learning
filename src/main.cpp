#include "stdafx.hpp"

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <array>
#include <iostream>

#include "util/color.hpp"


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
	constexpr int window_heigth = 640;
	constexpr int window_width = 480;
	constexpr util::rgb_float bg_color(77u, 190u, 255u);

	// Init lib
	if (!glfwInit()) return -1;

	// Min version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwSetErrorCallback(error_callback);

	// Create window
	GLFWwindow* window = glfwCreateWindow(window_heigth, window_width, "Hi OpenGL", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		std::cerr << "Failed to create window" << std::endl;
		return -1;
	}

	// Make the window's current context
	glfwMakeContextCurrent(window);

	// Key callbacks
	glfwSetKeyCallback(window, key_callback);

	gladLoadGL();

#ifndef NDEBUG
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << '\n';
#endif

	// Visible area
	glViewport(0, 0, window_heigth, window_width);

	// Set color and render
	glClearColor(bg_color.r, bg_color.g, bg_color.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Swap front and back buffers
	glfwSwapBuffers(window);

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		// Poll for and process events
		glfwPollEvents();
	}

	// Clean everything
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
