#include <iostream>
#include <fstream>
#include <string>
#include <regex>

int main()
{
    std::ifstream input("input.txt");
    if(!input)
    {
        std::cerr << "Nie można otworzyć pliku!" << std::endl;
        return 1;   //no file, no fun
    }

    //create string named content by copying each char one by one from beginning to the end of the file
    std::string content((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>()); 
    input.close();

    std::regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\))"); //additional () to create groups for regex match finding, then match[1] is 1st number as a string
    std::sregex_iterator it(content.begin(), content.end(), pattern); //creates iterator it that looks for the pattern
    std::sregex_iterator end; //creates iterator end that points to the end of search

    std::vector<std::pair<int, int>> pairs; //vector of found numbers in pairs

    while(it != end) //as long as we have next pattern matches
    {
        std::smatch match = *it; //get match

        pairs.emplace_back(std::stoi(match[1].str()), std::stoi(match[2].str())); //cast string numbers to int and save them in pairs pair

        ++it; //go to next match
    }


    int sum = 0;
    for(const auto& p : pairs)
    {
        sum += p.first * p.second; //multiply pair and add it to the sum
    }
    
    std::cout << sum <<std::endl;

    return 0;
}