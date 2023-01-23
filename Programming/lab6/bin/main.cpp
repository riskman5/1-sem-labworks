#include "lib/parser.h"
#include <iostream>


int main(int, char**) {
    std::string data = R"(
        [level1]
        key1 = 1

        [level1.level2-1]
        key2 = 2

        [level1.level2-2]
        key3 = 3
        key4 = 5
        key5 = "hello"

        [level3]

        [level1.level2-2.level2-2-2]
        key8 = "how are you"
        key10 = "whats up"

        [level2]
        key10 = 10
)";

    const auto root = omfl::parse(data);

    root.exp_tree("D:/tree.tree");


    return 0;
}
