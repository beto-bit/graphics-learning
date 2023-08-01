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


GLuint load_shaders_to_program(
	const std::string& vertex_shader_src,
	const std::string& fragment_shader_src
) {
	const char* vertex_shader_text = vertex_shader_src.c_str();
	const char* fragment_shader_text = fragment_shader_src.c_str();

	// Load Vertex Shader
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_text, nullptr);
	glCompileShader(vertex_shader);

	// Load Fragment Shader
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_text, nullptr);
	glCompileShader(fragment_shader);


	// Attach shaders
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	return program;
}


static void key_callback(
	GLFWwindow* window,
	int key,
	int scancode,
	int action,
	int mods
) {
	// Close on ESC press
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


static void error_callback(
	int error,
	const char* description
) {
	std::cerr << "Error: " << description << '\n';
}



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
