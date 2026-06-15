#include <iostream>
#include <string>
#include "config.h"

void final_printing( const Config &cfg, int find_count) {
        if (find_count == 0) {
                if (cfg.just_display_find_count) {
                        std::cout << 0 << "\n";
                } else {
                        std::cout << "Oof, couldn't find that substring unfortunately...\n";
                }
        } else if (cfg.display_find_count) {
                std::cout << "\nSubstring was found \033[32m" << find_count
                          << "\033[0m time";
                if (find_count > 2) {
                        std::cout << "s";
                }
                std::cout << "\n";
                }
        else if (cfg.just_display_find_count) {
                std::cout << find_count << "\n";
    }
}

void print_find(const Config &cfg, std::string line, int line_num, int start_index) {
        if (cfg.show_line_nums) {
                std::cout << "\033[95m" << line_num << ": " << "\033[0m";
        }
        int end_index = start_index + cfg.substring_length;
        std::cout << line.substr(0, start_index) << "\033[36;1m"
                  << line.substr(start_index, cfg.substring_length) << "\033[0m"
                  << line.substr(end_index, line.length() - end_index) << "\n";
}

void explanation() {
        std::cout << "\033[36mgrep++\033[0m finds a substring in a file.\n\n"
                  << "USAGE: \033[36mgrep++\033[0m [flags] <substring> <file_name>\n"
                  << "EXAMPLE: \033[36mgrep++\033[0m 'hello' file.txt\n\n"
                  << "FLAGS:\n"
                  << "  \033[95m-i\033[0m = Case-insensitive\n"
                  << "  \033[95m-c\033[0m = At the end of the output it shows the "
                  << "number of times the substring was found\n"
                  << "  \033[95m-C\033[0m = \033[1mJust\033[0m shows the number of "
                  << "times which the substring was found\n"
                  << "  \033[95m-n\033[0m = Shows the line numbers next to the lines "
                  << "themselves\n"
                  << "  \033[95m-N <num>\033[0m = \033[1mOnly\033[0m finds \033[3mnum\033[0m"
                  << " instances of that substring\n\n"
                  << "  \033[95m-v\033[0m = Displays the version of the program\n"
                  << "  \033[95m-h\033[0m = Displays this message\n";
}
