#pragma once

#include "stdafx.h"
#include <future>
#include <string>
#include <optional>

std::optional<std::string> file_to_string(const std::string& path);

std::future<std::optional<std::string>> async_file_to_string(const std::string& path);
