#pragma once

#include <string>
#include <vector>

struct Config {
        std::string substring;
        int substring_length;
        std::string file_name;
        bool show_line_nums;
        bool case_insensitive;
        bool just_display_find_count;
        bool display_find_count;
        int maximum_num_of_finds;
};

int handle_capital_N_flag(int Ns_index, const std::vector<std::string> &flags);
