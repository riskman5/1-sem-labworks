#include "number.h"
#include <string>


uint2022_t from_uint(uint32_t i) {
    uint2022_t from_uint_out;
    from_uint_out.arr[67] = i % 1000000000;
    from_uint_out.arr[66] = i / 1000000000;
    return from_uint_out;
}

uint2022_t from_string(const char* buff) {
    std::string temp_string(buff);
    int index = 67;
    uint2022_t from_string_out;
    while (temp_string.size() > 0){
        if (temp_string.size() < 9){
            from_string_out.arr[index] = std::stoi(temp_string);
            break;
        }
        from_string_out.arr[index] = std::stoi(temp_string.substr(temp_string.size()-9, 9));
        temp_string = temp_string.substr(0, temp_string.size() - 9);
        index--;
    }

    return from_string_out;
}

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t sum_out;
    int sum_remains = 0;
    int i;

    for (i = 67; i >= 0; i--){
        uint64_t current_res = lhs.arr[i] + rhs.arr[i] + sum_remains;
        if (current_res / 1000000000 > 0){
            sum_remains = current_res / 1000000000;
            sum_out.arr[i] = current_res % 1000000000;
        }
        else{
            sum_remains = 0;
            sum_out.arr[i] = current_res % 1000000000;
        }
    }

    return sum_out;
}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t sub_out;
    char sub_remains = 0;
    int i;

    for(i = 67; i >= 0; i--){
        if (lhs.arr[i] - sub_remains >= rhs.arr[i]){
            sub_out.arr[i] = lhs.arr[i] - rhs.arr[i] - sub_remains;
            sub_remains = 0;
        }
        else{
            sub_out.arr[i] = lhs.arr[i] + 1000000000 - rhs.arr[i];
            sub_remains = 1;
        }
    }
    return sub_out;
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t multipl_out;
    uint64_t multipl_remains = 0;
    uint64_t temp;
    int index = 0;
    int i;
    int j;

    for(i = 67; i >= 0; i--) {
        for (j = 67; j >= 0; j--) {
            if (j - index >= 0) {
                temp = (uint64_t) lhs.arr[i] * rhs.arr[j] + multipl_remains + multipl_out.arr[j - index];
                multipl_out.arr[j - index] = temp % 1000000000;
                multipl_remains = temp / 1000000000;
            }
        }
        index++;
    }

    return multipl_out;
}



bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {
    int i;
    for (i = 0; i<68; i++){
        if (lhs.arr[i] != rhs.arr[i]){
            return false;
        }
    }

    return true;
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {
    int i;
    for (i = 0; i<68; i++){
        if (lhs.arr[i] != rhs.arr[i]){
            return true;
        }
    }

    return false;
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
    int i;
    int first_index;
    for (i = 0; i < 68; i++){
        if (value.arr[i] != 0){
            first_index = i;
            break;
        }
    }

    stream << value.arr[first_index];
    for (i = first_index + 1;i < 68;i++){
        std::string num_lenght = std::to_string(value.arr[i]);
        while (num_lenght.size() != 9){
            num_lenght = "0" + num_lenght;
        }
        stream << num_lenght;
    }

    return stream;
}