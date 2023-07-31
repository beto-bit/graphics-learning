#include "stdafx.h"

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <string>
#include <optional>

#include "util/asyncReadFile.h"
#include "util/shape.h"


constexpr shp::triangle triangle = {{
	{ -0.6f, -0.4f, 1.f, 0.f, 0.f },
	{  0.6f, -0.4f, 0.f, 1.f, 0.f },
	{  0.f,   0.6f, 0.f, 0.f, 1.f }
}};

constexpr auto vertexPath = "assets/vertex.glsl";
constexpr auto fragmentPath = "assets/fragment.glsl";


int main() {
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
