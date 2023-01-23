#include "lib\arc.h"
#include <iostream>
#include <string>
#include <vector>


int main(int argc, char* argv[]){

    bool flag_to_skip = false;

    std::vector<std::string> file_names;
    std::string result_arc;
    int frequency = 8;
    bool params[7] = {false};
    int password = 0;

    for (int i = 1; i < argc; i++) {
        if (!flag_to_skip) {
            if ((std::string) argv[i] == "-c" || (std::string) argv[i] == "--create") {
                params[0] = true;
            } else if ((std::string) argv[i] == "-f" ||
                       (size((std::string) argv[i]) > 7 && (argv[i])[1] == '-' && (argv[i])[2] == 'f')) {
                if (size((std::string) argv[i]) > 7 && (argv[i])[1] == '-' && (argv[i])[2] == 'f')
                    result_arc = ((std::string) argv[i]).substr(7, size((std::string) argv[i]) - 1);
                else {
                    result_arc = argv[i + 1];
                    flag_to_skip = true;
                }
                params[1] = true;
            } else if ((std::string) argv[i] == "-l" || (std::string) argv[i] == "--list") {
                params[2] = true;
            } else if ((std::string) argv[i] == "-x" || (std::string) argv[i] == "--extract") {
                params[3] = true;
            } else if ((std::string) argv[i] == "-a" || (std::string) argv[i] == "--append") {
                params[4] = true;
            } else if ((std::string) argv[i] == "-d" || (std::string) argv[i] == "--delete") {
                params[5] = true;
            } else if ((std::string) argv[i] == "-A" || (std::string) argv[i] == "--concatenate") {
                params[6] = true;
            } else if ((std::string) argv[i] == "-fr") {
                frequency = std::stoi(argv[i+1]);
                flag_to_skip = true;
            }
            else if ((std::string) argv[i] == "-pas"){
                 password = std::stoi(argv[i+1]);
                 flag_to_skip = true;
            }
            else
                file_names.push_back((std::string) argv[i]);
        }
        else{
            flag_to_skip = !flag_to_skip;
        }
    }


    todo(file_names, params, result_arc, frequency, password);

    return 0;
}