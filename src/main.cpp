#include "stdafx.hpp"

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <array>
#include <cmath>
#include <iostream>

#include "util/color.hpp"


// Doing static_cast because GCC doesn't have std::sqrtf.
// Stick to the standard dammit.
constexpr float sqrt_of_3 = 1.73205080f;

constexpr auto vertex_shader_src =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}";

constexpr auto fragment_shader_src =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.29f, 0.56f, 1.0f, 0.9f);\n"
"}";


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


GLuint compile_shader(GLuint shader_type, const char* shader_src) {
	GLuint shader = glCreateShader(shader_type);

	glShaderSource(shader, 1, &shader_src, nullptr);
	glCompileShader(shader);

	return shader;
}

GLuint create_shader_program(const char* vertex_shdr_src, const char* fragment_shdr_src) {
	GLuint vertex_shader = compile_shader(GL_VERTEX_SHADER, vertex_shdr_src);
	GLuint fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fragment_shdr_src);

	GLuint shader_program = glCreateProgram();

	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return shader_program;
}


int main() {
	constexpr int window_heigth = 520;
	constexpr int window_width = 520;
	constexpr util::rgb_float bg_color(115u, 251u, 211u);

	constexpr std::array vertices {
		-0.5f, -0.5f * sqrt_of_3 / 3, 0.0f,     // lower left corner
		 0.5f, -0.5f * sqrt_of_3 / 3, 0.0f,     // lower right corner
		 0.0f,  0.5f * sqrt_of_3 * 2/3, 0.0f    // upper corner
	};


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

	// Visible area
	glViewport(0, 0, window_heigth, window_width);

#ifndef NDEBUG
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << '\n';
#endif

	// Compile shaders
	GLuint shader_program = create_shader_program(vertex_shader_src, fragment_shader_src);

	// Vertex buffer object
	GLuint VAO, VBO;

	// Generate VAO and VBO with 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Set this VAO as the current
	glBindVertexArray(VAO);

	// Bind the VBO and "upload" the vertices into the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

	// Configure the the Vertex Array so OpenGL knows how to read the VBO and enable it
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		// Set color and render
		glClearColor(bg_color.r, bg_color.g, bg_color.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Tell which shader program we want to use
		glUseProgram(shader_program);
		glBindVertexArray(VAO);

		// Draw shit
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	// Delete all objects
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shader_program);

	// Clean everything
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
