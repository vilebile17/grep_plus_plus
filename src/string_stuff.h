#pragma once

#include <string>
#include <vector>
#include "config.h"

std::string string_to_lower(const std::string &str);
std::vector<int> find_substrings(const Config &cfg, std::string larger_string);
std::string remove_dashes(const std::string &str);
