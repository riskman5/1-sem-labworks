#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <tuple>
#include <algorithm>

namespace ArgumentParser {

    class General{
    private:
        std::tuple<char, std::string, std::string> full_short_name_desc = std::make_tuple(' ', " ", " ");
        bool positional = false;
        bool default_flag = false;
        int multivalue = 0;

    public:
        void set_names(char short_name, std::string long_name, std::string description = " ");
        void set_multivalue(int x);
        void set_positional();
        void set_default_flag();
        char get_short_name();
        std::string get_long_name();
        std::string get_descreption();
        int get_multivalue();
        bool get_positional();
        bool get_default_flag();
    };


    class IntArg: public General{
    private:
            int* store_value = nullptr;
            std::vector<int>* store_values = nullptr;
            int key = -2147483647;
            std::vector<int> key_vect;
    public:
        IntArg& MultiValue();
        IntArg& MultiValue(int x);
        IntArg& Positional();
        IntArg& StoreValue(int& x);
        IntArg& StoreValues(std::vector<int>& x);
        int get_key();
        int get_key_vect(int x);
        int get_size_key_vect();
        void set_key(int x);
        void set_key_vect(int x);
        std::string get_default();
    };


    class StringArg: public General{
    private:
        std::string* store_value = nullptr;
        std::vector<std::string>* store_values = nullptr;
        std::string key = " ";
        std::vector<std::string> key_vect;
    public:
        StringArg& MultiValue();
        StringArg& MultiValue(int x);
        StringArg& Positional();
        StringArg& StoreValue(std::string& x);
        StringArg& StoreValues(std::vector<std::string>& x);
        StringArg& Default(std::string def);
        std::string get_key();
        std::string get_key_vect(int x);
        int get_size_key_vect();
        void set_key(std::string x);
        void set_key_vect(std::string x);
        std::string get_default();
    };

    class FlagArg: public General{
    private:
        bool* store_value = nullptr;
        std::vector<bool>* store_values = nullptr;
        bool key = false;
        std::vector<bool> key_vect;

    public:
        FlagArg& MultiValue();
        FlagArg& MultiValue(int x);
        FlagArg& Positional();
        FlagArg& StoreValue(bool& x);
        FlagArg& StoreValues(std::vector<bool>& x);
        FlagArg& Default(bool fl);
        bool get_key();
        bool get_key_vect(int x);
        int get_size_key_vect();
        void set_key(bool x);
        void set_key_vect(bool x);
        std::string get_default();
    };


    class ArgParser {

    private:
        std::string name;
        std::vector<FlagArg*> bool_arguments;
        std::vector<IntArg*> int_arguments;
        std::vector<StringArg*> string_arguments;
        std::tuple<char, std::string, std::string> help_argument = std::make_tuple(' ', " ", " ");
        bool help;

    public:
        ArgParser (std::string name);

        bool Help();

        std::string HelpDescription();

        IntArg& AddIntArgument(char short_name = ' ');

        IntArg& AddIntArgument(std::string long_name = " ", std::string description = " ");

        IntArg& AddIntArgument(char short_name = ' ', std::string long_name = " ", std::string description = " ");

        StringArg& AddStringArgument(char short_name = ' ');

        StringArg& AddStringArgument(std::string long_name = " ",std::string description = " ");

        StringArg& AddStringArgument(char short_name = ' ', std::string long_name = " ", std::string description = " ");

        FlagArg& AddFlag(char short_name = ' ');

        FlagArg& AddFlag(std::string long_name = " ", std::string description = " ");

        FlagArg& AddFlag(char short_name = ' ', std::string long_name = " ", std::string description = " ");

        int GetIntValue(char short_name, int pos = -1);

        int GetIntValue (std::string long_name, int pos = -1);

        std::string GetStringValue(char short_name, int pos = -1);

        std::string GetStringValue(std::string long_name, int pos = -1);

        bool GetFlag(char short_name, int pos = -1);

        bool GetFlag(std::string long_name, int pos = -1);

        void AddHelp(char short_name, std::string long_name, std::string description);

        bool Parse(std::vector<std::string> params);

        IntArg* Find_in_int(std::string x);

        IntArg* Find_in_int(char x);

        StringArg* Find_in_string(std::string x);

        StringArg* Find_in_string(char x);

        FlagArg* Find_in_flags(std::string x);

        FlagArg* Find_in_flags(char x);

        void del_argument(std::string a);
    };

}