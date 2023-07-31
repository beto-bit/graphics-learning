#include "stdafx.h"

#include <array>
#include <iostream>

int main() {
	std::array arr{ 1, 2, 3, 4 };

	for (int num : arr)
		std::cout << num << '\n';

	return 0;
}
