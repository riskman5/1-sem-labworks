#include "lib\sandpile.h"
#include <iostream>
#include <string>


int main (int argc, char* argv[]){
    uint64_t params[4] = {0};
    std::string inpath;
    std::string outpath;
    std::string barier = " ";
    int inputcount = 0; //should be 5 to start the program


    for(int i = 1; i < argc; i++) {
        if ((std::string) argv[i] == "-l" || (std::string) argv[i] == "--length") {
            try {
                params[0] = std::stoi(argv[i + 1]);
                std::cout << "Length has been set" << '\n';
                inputcount++;
            }
            catch (const std::exception &ex) {
                std::cout << "Length is incorrect" << '\n';
            }
        }

        if ((std::string) argv[i] == "-w" || (std::string) argv[i] == "--width") {
            try {
                params[1] = std::stoi(argv[i + 1]);
                inputcount++;
                std::cout << "Width has been set" << '\n';
            }
            catch (const std::exception &ex) {
                std::cout << "Width is incorrect" << '\n';
            }
        }


        if ((std::string) argv[i] == "-m" || (std::string) argv[i] == "--max-iter") {
            try {
                params[2] = std::stoi(argv[i + 1]);
                inputcount++;
                std::cout << "Max count of iterations has been set" << '\n';
            }
            catch (const std::exception &ex) {
                std::cout << "Max count of iterations is incorrect";
            }
        }

        if ((std::string) argv[i] == "-f" || (std::string) argv[i] == "--freq") {
            try {
                params[3] = std::stoi(argv[i + 1]);
                inputcount++;
                std::cout << "Frequency has been set" << '\n';
            }
            catch (const std::exception &ex) {
                std::cout << "Frequency is incorrect";
            }
        }


        if ((std::string) argv[i] == "-i" || (std::string) argv[i] == "--input") {
            inpath = argv[i + 1];
            std::cout << "input path has been set" << '\n';
            inputcount++;
        }

        if ((std::string) argv[i] == "-o" || (std::string) argv[i] == "--output") {
            outpath = argv[i + 1];
            std::cout << "output path has been set" << '\n';
            inputcount++;
        }

        if((std::string) argv[i] == "-b" || (std::string) argv[i] == "--barier"){
            barier = argv[i+1];
        }
    }
    if (inputcount >= 5) {
        Grid grid = Grid(params[0], params[1], params[2], params[3], outpath);
        clear_grid(&grid);
        if(barier != " ") set_baries(&grid, barier);
        set_sand(&grid, inpath);
        crumbling(&grid);
    }
    return 0;
}