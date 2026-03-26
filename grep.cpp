#include <cctype>
#include <cstddef>
#include <fstream>
#include <iostream>
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

struct Line_Info {
        std::string line;
        int line_num;
};

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

void print_find(const Config &cfg, const Line_Info &line_info, int start_index) {
        if (cfg.show_line_nums) {
                std::cout << "\033[95m" << line_info.line_num << ": " << "\033[0m";
        }
        int end_index = start_index + cfg.substring_length;
        std::cout << line_info.line.substr(0, start_index) << "\033[36;1m"
                  << line_info.line.substr(start_index, cfg.substring_length) << "\033[0m"
                  << line_info.line.substr(end_index, line_info.line.length() - end_index) << "\n";
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

int handle_capital_N_flag(int Ns_index, const std::vector<std::string> &flags) {
        if (flags[Ns_index].find('N') == std::string::npos) {
                return 0;
        }

        if (flags.size() == Ns_index + 1) {
                return -1;
        }

        std::string digits = "0123456789";
        for (char ch : flags[Ns_index + 1]) {
                if (digits.find(ch) == std::string::npos) {
                        return -1;
                }
        }

        return std::stoi(flags[Ns_index + 1]);
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

bool handle_starting_indices(const Config &cfg, Line_Info &line_info, std::vector<int> starting_indices, int &find_count) {
        for (int start_index : starting_indices) {
                if (!cfg.just_display_find_count) {
                        print_find(cfg, line_info, start_index);
                }
                find_count++;

                if (cfg.maximum_num_of_finds != 0 && find_count >= cfg.maximum_num_of_finds) {
                        return true;
                }
        }
        line_info.line_num++;
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
                        std::cout << "\033[36mgrep++\033[0m version 1.7.2\n";
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
        Line_Info line_info {"", 1};

        while (std::getline(file, line)) {
                starting_indices = find_substrings(cfg, line);
                line_info.line = line;
                bool stop_loop = handle_starting_indices(cfg, line_info, starting_indices, find_count);
                if (stop_loop) {
                        break;
                }
        }

        final_printing(cfg, find_count);
}
