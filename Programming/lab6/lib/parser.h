#pragma once

#include <filesystem>
#include <istream>


namespace omfl {
    std::string clear_string(std::string temp_string);

    std::vector<std::string> SplitString(const std::string& str = "", char sybmbol = ' ');



    struct List{
        struct Node_for_list{
            int data_int = INT_MIN;
            float data_float = -10000001;
            std::string data_str = "";
            List* data_list = nullptr;
            bool data_bool = false;

            Node_for_list* next_node_for_list = nullptr;
        };

        Node_for_list* root = nullptr;
        void push_back(Node_for_list* node_to_push){
            if (root == nullptr)
                root = node_to_push;
            else{
                Node_for_list* temp_node = root;
                while(temp_node->next_node_for_list != nullptr)
                    temp_node = temp_node -> next_node_for_list;
                temp_node -> next_node_for_list = node_to_push;
            }
        }
        void search(int x);
    };

    struct Node{
        std::vector<std::pair<std::string, int>> int_arguments;
        std::vector<std::pair<std::string, float>> float_arguments;
        std::vector<std::pair<std::string, std::string>> string_arguments;
        std::vector<std::pair<std::string, bool>> bool_arguments;
        std::vector<std::pair<std::string, List*>> list_arguments;
    };

    struct Section{
         std::string name;

         Section* next = nullptr;
         Node* arguments = nullptr;
         Section* under_section = nullptr;

         Section(std::string name){
             this->name = name;
             this->arguments = new Node;
         }

         Section* width_find(Section* current_section, std::string name){
             while (current_section != nullptr){
                 if (current_section->name == name)
                     return current_section;
                 else
                     current_section = current_section -> next;
             }
             return nullptr;
         }
    };

    class Parser {
    private:
        Section* root_of_sections = nullptr;
        bool Valid = true;

    public:
        Parser(){
            root_of_sections = new Section("general");
        }

        Section* get_root_of_sections();

        void set_valid(bool flag);

        List* parse_list(std::vector<std::string> list_arguments);

        bool valid() const;

        Parser Get(std::string get_string) const;

        bool IsInt();

        bool IsFloat();

        bool IsString();

        bool IsArray();

        bool IsBool();

        int AsInt();

        int AsIntOrDefault(int def);

        float AsFloat();

        float AsFloatOrDefault(float def);

        std::string AsString();

        std::string AsStringOrDefault(std::string def);

        bool AsBool();

        bool AsBoolOrDefault(bool def);

        Parser operator[](int number);

        void exp_tree(std::string path) const;

        void push_all_from_section(Section* current_section, std::ofstream& file, int tabs_count) const;
    };

    Parser parse(const std::filesystem::path &path);

    Parser parse(const std::string &str);

    bool is_valid_key(std::string str_to_verify);

    int double_comma_count(std::string temp_string);

    void clear_pointers();

    bool verify_int_and_float(std::string temp_string);

}// namespace