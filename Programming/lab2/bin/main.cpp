
#include <lib/number.h>
#include <iostream>

int main() {
    uint2022_t value1, value2;
    value1 = from_uint(2147483647);
    value2 = from_string("2147483647");
    std::cout << (value1 == value2) << std::endl;

    return 0;
}
