#pragma once

namespace util {
	struct position
	{
		float x{};
		float y{};
	};

	struct color
	{
		float r{};
		float g{};
		float b{};
	};

	struct vertex
	{
		position pos{};
		color col{};
	};

	struct triangle
	{
		vertex vertices[3];
	};
}