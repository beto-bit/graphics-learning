#include "stdafx.h"

#include <array>
#include <iostream>

#include <fmt/core.h>
#include <fmt/ranges.h>

int main() {
	std::array arr{ 1, 2, 3, 4 };

	fmt::print("{}", arr);

	return 0;
}
