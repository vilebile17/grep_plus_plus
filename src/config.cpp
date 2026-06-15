#include <string>

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
