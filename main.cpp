#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "config.h"
#include "util.h"
#include "printing.h"
#include "string_stuff.h"

bool helper_for_starting_indices(
                const Config &cfg,
                const std::vector<int> &starting_indices,
                const std::string &line,
                const int line_num,
                int &find_count)
{
        for (int start_index : starting_indices) {
                if (!cfg.just_display_find_count) {
                        print_find(cfg, line, line_num, start_index);
                }
                find_count++;

                if (cfg.maximum_num_of_finds != 0 && find_count >= cfg.maximum_num_of_finds) {
                        return true;
                }
        }
        return false;
}

int main(int argc, char **argv) {
        Config cfg = {"", 0, "", false, false, false, false, 0};
        std::vector<std::string> flags;

        // ========= PARAMETERS ==========
        if (argc >= 3) {
                for (int i = 1; i < argc - 2; i++) {
                        flags.push_back(argv[i]);
                }

                for (size_t i = 0; i < flags.size(); i++) {
                        flags[i] = remove_dashes(flags[i]);
                }

                cfg.substring = argv[argc - 2];
                cfg.substring_length = cfg.substring.length();
                cfg.file_name = argv[argc - 1];
        } else if (argc == 2) {
                flags.push_back(remove_dashes(argv[1]));
        } else {
                explanation();
                return 1;
        }

        // ========== FLAGS ============
        for (int i = 0; i < flags.size(); i++) {
                std::string flag = flags[i];
                if (flag.find('v') != std::string::npos) {
                        std::cout << "\033[36mgrep++\033[0m version 1.7.3\n";
                        return 0;
                }
                if (flag.find('h') != std::string::npos) {
                        explanation();
                        return 0;
                }

                cfg.show_line_nums = flag.find('n') != std::string::npos || cfg.show_line_nums;
                cfg.case_insensitive = flag.find('i') != std::string::npos || cfg.case_insensitive;
                cfg.just_display_find_count = flag.find('C') != std::string::npos || cfg.just_display_find_count;
                cfg.display_find_count = flag.find('c') != std::string::npos || cfg.display_find_count;

                int temp = handle_capital_N_flag(i, flags);
                if (temp == -1) {
                        std::cout << "\033[31mERROR:\033[0m The flag '-N' must take an integer argument after\n"
                                  << "\033[36mEXAMPLE:\033[0m grep++ -N 5 'hello' test.txt\n";
                        return 1;
                } else if (temp > 0) {
                        cfg.maximum_num_of_finds = temp;
                }

                if (cfg.display_find_count && cfg.just_display_find_count) {
                        // Gives priority to just_display_find_count.
                        cfg.display_find_count = false;
                }
        }

        // ========== BAD CALL============
        if (argc < 3) {
                explanation();
                return 1;
        }

        // =========== ACTUAL STUFF GETS DONE HERE ============
        std::ifstream file(cfg.file_name);
        if (!file.is_open()) {
                std::cerr << "Failed to open the file...\n"
                          << "USAGE: grep++ [flags] <substring> \033[1m<file_name>\033[0m\n";
                          return 1;
        }

        std::string line;
        std::vector<int> starting_indices;
        int find_count;
        int line_num = 1;

        while (std::getline(file, line)) {
                starting_indices = find_substrings(cfg, line);
                bool stop_loop = helper_for_starting_indices(cfg, starting_indices, line, line_num, find_count);
                if (stop_loop) {
                        break;
                }
                line_num++;
        }

        final_printing(cfg, find_count);
}
