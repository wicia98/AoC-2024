#include <iostream>
#include <fstream>
#include <string>
#include <regex>

int main() {
    std::ifstream input("input.txt");
    if (!input) {
        std::cerr << "Nie można otworzyć pliku!" << std::endl;
        return 1;   // No file, no fun
    }

    // Read the entire file content into a string
    std::string content((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    input.close();

    // Define regex pattern to match `do()`, `dont()`, and `mul(X,Y)`
    std::regex pattern(R"(do\(\)|dont\(\)|mul\((\d{1,3}),(\d{1,3})\))");
    std::sregex_iterator it(content.begin(), content.end(), pattern);
    std::sregex_iterator end;

    bool active = false;  // Tracks whether multiplication is valid
    int sum = 0;

    while (it != end) {
        std::smatch match = *it;

        std::string match_str = match[0].str(); // Get full match
        if (match_str == "do()") {
            active = true;
        } else if (match_str == "dont()") {
            active = false;
        } else if (active && match[1].matched && match[2].matched) {
            // If active, multiply extracted numbers
            int a = std::stoi(match[1].str());
            int b = std::stoi(match[2].str());
            sum += a * b;
        }

        ++it;  // Move to next match
    }

    std::cout << "Sum: " << sum << std::endl;
    return 0;
}
