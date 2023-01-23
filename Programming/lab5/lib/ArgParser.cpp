#include "ArgParser.h"

namespace ArgumentParser{
    // ArgParser methods
    ArgParser::ArgParser(std::string name) {
        this->name = name;
    }

    bool ArgParser::Help() {
        HelpDescription();
        return help;
    }

    std::string ArgParser::HelpDescription() {
        std::string string_to_return;
        string_to_return += name + '\n';
        string_to_return += std::get<2>(help_argument) + '\n';
        string_to_return += '\n';


        for (int i = 0; i < string_arguments.size(); i++){
            if (string_arguments[i]->get_short_name() != ' ') {
                string_to_return += "-";
                string_to_return += string_arguments[i]->get_short_name();
                string_to_return += ", ";
            }
            else
                string_to_return += "    ";
            if (string_arguments[i]->get_long_name() != " ")
                string_to_return += "--" + string_arguments[i]->get_long_name() + "=<string>" + ", ";
            if (string_arguments[i]->get_descreption() != " ")
                string_to_return += string_arguments[i]->get_descreption();
            if (string_arguments[i]->get_multivalue() != 0){
                string_to_return += " [repeated, min args = " + std::to_string(string_arguments[i]->get_multivalue()) + "]";
            }
            if (string_arguments[i]->get_default_flag()){
                string_to_return += " [default =" + string_arguments[i]->get_default() + "]";
            }
            string_to_return += '\n';
        }

        for (int i = 0; i < bool_arguments.size(); i++){
            if (bool_arguments[i]->get_short_name() != ' ') {
                string_to_return += "-";
                string_to_return += bool_arguments[i]->get_short_name();
                string_to_return += ", ";
            }
            else
                string_to_return += "    ";
            if (bool_arguments[i]->get_long_name() != " ")
                string_to_return += "--" + bool_arguments[i]->get_long_name() + "=<bool>" + ", ";
            if (bool_arguments[i]->get_descreption() != " ")
                string_to_return += bool_arguments[i]->get_descreption();
            if (bool_arguments[i]->get_multivalue() != 0){
                string_to_return += " [repeated, min args = " + std::to_string(bool_arguments[i]->get_multivalue()) + "]";
            }
            if (bool_arguments[i]->get_default_flag()){
                string_to_return += " [default =" + bool_arguments[i]->get_default() + "]";
            }
            string_to_return += '\n';
        }

        for (int i = 0; i < int_arguments.size(); i++){
            if (int_arguments[i]->get_short_name() != ' ') {
                string_to_return += "-";
                string_to_return += int_arguments[i]->get_short_name();
                string_to_return += ", ";
            }
            else
                string_to_return += "    ";
            if (int_arguments[i]->get_long_name() != " ")
                string_to_return += "--" + int_arguments[i]->get_long_name() + "=<int>" + ", ";
            if (int_arguments[i]->get_descreption() != " ")
                string_to_return += int_arguments[i]->get_descreption();
            if (int_arguments[i]->get_multivalue() != 0){
                string_to_return += " [repeated, min args = " + std::to_string(int_arguments[i]->get_multivalue()) + "]";
            }
            if (int_arguments[i]->get_default_flag()){
                string_to_return += " [default =" + int_arguments[i]->get_default() + "]";
            }
            string_to_return += '\n';
        }

        string_to_return += '\n';

        if (std::get<0>(help_argument) != ' ') {
            string_to_return += '-';
            string_to_return += std::get<0>(help_argument);
            string_to_return += ", ";
        }
        else
            string_to_return += "   ";

        if (std::get<1>(help_argument) != " "){
            string_to_return += std::get<1>(help_argument) + " Display this help and exit\n";
        }
        return string_to_return;
    }

    IntArg& ArgParser::AddIntArgument(char short_name) {
        std::string long_name = " ";
        std::string description = " ";
        IntArg* temp_name = new IntArg;
        temp_name->set_names(short_name, long_name, description);
        int_arguments.push_back(temp_name);
        return *temp_name;
    }

    IntArg& ArgParser::AddIntArgument(std::string long_name, std::string description) {
        char short_name = ' ';
        IntArg* temp_name = new IntArg;
        temp_name->set_names(short_name, long_name, description);
        int_arguments.push_back(temp_name);
        return *temp_name;
    }

    IntArg& ArgParser::AddIntArgument(char short_name, std::string long_name, std::string description) {
        IntArg* temp_name = new IntArg;
        temp_name->set_names(short_name, long_name, description);
        int_arguments.push_back(temp_name);
        return *temp_name;
    }

    StringArg &ArgParser::AddStringArgument(char short_name) {
        std::string long_name = " ";
        std::string description = " ";
        StringArg* temp_name = new StringArg;
        temp_name->set_names(short_name, long_name, description);
        string_arguments.push_back(temp_name);
        return *temp_name;
    }

    StringArg &ArgParser::AddStringArgument(std::string long_name, std::string description) {
        char short_name = ' ';
        StringArg* temp_name = new StringArg;
        temp_name->set_names(short_name, long_name, description);
        string_arguments.push_back(temp_name);
        return *temp_name;
    }

    StringArg &ArgParser::AddStringArgument(char short_name, std::string long_name, std::string discreption) {
        StringArg* temp_name = new StringArg;
        temp_name->set_names(short_name, long_name, discreption);
        string_arguments.push_back(temp_name);
        return *temp_name;
    }

    FlagArg &ArgParser::AddFlag(char short_name) {
        std::string long_name = " ";
        std::string description = " ";
        FlagArg* temp_name = new FlagArg;
        temp_name->set_names(short_name, long_name, description);
        bool_arguments.push_back(temp_name);
        return *temp_name;
    }

    FlagArg &ArgParser::AddFlag(std::string long_name, std::string description) {
        char shor_name = ' ';
        FlagArg* temp_name = new FlagArg;
        temp_name->set_names(shor_name,long_name,description);
        bool_arguments.push_back(temp_name);
        return *temp_name;
    }

    FlagArg &ArgParser::AddFlag(char short_name, std::string long_name, std::string description) {
        FlagArg* temp_name = new FlagArg;
        temp_name->set_names(short_name,long_name,description);
        bool_arguments.push_back(temp_name);
        return *temp_name;
    }

    int ArgParser::GetIntValue(char short_name, int pos) {
        for(int i = 0; i < int_arguments.size(); i++){
            if (int_arguments[i]->get_short_name() == short_name){
                if (pos == -1)
                    return int_arguments[i]->get_key();
                return int_arguments[i]->get_key_vect(pos);
            }
        }
        return -1;
    }

    int ArgParser::GetIntValue(std::string long_name, int pos) {
        for(int i = 0; i < int_arguments.size(); i++){
            if (int_arguments[i]->get_long_name() == long_name){
                if (pos == -1)
                    return int_arguments[i]->get_key();
                return int_arguments[i]->get_key_vect(pos);
            }
        }
        return -1;
    }

    std::string ArgParser::GetStringValue(char short_name, int pos) {
        for(int i = 0; i < string_arguments.size(); i++){
            if (string_arguments[i]->get_short_name() == short_name){
                if (pos == -1)
                    return string_arguments[i]->get_key();
                return string_arguments[i]->get_key_vect(pos);
            }
        }
        return " ";
    }

    std::string ArgParser::GetStringValue(std::string long_name, int pos) {
        for(int i = 0; i < string_arguments.size(); i++){
            if (string_arguments[i]->get_long_name() == long_name){
                if (pos == -1)
                    return string_arguments[i]->get_key();
                return string_arguments[i]->get_key_vect(pos);
            }
        }
        return " ";
    }

    bool ArgParser::GetFlag(char short_name, int pos) {
        for(int i = 0; i < bool_arguments.size(); i++){
            if (bool_arguments[i]->get_short_name() == short_name){
                if (pos == -1)
                    return bool_arguments[i]->get_key();
                return bool_arguments[i]->get_key_vect(pos);
            }
        }
        return false;
    }

    bool ArgParser::GetFlag(std::string long_name, int pos) {
        for(int i = 0; i < bool_arguments.size(); i++){
            if (bool_arguments[i]->get_long_name() == long_name){
                if (pos == -1)
                    return bool_arguments[i]->get_key();
                return bool_arguments[i]->get_key_vect(pos);
            }
        }
        return false;
    }

    void ArgParser::AddHelp(char short_name, std::string long_name, std::string description) {
        help_argument = std::make_tuple(short_name, long_name, description);
        help = true;
    }

    bool ArgParser::Parse(std::vector<std::string> params) {
        IntArg* int_arg_ptr = nullptr;
        StringArg* string_arg_ptr = nullptr;
        FlagArg* flag_arg_ptr = nullptr;
        char temp_char;

        for (int i = 1; i < params.size(); i++){
            if (params[i].find("--") != std::string::npos){
                int_arg_ptr = nullptr;
                string_arg_ptr = nullptr;
                flag_arg_ptr = nullptr;
                if (params[i].find("=") != std::string::npos){
                    int_arg_ptr = Find_in_int(params[i].substr(params[i].rfind('-') + 1, params[i].size() - (params[i].size() - params[i].find('=')) - (params[i].rfind('-') + 1)));
                    string_arg_ptr = Find_in_string(params[i].substr(params[i].rfind('-') + 1, params[i].size() - (params[i].size() - params[i].find('=')) - (params[i].rfind('-') + 1)));
                    if (int_arg_ptr != nullptr) {
                        try {
                            int_arg_ptr->set_key(std::stoi(params[i].substr(params[i].find("=") + 1, params.size() -(params[i].find("=") +1))));
                            int_arg_ptr->set_key_vect(std::stoi(params[i].substr(params[i].find("=") + 1, params.size() - (params[i].find("=") + 1))));
                        }
                        catch (const std::exception &ex){};
                    }
                    if (string_arg_ptr != nullptr){
                        string_arg_ptr->set_key(params[i].substr(params[i].find("=") + 1, params.size() - (params[i].find("=") + 1)));
                        string_arg_ptr->set_key_vect(params[i].substr(params[i].find("=") + 1, params.size() - (params[i].find("=") + 1)));
                    }
                }
                else{
                    if (params[i] == ("--" + std::get<1>(help_argument))) {
                        help = true;
                        return true;
                    }
                    int_arg_ptr = Find_in_int(params[i].substr(params[i].rfind("-") + 1));
                    string_arg_ptr = Find_in_string(params[i].substr(params[i].rfind("-") + 1));
                    flag_arg_ptr = Find_in_flags(params[i].substr(params[i].rfind("-") + 1));
                    if (flag_arg_ptr != nullptr) {
                        flag_arg_ptr->set_key(true);
                        flag_arg_ptr->set_key_vect(true);
                    }
                }
            }

            else if (params[i].find("-") != std::string::npos && params[i].find("--") == std::string::npos){
                if (params[i].find("=") == std::string::npos) {
                    if (params[i][1] == std::get<0>(help_argument)) {
                        help = true;
                        return true;
                    }
                    params[i] = params[i].substr(1);
                    for (int j = 0; j < params[i].size(); j++) {
                        int_arg_ptr = Find_in_int((char) params[i][j]);
                        string_arg_ptr = Find_in_string((char) params[i][j]);
                        flag_arg_ptr = Find_in_flags((char) params[i][j]);
                        if (flag_arg_ptr != nullptr) {
                            flag_arg_ptr->set_key(true);
                            flag_arg_ptr->set_key_vect(true);
                        }
                    }
                }
                else{
                    if (params[i].find("=") != std::string::npos){
                        int_arg_ptr = Find_in_int((char) (params[i].substr(params[i].rfind('-') + 1, params[i].size() - (params[i].size() - params[i].find('=')) - (params[i].rfind('-') + 1)))[0]);
                        string_arg_ptr = Find_in_string((char) (params[i].substr(params[i].rfind('-') + 1, params[i].size() - (params[i].size() - params[i].find('=')) - (params[i].rfind('-') + 1)))[0]);
                        if (int_arg_ptr != nullptr){
                            try{
                                int_arg_ptr->set_key(std::stoi(params[i].substr(params[i].find("=") + 1, params.size() - (params[i].find("=") + 1))));
                                int_arg_ptr->set_key_vect(std::stoi(params[i].substr(params[i].find("=") + 1, params.size() - (params[i].find("=") + 1))));
                            }
                            catch (const std::exception &ex){};
                        }
                        if (string_arg_ptr != nullptr){
                            string_arg_ptr->set_key(params[i].substr(params[i].find("=") + 1, params.size() - (params[i].find("=") + 1)));
                            string_arg_ptr->set_key_vect(params[i].substr(params[i].find("=") + 1, params.size() - (params[i].find("=") + 1)));
                        }
                    }
                }
            }

            else{
                if (int_arg_ptr != nullptr){
                    try{
                        int_arg_ptr->set_key(std::stoi(params[i]));
                        int_arg_ptr->set_key_vect(std::stoi(params[i]));
                    }
                    catch (const std::exception &ex){};
                }
                if (string_arg_ptr != nullptr){
                    string_arg_ptr->set_key(params[i]);
                    string_arg_ptr->set_key_vect(params[i]);
                }
                if (params[i].size() == 1)
                    flag_arg_ptr = Find_in_flags((char)params[i][0]);
                else
                    flag_arg_ptr = Find_in_flags(params[i]);
                if (flag_arg_ptr != nullptr){
                    flag_arg_ptr->set_key(true);
                    flag_arg_ptr->set_key_vect(true);
                }
                if (int_arg_ptr == nullptr && string_arg_ptr == nullptr && flag_arg_ptr == nullptr){
                    for (int j = 0; j < int_arguments.size(); j++){
                        if (int_arguments[j]->get_positional()){
                            try{
                                int_arguments[j]->set_key(std::stoi(params[i]));
                                int_arguments[j]->set_key_vect(std::stoi(params[i]));
                            }
                            catch (const std::exception &ex){};
                        }
                    }

                    for (int j = 0; j < string_arguments.size(); j++){
                        if (string_arguments[j]->get_positional()){
                            string_arguments[j]->set_key(params[i]);
                            string_arguments[j]->set_key_vect(params[i]);
                        }
                    }
                }
            }
        }

        for (int i = 0; i < int_arguments.size(); i++) {
            if (int_arguments[i]->get_size_key_vect() < int_arguments[i]->get_multivalue())
                return false;
            if (int_arguments[i]->get_key() == -2147483647)
                return false;
        }

        for (int i = 0; i < string_arguments.size(); i++) {
            if (string_arguments[i]->get_size_key_vect() < string_arguments[i]->get_multivalue())
                return false;
            if (string_arguments[i]->get_key() == " ")
                return false;
        }

        for (int i = 0; i < bool_arguments.size(); i++) {
            if (bool_arguments[i]->get_size_key_vect() < bool_arguments[i]->get_multivalue())
                return false;
            if (!bool_arguments[i]->get_key())
                return false;
        }


        return true;
    }

    IntArg *ArgParser::Find_in_int(std::string x) {
        IntArg* int_arg_ptr = nullptr;
        for (int i = 0; i < int_arguments.size(); i++){
            if (int_arguments[i]->get_long_name() == x){
                int_arg_ptr = int_arguments[i];
                break;
            }
        }
        return int_arg_ptr;
    }

    IntArg *ArgParser::Find_in_int(char x) {
        IntArg* int_arg_ptr = nullptr;
        for (int i = 0; i < int_arguments.size(); i++){
            if (int_arguments[i]->get_short_name() == x){
                int_arg_ptr = int_arguments[i];
                break;
            }
        }
        return int_arg_ptr;
    }

    StringArg *ArgParser::Find_in_string(std::string x) {
        StringArg* string_arg_ptr = nullptr;
        for (int i = 0; i < string_arguments.size(); i++){
            if (string_arguments[i]->get_long_name() == x){
                string_arg_ptr = string_arguments[i];
                break;
            }
        }
        return string_arg_ptr;
    }

    StringArg *ArgParser::Find_in_string(char x) {
        StringArg* string_arg_ptr = nullptr;
        for (int i = 0; i < string_arguments.size(); i++){
            if (string_arguments[i]->get_short_name() == x){
                string_arg_ptr = string_arguments[i];
                break;
            }
        }
        return string_arg_ptr;
    }

    FlagArg *ArgParser::Find_in_flags(std::string x) {
        FlagArg* string_arg_ptr = nullptr;
        for (int i = 0; i < bool_arguments.size(); i++){
            if (bool_arguments[i]->get_long_name() == x){
                string_arg_ptr = bool_arguments[i];
                break;
            }
        }
        return string_arg_ptr;
    }

    FlagArg *ArgParser::Find_in_flags(char x) {
        FlagArg* string_arg_ptr = nullptr;
        for (int i = 0; i < bool_arguments.size(); i++){
            if (bool_arguments[i]->get_short_name() == x){
                string_arg_ptr = bool_arguments[i];
                break;
            }
        }
        return string_arg_ptr;
    }

    void ArgParser::del_argument(std::string a) {
        for (int i = 0; i < int_arguments.size(); i++){
            if (int_arguments[i]->get_long_name() == a){
                int_arguments.erase(int_arguments.begin() + i);
            }
        }

        for (int i = 0; i < bool_arguments.size(); i++){
            if (bool_arguments[i]->get_long_name() == a){
                bool_arguments.erase(bool_arguments.begin() + i);
            }
        }

    }


    //General methods
    void General::set_names(char short_name, std::string long_name, std::string descripton){
        full_short_name_desc = std::make_tuple(short_name, long_name, descripton);
    }

    void General::set_multivalue(int x) {
        this->multivalue = x;
    }

    void General::set_positional() {
        this->positional = true;
    }

    char General::get_short_name() {
        return std::get<0>(full_short_name_desc);
    }

    std::string General::get_long_name() {
        return std::get<1>(full_short_name_desc);
    }

    std::string General::get_descreption() {
        return std::get<2>(full_short_name_desc);
    }

    int General::get_multivalue() {
        return multivalue;
    }

    bool General::get_positional() {
        return positional;
    }

    void General::set_default_flag() {
        default_flag = true;
    }

    bool General::get_default_flag() {
        return default_flag;
    }


    //IntArg methods
    IntArg &IntArg::MultiValue() {
        return *this;
    }

    IntArg &IntArg::MultiValue(int x) {
        set_multivalue(x);
        return *this;
    }

    IntArg &IntArg::Positional() {
        set_positional();
        return *this;
    }

    IntArg &IntArg::StoreValue(int& x) {
        store_value = &x;
        return *this;
    }

    IntArg &IntArg::StoreValues(std::vector<int>& x) {
        store_values = &x;
        return *this;
    }

    int IntArg::get_key() {
        return key;
    }

    int IntArg::get_key_vect(int x) {
        return key_vect[x];
    }



    void IntArg::set_key(int x) {
        key = x;
        if (store_value != nullptr){
            *store_value = x;
        }
    }

    void IntArg::set_key_vect(int x) {
        key_vect.push_back(x);
        if (store_values != nullptr){
            *store_values = key_vect;
        }
    }

    int IntArg::get_size_key_vect() {
        return key_vect.size();
    }

    std::string IntArg::get_default() {
        return std::to_string(key);
    }


    //StringArg methods
    StringArg &StringArg::MultiValue() {
        return *this;
    }

    StringArg &StringArg::MultiValue(int x) {
        set_multivalue(x);
        return *this;
    }

    StringArg &StringArg::Positional() {
        set_positional();
        return *this;
    }

    StringArg &StringArg::StoreValue(std::string& x) {
        store_value = &x;
        return *this;
    }

    StringArg &StringArg::StoreValues(std::vector<std::string>& x) {
        store_values = &x;
        return *this;
    }

    StringArg &StringArg::Default(std::string def) {
        set_default_flag();
        key = def;
        if (store_value != nullptr)
            *store_value = def;
        return *this;
    }

    std::string StringArg::get_key() {
        return key;
    }

    std::string StringArg::get_key_vect(int x) {
        return key_vect[x];
    }



    void StringArg::set_key(std::string x) {
        key = x;
        if (store_value != nullptr)
            *store_value = x;
    }

    void StringArg::set_key_vect(std::string x) {
        key_vect.push_back(x);
        if (store_values != nullptr)
            *store_values = key_vect;
    }

    int StringArg::get_size_key_vect() {
        return key_vect.size();
    }

    std::string StringArg::get_default() {
        return key;
    }


    //FlagArg methods
    FlagArg &FlagArg::MultiValue() {
        return *this;
    }

    FlagArg &FlagArg::MultiValue(int x) {
        set_multivalue(x);
        return *this;
    }

    FlagArg &FlagArg::Positional() {
        set_positional();
        return *this;
    }

    FlagArg &FlagArg::StoreValue(bool& x){
        store_value = &x;
        return *this;
    }

    FlagArg &FlagArg::StoreValues(std::vector<bool>& x) {
        store_values = &x;
        return *this;
    }

    FlagArg &FlagArg::Default(bool fl) {
        set_default_flag();
        key = fl;
        if (store_value != nullptr)
            *store_value = fl;
        return *this;
    }

    bool FlagArg::get_key() {
        return key;
    }

    bool FlagArg::get_key_vect(int x) {
        return key_vect[x];
    }



    void FlagArg::set_key(bool x) {
        key = x;
        if (store_value != nullptr)
            *store_value = x;
    }

    void FlagArg::set_key_vect(bool x) {
        key_vect.push_back(x);
        if (store_values != nullptr)
            *store_values = key_vect;
    }

    int FlagArg::get_size_key_vect() {
        return key_vect.size();
    }

    std::string FlagArg::get_default() {
        return "True";
    }


}
