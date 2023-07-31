#include "stdafx.h"
#include <fstream>
#include <future>
#include <optional>
#include <string>

std::optional<std::string> file_to_string(const std::string& path) {
	std::ifstream file{ path };

	if (!file.is_open()) return std::nullopt;

	std::string content{
		std::istreambuf_iterator<char>{file},
		std::istreambuf_iterator<char>{}
	};

	return std::make_optional(content);
}

std::future<std::optional<std::string>> async_file_to_string(const std::string& path) {
	return std::async(std::launch::async, file_to_string, path);
}