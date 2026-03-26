#include <iostream>
#include "config.h"
#include <string>
#include <vector>

std::string string_to_lower(const std::string &str) {
        std::string new_str = "";
        for (char ch : str) {
                // ugh brother, ugh. ChatGPT doing some disgustring bug fixes
                new_str += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        }
        return new_str;
}

std::vector<int> find_substrings(const Config &cfg, std::string larger_string) {
        std::string substring = cfg.substring;
        if (cfg.case_insensitive) {
                std::cout << "We are case insensitive\n";
                larger_string = string_to_lower(larger_string);
                substring = string_to_lower(cfg.substring);
        }

        std::vector<int> list;
        int substring_length = cfg.substring.length();
        for (size_t i = 0; i + substring_length <= larger_string.length(); i++) {
                if (larger_string.compare(i, substring_length, cfg.substring) == 0) {
                        list.push_back((int)i);
                }
        }
        return list;
}


std::string remove_dashes(const std::string &str) {
        std::string new_str = "";
        for (char ch : str) {
                if (ch != '-') {
                        new_str += ch;
                }
        }
        return new_str;
}
