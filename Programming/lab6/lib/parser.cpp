#include "parser.h"
#include <iterator>
#include <iostream>
#include <fstream>


namespace omfl{
    Section* last_secton = nullptr;
    Node* last_node = nullptr;
    std::pair<std::string, int>* last_int_argument = nullptr;
    std::pair<std::string, float>* last_float_argument = nullptr;
    std::pair<std::string, std::string>* last_string_argument = nullptr;
    std::pair<std::string, bool>* last_bool_argument = nullptr;
    std::pair<std::string, List*>* last_list_argument = nullptr;
    bool valid_ = true;


    std::string clear_string(std::string temp_string){
        std::string string_to_return = "";
        bool flag_to_clear = false;
        int i = 0;
        while (i <= temp_string.size()) {
            if (!flag_to_clear) {
                if (temp_string[i] == '\n' || temp_string[i] == '\t' || temp_string[i] == '\000'){}
                else
                    string_to_return += temp_string[i];
                if (temp_string[i] == '"')
                    flag_to_clear = true;
                i++;
            }
            else{
                if (temp_string[i] == '"') {
                    string_to_return += temp_string[i];
                    flag_to_clear = false;
                }
                else {
                    string_to_return += temp_string[i];
                }
                i++;
            }
        }
        return string_to_return;
    }


    std::vector<std::string> SplitString(const std::string& str, char symbol) {
        std::vector<std::string> arguments;
        std::string temp_string;
        int i = 0;
        bool flag_to_comment = false;
        bool flag_to_string = false;
        int flag_to_list = 0;

        while (i != str.size()){
            if ((str[i] == ' ' || str[i] == symbol)  && !flag_to_comment && !flag_to_string && flag_to_list == 0){
                if (temp_string != "") {
                    temp_string = clear_string(temp_string);
                    arguments.push_back(temp_string);
                }
                temp_string = "";
            }

            else if(str[i] == '#'){
                flag_to_comment = true;
            }

            else if(flag_to_comment){
                temp_string+=str[i];
                if (temp_string.size()>=2 && temp_string.substr(temp_string.size()-2, 2) == "\\n"){
                    temp_string = " ";
                    flag_to_comment = false;
                }
            }

            else if(flag_to_string){
                if (str[i] == '"'){
                    temp_string+=str[i];
                    flag_to_string = false;
                    temp_string = clear_string(temp_string);
                    arguments.push_back(temp_string);
                    temp_string = "";
                }
                else
                    temp_string+=str[i];
            }

            else if(flag_to_list > 0){
                if (str[i] == '[')
                    flag_to_list++;
                if (str[i] == ']'){
                    temp_string+=str[i];
                    temp_string = clear_string(temp_string);
                    flag_to_list--;
                    if (flag_to_list == 0) {
                        arguments.push_back(temp_string);
                        temp_string = "";
                    }
                }
                else
                    temp_string+=str[i];
            }

            else if(str[i] == '"'){
                temp_string += str[i];
                flag_to_string = true;
            }

            else if(str[i] == '[' && !flag_to_comment && !flag_to_string) {
                temp_string+=str[i];
                flag_to_list++;
            }

            else
                temp_string+=str[i];

            i++;
        }

        if (temp_string != "" && !flag_to_comment) {
            temp_string = clear_string(temp_string);
            arguments.push_back(temp_string);
        }
        return arguments;
    }

    List *Parser::parse_list(std::vector<std::string> list_arguments){
        List* List_to_return = new List;

        for (int i = 0;  i < list_arguments.size(); i++) {
            if (double_comma_count(list_arguments[i]) == 2) {
                List::Node_for_list* new_node = new List::Node_for_list;
                new_node->data_str =  list_arguments[i].substr(list_arguments[i].find('"'), list_arguments[i].find('"') - list_arguments[i].rfind('"') + 1);
                List_to_return->push_back(new_node);
            }

            else if(list_arguments[i][0] == '[' && list_arguments[i][list_arguments[i].size()-1]){
                List::Node_for_list* new_node = new List::Node_for_list;
                std::vector<std::string> vector_of_list_arguments = SplitString(list_arguments[i].substr(1, list_arguments[i].size()-2), ',');
                new_node->data_list = parse_list(vector_of_list_arguments);
                List_to_return->push_back(new_node);
            }

            else if(list_arguments[i] == "true"){
                List::Node_for_list* new_node = new List::Node_for_list;
                new_node->data_bool = true;
                List_to_return->push_back(new_node);
            }

            else if(list_arguments[i].find('.') != std::string::npos){
                try{
                    List::Node_for_list* new_node = new List::Node_for_list;
                    if (std::stof(list_arguments[i])){}
                    new_node->data_float = atof((list_arguments[i]).c_str());
                    List_to_return->push_back(new_node);
                }
                catch (std::exception &ex){
                    valid_ = false;
                }
            }

            else{
                try{
                    List::Node_for_list* new_node = new List::Node_for_list;
                    if (std::stoi(list_arguments[i])){};
                    if (list_arguments[i].find(';') != std::string::npos)
                        valid_ = false;
                    new_node->data_int = atoi((list_arguments[i]).c_str());
                    List_to_return->push_back(new_node);
                }
                catch (std::exception &ex) {
                    valid_ = false;
                }
            }
        }

        return List_to_return;
    }



    Parser parse(const std::string &str) {
        auto current_parser = Parser();
        std::vector<std::string> to_parse = SplitString(clear_string(str));

        bool argument_now = false;
        Section* current_section = current_parser.get_root_of_sections();
        std::string current_key;
        bool now_equality = false;

        for (int i = 0; i < to_parse.size(); i++){
            if (now_equality){
                now_equality = false;
                argument_now = !argument_now;
                if (to_parse[i] != "=")
                    current_parser.set_valid(false);
                if (i == to_parse.size()-1)
                    current_parser.set_valid(false);

            }

            else if (!argument_now){
                if (to_parse[i][0] == '[' && to_parse[i][to_parse[i].size()-1] == ']'){//income section
                    if ((to_parse[i][0] == '[' && to_parse[i][1] == ']') || (to_parse[i].find('.') == 1) || (to_parse[i].rfind('.') == to_parse[i].size()-2))
                        current_parser.set_valid(false);
                    current_section = current_parser.get_root_of_sections();
                    std::vector<std::string> sections = SplitString(to_parse[i].substr(1, to_parse[i].size()-2), '.');

                    for (int j = 0; j < sections.size(); j++){
                        if (current_section->width_find(current_section->under_section, sections[j])  == nullptr){
                            if (current_section->under_section == nullptr) {
                                current_section->under_section = new Section(sections[j]);
                                current_section = current_section->under_section;
                            }
                            else{
                                current_section = current_section->under_section;
                                while(current_section->next != nullptr){
                                    current_section = current_section->next;
                                }
                                current_section->next = new Section(sections[j]);
                                current_section = current_section -> next;
                            }
                        }
                        else{
                            current_section = current_section->width_find(current_section->under_section, sections[j]);
                        }
                    }


                }

                else{ //income key name;
                    current_key = to_parse[i];
                    if (!is_valid_key(current_key)){
                        current_parser.set_valid(false);
                        return current_parser;
                    }
                    now_equality = true;
                }
            }

            else{
                to_parse[i] = clear_string(to_parse[i]);

                bool flag_something_worked = false;
                if (double_comma_count(to_parse[i]) == 2){
                    for (int j = 0; j < current_section->arguments->string_arguments.size(); j++){
                        if (current_key == current_section->arguments->string_arguments[j].first)
                            current_parser.set_valid(false);
                    }
                    std::pair<std::string, std::string> str_argument_to_push = {current_key, to_parse[i].substr(to_parse[i].find('"'), to_parse[i].rfind('"') - to_parse[i].find('"') + 1)};
                    current_section->arguments->string_arguments.push_back(str_argument_to_push);
                    flag_something_worked = true;
                }

                else if(to_parse[i] == "true"){
                    for (int j = 0; j < current_section->arguments->bool_arguments.size(); j++){
                        if (current_key == current_section->arguments->bool_arguments[j].first)
                            current_parser.set_valid(false);
                    }
                    std::pair<std::string, bool> bool_argument_to_push = {current_key, true};
                    current_section->arguments->bool_arguments.push_back(bool_argument_to_push);
                    flag_something_worked = true;
                }

                else if(to_parse[i] == "false"){
                    for (int j = 0; j < current_section->arguments->bool_arguments.size(); j++){
                        if (current_key == current_section->arguments->bool_arguments[j].first)
                            current_parser.set_valid(false);
                    }
                    std::pair<std::string, bool> bool_argument_to_push = {current_key, false};
                    current_section->arguments->bool_arguments.push_back(bool_argument_to_push);
                    flag_something_worked = true;
                }

                else if(to_parse[i][0] == '[' && to_parse[i][to_parse[i].size()-1] == ']'){
                    for (int j = 0; j < current_section->arguments->list_arguments.size(); j++){
                        if (current_key == current_section->arguments->list_arguments[j].first)
                            current_parser.set_valid(false);
                    }
                    int count_1 = 0;
                    int count_2 = 0;
                    for (int j = 0; j < to_parse[i].size(); j++){
                        if (to_parse[i][j] == '[')
                            count_1++;
                        else if (to_parse[i][j] == ']')
                            count_2++;
                    }
                    if (count_1 != count_2)
                        current_parser.set_valid(false);
                    std::vector<std::string> vector_of_list_arguments = SplitString(to_parse[i].substr(1, to_parse[i].size()-2), ',');
                    std::pair<std::string, List*> list_argument_to_push = {current_key, current_parser.parse_list(vector_of_list_arguments)};
                    current_section->arguments->list_arguments.push_back(list_argument_to_push);
                    if (!valid_)
                        current_parser.set_valid(false);
                    flag_something_worked = true;
                }

                else if(to_parse[i].find('.') != std::string::npos){
                    try{
                        for (int j = 0; j < current_section->arguments->float_arguments.size(); j++){
                            if (current_key == current_section->arguments->float_arguments[j].first)
                                current_parser.set_valid(false);
                        }
                        if (std::stof(to_parse[i])){}
                        char temp = to_parse[i][to_parse[i].size()-1];
                        if (!((int) temp >= 48 && (int) temp <= 57) || to_parse[i][0] == '.' || to_parse[i].find("+.") != std::string::npos || to_parse[i].find("-.") != std::string::npos || !verify_int_and_float(to_parse[i]))
                            current_parser.set_valid(false);
                        std::pair<std::string, float> float_argument_to_push =  {current_key, std::atof((to_parse[i]).c_str())};
                        current_section->arguments->float_arguments.push_back(float_argument_to_push);
                        flag_something_worked = true;
                    }
                    catch (const std::exception &ex){
                        current_parser.set_valid(false);
                    }
                }

                else{
                    try{
                        for (int j = 0; j < current_section->arguments->int_arguments.size(); j++){
                            if (current_key == current_section->arguments->int_arguments[j].first)
                                current_parser.set_valid(false);
                        }
                        char temp = to_parse[i][to_parse[i].size()-1];
                        if (std::stoi(to_parse[i])){}
                        if (!((int) temp >= 48 && (int) temp <= 57) || !verify_int_and_float(to_parse[i]))
                            current_parser.set_valid(false);
                        std::pair<std::string, int> int_argument_to_push = {current_key, std::atoi((to_parse[i]).c_str())};
                        current_section->arguments->int_arguments.push_back(int_argument_to_push);
                        flag_something_worked = true;
                    }
                    catch (const std::exception &ex){
                        current_parser.set_valid(false);
                    }
                }
                if (!flag_something_worked)
                    current_parser.set_valid(false);
                argument_now = !argument_now;
            }
        }
        return current_parser;
    }



    Section *Parser::get_root_of_sections() {
        return root_of_sections;
    }

    void Parser::set_valid(bool flag) {
        this->Valid = flag;
    }

    bool Parser::valid() const {
        return Valid;
    }

    Parser Parser::Get(std::string get_string) const {
        if (last_secton == nullptr)
            last_secton = root_of_sections;
        std::vector<std::string> path = SplitString(get_string, '.');
        for (int i = 0;  i < path.size(); i++){
            Section* temp_section = last_secton->under_section;
            while (temp_section != nullptr){
                if (temp_section->name == path[i]){
                    last_secton = temp_section;
                    break;
                }
                temp_section = temp_section->next;
            }

            temp_section = last_secton;

            while (temp_section != nullptr){
                if (temp_section->name == path[i]){
                    last_secton = temp_section;
                    break;
                }
                temp_section = temp_section->next;
            }

            Node* last_node = last_secton->arguments;


            for (int j = 0; j < last_node->int_arguments.size(); j++){
                if (last_node->int_arguments[j].first == path[i])
                    last_int_argument = &(last_node->int_arguments[j]);
            }

            for (int j = 0; j < last_node->float_arguments.size(); j++){
                if (last_node->float_arguments[j].first == path[i])
                    last_float_argument = &(last_node->float_arguments[j]);
            }

            for (int j = 0; j < last_node->bool_arguments.size(); j++){
                if (last_node->bool_arguments[j].first == path[i])
                    last_bool_argument = &(last_node->bool_arguments[j]);
            }

            for (int j = 0; j < last_node->string_arguments.size(); j++){
                if (last_node->string_arguments[j].first == path[i])
                    last_string_argument = &(last_node->string_arguments[j]);
            }

            for (int j = 0; j < last_node->list_arguments.size(); j++){
                if (last_node->list_arguments[j].first == path[i])
                    last_list_argument = &(last_node->list_arguments[j]);
            }

        }

        return *this;
    }

    bool Parser::IsInt() {
        if (last_int_argument != nullptr) {
            clear_pointers();
            return true;
        }
        else {
            clear_pointers();
            return false;
        }
    }

    bool Parser::IsFloat() {
        if (last_float_argument != nullptr) {
            clear_pointers();
            return true;
        }
        else {
            clear_pointers();
            return false;
        }
    }

    bool Parser::IsString() {
        if (last_string_argument != nullptr) {
            clear_pointers();
            return true;
        }
        else {
            clear_pointers();
            return false;
        }
    }

    bool Parser::IsArray() {
        if (last_list_argument != nullptr) {
            clear_pointers();
            return true;
        }
        else {
            clear_pointers();
            return false;
        }
    }

    bool Parser::IsBool() {
        if(last_bool_argument != nullptr){
            clear_pointers();
            return true;
        }
        else{
            clear_pointers();
            return false;
        }
    }

    int Parser::AsInt() {
        int int_to_return = last_int_argument->second;
        clear_pointers();
        return int_to_return;
    }

    int Parser::AsIntOrDefault(int def) {
        if (last_int_argument != nullptr){
            int int_to_return = last_int_argument->second;
            clear_pointers();
            return int_to_return;
        }
        clear_pointers();
        return def;
    }

    float Parser::AsFloat() {
        float float_to_return = last_float_argument->second;
        clear_pointers();
        return float_to_return;
    }

    float Parser::AsFloatOrDefault(float def) {
        if (last_float_argument != nullptr){
            float float_to_return = last_float_argument->second;
            clear_pointers();
            return float_to_return;
        }
        clear_pointers();
        return def;
    }

    std::string Parser::AsString() {
        std::string string_to_return = (last_string_argument->second).substr((last_string_argument->second).find('"') + 1, (last_string_argument->second).rfind('"') - (last_string_argument->second).find('"') - 1);
        clear_pointers();
        return string_to_return;
    }

    std::string Parser::AsStringOrDefault(std::string def) {
        if (last_string_argument != nullptr){
            std::string string_to_return = last_string_argument->second;
            clear_pointers();
            return string_to_return;
        }
        clear_pointers();
        return def;
    }

    bool Parser::AsBool() {
        bool bool_to_return = last_bool_argument->second;
        clear_pointers();
        return bool_to_return;
    }

    bool Parser::AsBoolOrDefault(bool def) {
        if (last_bool_argument != nullptr){
            bool bool_to_return = last_bool_argument->second;
            clear_pointers();
            return bool_to_return;
        }
        clear_pointers();
        return def;
    }

    Parser Parser::operator[](int number) {
        last_list_argument->second->search(number);
        return *this;
    }

    void Parser::exp_tree(std::string path) const {
        std::ofstream outfile(path);
        Section* current_section = root_of_sections;
        push_all_from_section(current_section, outfile, -1);
        outfile.close();
    }

    void Parser::push_all_from_section(Section* current_section, std::ofstream& file, int tabs_count) const {
        Node* current_node = current_section->arguments;
        std::vector <std::string> section_level = SplitString(current_section->name, '.');
        if (current_section->name != "general") {
            for (int i = 0; i < tabs_count; i++)
                file << '\t';
            file << "[" << current_section->name << "]" << '\n';
        }
        for (int i = 0; i < current_node -> int_arguments.size(); i++){
            for (int j = 0; j < tabs_count; j++)
                file << '\t';
            file << '\t' << current_node -> int_arguments[i].first << " = " << current_node -> int_arguments[i].second << '\n';
        }

        for (int i = 0; i < current_node->float_arguments.size(); i++){
            for (int j = 0; j < tabs_count; j++)
                file << '\t';
            file << '\t' << current_node -> float_arguments[i].first << " = " << current_node -> float_arguments[i].second << '\n';
        }

        for (int i = 0; i < current_node->string_arguments.size(); i++){
            for (int j = 0; j < tabs_count; j++)
                file << '\t';
            file << '\t' << current_node -> string_arguments[i].first << " = " << current_node -> string_arguments[i].second << '\n';
        }

        for (int i = 0; i < current_node->bool_arguments.size(); i++){
            for (int j = 0; j < tabs_count; j++)
                file << '\t';
            file << '\t' << current_node -> bool_arguments[i].first << " = " << current_node -> bool_arguments[i].second << '\n';
        }

        if (current_section -> under_section != nullptr)
            push_all_from_section(current_section->under_section, file, 1+tabs_count);

        if (current_section -> next != nullptr)
            push_all_from_section(current_section->next, file, tabs_count);

    }


    bool is_valid_key(std::string str_to_verify){
        for (int i = 0; i < str_to_verify.size(); i++){
            if (!(((int)str_to_verify[i] >= 65 && (int)str_to_verify[i] <= 90) || isalnum(str_to_verify[i]) || str_to_verify[i] == '-' || str_to_verify[i] == '_'))
                return false;
        }
        return true;
    }

    int double_comma_count(std::string temp_string){
        int double_comma_counter = 0;
        for (int i = 0; i < temp_string.size(); i++){
            if (temp_string[i] == '"')
                double_comma_counter++;
        }
        return double_comma_counter;
    }


    void clear_pointers(){
        last_secton = nullptr;
        last_node = nullptr;
        last_int_argument = nullptr;
        last_float_argument = nullptr;
        last_string_argument = nullptr;
        last_bool_argument = nullptr;
        last_list_argument = nullptr;
    };

    void List::search(int x) {
        int count = 0;
        Node_for_list* temp_node = root;
        while (count != x){
            temp_node = temp_node->next_node_for_list;
            if (temp_node == nullptr)
                break;
            count++;
        }

        std::string trash = "trash";

        if (temp_node != nullptr) {
            if (temp_node->data_int != INT_MIN) {
                std::pair<std::string, int> *to_save = new std::pair{trash, temp_node->data_int};
                last_int_argument = to_save;
            } else if (temp_node->data_float != -10000001) {
                std::pair<std::string, float> *to_save = new std::pair{trash, temp_node->data_float};
                last_float_argument = to_save;
            } else if (temp_node->data_str != "") {
                std::pair<std::string, std::string> *to_save = new std::pair{trash, temp_node->data_str};
                last_string_argument = to_save;
            } else if (temp_node->data_list != nullptr) {
                std::pair<std::string, List *> *to_save = new std::pair{trash, temp_node->data_list};
                last_list_argument = to_save;
            } else if (temp_node->data_bool){
                std::pair<std::string, bool> *to_save = new std::pair{trash, temp_node->data_bool};
                last_bool_argument = to_save;
            }
        }
    }
    bool verify_int_and_float(std::string temp_string){
        for (int i = 1; i < temp_string.size(); i++){
            if (temp_string[i] == '+' || temp_string[i] == '-')
                return false;
        }
        return true;
    }
}

