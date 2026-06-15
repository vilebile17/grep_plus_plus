#include <string>
#include <vector>

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
