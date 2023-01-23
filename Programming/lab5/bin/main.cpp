#include <functional>
#include <lib/ArgParser.h>
#include <sstream>
#include <string>
#include <algorithm>

#include <iostream>
#include <numeric>
#include <iterator>


std::vector<std::string> SplitString(const std::string& str) {
    std::istringstream iss(str);

    return {std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>()};
}

int main(int argc, char** argv) {
    std::vector<std::string> arguments;
    for (int i = 1; i < argc; i++){
        arguments.push_back(argv[i]);
    }

    ArgumentParser::ArgParser parser("My Parser");
    parser.AddStringArgument('i', "input", "File path for input file").MultiValue(1);
    parser.AddIntArgument("number", "Some Number");

    for (int i = 1; i < arguments.size(); i++){
        if (arguments[i].find(".exe") != std::string::npos){
            int j = i;
            std::string temp_string = arguments[i];
            arguments.erase(arguments.begin() + i);
            while ((arguments[j].find('-') == std::string::npos) && j < arguments.size()) {
                temp_string += " " + arguments[j];
                arguments.erase(arguments.begin() + j);
                j++;
            }
            const char* a = temp_string.c_str();
            std::string value;
            value = system(a);
            if (parser.GetIntValue(argv[i-1]) != -1){
                parser.del_argument(argv[i-1]);
                parser.AddStringArgument(argv[i-1]);
                parser.GetStringValue(argv[i-1]);
            }
            if(!parser.GetFlag(argv[i-1])){
                parser.del_argument(argv[i-1]);
                parser.AddStringArgument(argv[i-1]);
                parser.GetStringValue(argv[i-1]);
            }
        }
    }

    parser.Parse(arguments);

    return 0;
}
