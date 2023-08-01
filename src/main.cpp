#include "stdafx.h"

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <string>
#include <optional>

#include "util/asyncReadFile.h"
#include "util/linmath.h" // Grabbed from here: https://github.com/glfw/glfw/blob/master/deps/linmath.h
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
	auto vertex_shader_src = async_file_to_string(vertexPath);
	auto fragment_shader_src = async_file_to_string(fragmentPath);

	// Init lib
	if (!glfwInit()) return -1;

	// Min version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

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

	glfwSwapInterval(1);

	// ==================================================
	// Shady OpenGL stuff I don't really wan't to dive in
	GLuint vertex_buffer;

	// Create and bind buffer for the triangle idk
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle.vertices, GL_STATIC_DRAW);

	GLuint program = load_shaders_to_program(
		vertex_shader_src.get().value(),
		fragment_shader_src.get().value()
	);

	// Positioning stuff I guess
	GLint mvp_location = glGetUniformLocation(program, "MVP");
	GLint vpos_location = glGetAttribLocation(program, "vPos");
	GLint vcol_location = glGetAttribLocation(program, "vCol");


	// what
	glEnableVertexAttribArray(vpos_location);
	glVertexAttribPointer(
		vpos_location,
		2,
		GL_FLOAT,
		false,
		sizeof(shp::vertex),
		nullptr
	);

	glEnableVertexAttribArray(vcol_location);
	glVertexAttribPointer(
		vcol_location,
		3,
		GL_FLOAT,
		false,
		sizeof(shp::vertex),
		reinterpret_cast<void*>(sizeof(float) * 2)
	);
	// End of shady stuff I don't want to dive in
	// ==========================================


	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		// Not so shady stuff
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		float ratio = width / static_cast<float>(height);

		// A canvas or something like that
		glViewport(0, 0, width, height);

		// Render here
		glClear(GL_COLOR_BUFFER_BIT);


		// Cool rotations I guess
		mat4x4 m, p, mvp;

		mat4x4_identity(m);
		mat4x4_rotate_Z(m, m, static_cast<float>(glfwGetTime()));
		mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		mat4x4_mul(mvp, p, m);


		// Apply everything (?)
		glUseProgram(program);
		glUniformMatrix4fv(mvp_location, 1, false, reinterpret_cast<const GLfloat*>(mvp));
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
