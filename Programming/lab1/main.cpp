#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int main (int argc, char* argv[]) {
    std::vector <std::string> filenames, functions;
    std::vector <char> functions_binary {0,0,0,0};
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]).find("-") == 0) {
            functions.push_back(argv[i]);
        }
        else{
            filenames.push_back(argv[i]);
        }
    }
    // add functions if there is more than one in prefix -
    std::string newfunction;
    std::string minus = "-";
    int functionssize = functions.size();
    for (int i = 0; i < functionssize; i++){
        if (((functions[i])[0] == '-') && ((functions[i]).find("--") == std::string::npos)){
            for (int j = 1; j < (functions[i]).size(); j++){
                newfunction = minus + ((functions[i])[j]);
                functions.push_back(newfunction);

            }
        }
    }

    //functions to functions_binary
    for (int j = 0; j < functions.size(); j++) {
        if (functions[j] == "-l" || functions[j] == "--lines") {
            functions_binary[0] += 1;
        }
        if (functions[j] == "-c" || functions[j] == "--bytes") {
            functions_binary[1] += 1;
        }
        if (functions[j] == "-w" || functions[j] == "--words") {
            functions_binary[2] += 1;
        }
        if (functions[j] == "-m" || functions[j] == "--chars") {
            functions_binary[3] += 1;
        }
    }

    //if no fuctions in cmd
    int sumfunctionsbinary = 0;
    for (char n: functions_binary){
        sumfunctionsbinary += n;
    }

    if (sumfunctionsbinary == 0){
        functions_binary = {1, 1, 1, 1};
    }

    //cout all picked functions for all  files
    for (int i = 0; i < filenames.size(); i++){
        std::ifstream currentfile;
        char currentchar;
        currentfile.open(filenames[i]);
        if (currentfile.is_open()) {
            int linecount = 0;
            if (functions_binary[0] > 0){
               while(currentfile.get(currentchar)){
                   if (currentchar == '\n'){
                       linecount++;
                   }
               }
               currentfile.clear();
               std::cout<<"Amount of lines of file " << filenames[i] << " : " << linecount + 1 << std::endl;
            }

            if (functions_binary[1] > 0) {
                size_t filesize = 0;
                currentfile.seekg(0, std::ios::end);
                filesize = currentfile.tellg();
                std::cout << "Size of file " << filenames[i] << " : " << filesize << " Bytes" << std::endl;
                currentfile.seekg(0);
            }


            if (functions_binary[2] > 0) {
                int wordcount = 0;
                bool flag = false;
                std::string currentline;
                while (currentfile >> currentline) {
                    currentline = ' ' + currentline + ' ';
                    for (int k = 0; k < currentline.length(); k++) {
                        if (isalpha(currentline[k]) || isalnum(currentline[k])) {
                            flag = true;
                        } else {
                            if (flag) {
                                wordcount++;
                            }
                            flag = false;
                        }
                    }
                }
                std::cout<<"Amount of words of file "<< filenames[i] << " : " << wordcount<<std::endl;
                currentfile.clear();
                currentfile.seekg(0);
            }

            if (functions_binary[3] > 0) {
                char symbol;
                int symbolcount = 0;
                while(currentfile.get(symbol)){
                    if (std::isalpha(symbol)){
                        symbolcount++;
                    }
                }
                std::cout<<"Amount of chars of file " << filenames[i] << " : " << symbolcount << std::endl;
            }
            std::cout<<std::endl;
            currentfile.close();
            }
        else{
            std::cout<<"Wrong file directory "<<filenames[i]<<std::endl;
        }
    }
    return 0;
    }
