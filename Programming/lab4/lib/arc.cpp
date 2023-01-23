#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>

std::string hamming_w(const std::string &buf) {
    std::string newbuf = buf;
    int temp = 1;

    for (int i = 0; i < buf.size(); i++) {
        if (temp - 1 == i) {
            newbuf.insert(i, "0");
            temp *= 2;
        }
    }

    temp = 1;

    for (int i = 0; i < newbuf.size(); i++) {
        int pos = temp;
        temp *= 2;

        if (pos < newbuf.size()) {
            bool flag_to_count = true;
            int signtif_count = 0;
            int unsigntif_count = 0;
            for (int j = pos - 1; j < newbuf.size(); j++) {
                unsigntif_count++;
                if (flag_to_count)
                    if (newbuf[j] == '1')
                        signtif_count++;
                if (unsigntif_count == pos) {
                    flag_to_count = !flag_to_count;
                    unsigntif_count = 0;
                }
            }

            if (signtif_count % 2 == 0)
                newbuf[pos - 1] = '0';
            else
                newbuf[pos - 1] = '1';
        } else
            break;
    }
    return newbuf;
}

std::string hamming_r(const std::string &buf) {
    std::string newbuf;
    std::string buf_copy(buf);
    int temp = 1;

    for (int i = 0; i < buf_copy.size(); i++) {
        if (temp - 1 == i) {
            temp *= 2;
        } else
            newbuf += buf_copy[i];
    }

    newbuf = hamming_w(newbuf);

    int errorplace = 0;
    for (int i = 0; i < newbuf.size(); i++) {
        if (buf[i] != newbuf[i]) {
            errorplace += i + 1;
        }
    }

    if (errorplace != 0)
        buf_copy[errorplace - 1] = buf_copy[errorplace - 1] == '0' ? '1' : '0';

    int pow = 1;
    temp = 0;

    for (int i = 0; i < buf_copy.size(); i++) {
        if (pow - 1 == i) {
            buf_copy.erase(i - temp, 1);
            pow *= 2;
            temp++;
        }
    }

    return buf_copy;
}

uint64_t completed_string_length(uint64_t len) {
    for (uint64_t i = len; i < len + 9; len++){
        if ((len % 8)  == 0)
            return len;
    }
}

uint64_t hamming_bits(uint64_t len) {
        uint64_t bit_len = len << 3;
        uint64_t new_bits = 0;

        uint64_t pow = 1;

        while (true) {
            if (pow <= bit_len + new_bits) {
                new_bits++;
                pow *= 2;
            } else
                return new_bits;
        }
}

uint64_t hamming_string_length(uint64_t len) {
    uint64_t bit_len = len << 3;
    return completed_string_length(bit_len + hamming_bits(len)) >> 3;
}

std::string to_binary(int8_t x) {
    std::string s(8, '0');

    for (int i = 7; i >= 0; --i) {
        s[i] = (char) ('0' + (x & 1));
        x >>= 1;
    }

    return s;
}

std::string complete_string(const std::string &s) {
    std::string r(s);
    int new_len_rem = 0;

    for (uint64_t i = 0; i < 8; i++){
        if ((r.size() + i) % 8 == 0) {
            new_len_rem = i;
            break;
        }
    }

    while (new_len_rem > 0) {
        r = "0" + r;

        --new_len_rem;
    }

    return r;
}

void to_bytes(const std::string &s, char *buffer) {
    size_t len = s.size() >> 3;

    for (uint64_t i = 0; i < len; ++i) {
        uint64_t offset = i << 3;
        uint8_t x = 0;

        for (uint64_t j = 0; j < 8; ++j)
            x = x * 2 + (s[offset + j] - '0');

        buffer[i] = (char) x;
    }
}

void list(std::string &arc) {
    std::ifstream arc_stream(arc, std::ios::binary);

    std::cout<<"FILES in Arc:\n";

    while (!arc_stream.eof() && arc_stream.good()) {
        std::string filename;
        char c;

        do {
            arc_stream.get(c);

            if (c != 0)
                filename += c;
        } while (c != 0);

        if (!filename.empty()) {
            std::cout << "- " << filename << std::endl;

            unsigned buf_size = 0;

            do {
                arc_stream.get(c);
                buf_size = (uint8_t) c;

                if (buf_size > 0)
                    arc_stream.seekg(hamming_string_length(buf_size), std::ios::cur);
            } while (buf_size > 0);
        }
    }

    arc_stream.close();
}

void extract(std::vector<std::string> &file_names, std::string &arc, int password) {
    std::ifstream arc_stream(arc, std::ios::binary);
    bool all_files = file_names.empty();

    while (!arc_stream.eof() && arc_stream.good()) {
        std::string filename;
        char c;

        do {
            arc_stream.get(c);

            if (c != 0)
                filename += c;
        } while (c != 0);

        bool contains_file = std::find(file_names.begin(), file_names.end(), filename) != file_names.end();

        if (contains_file || all_files) {
            std::ofstream arc_entry(filename, std::ios::binary);

            unsigned buf_size;

            do {
                arc_stream.get(c);
                if ((uint8_t)c != 0)
                    buf_size = ((uint8_t) c) - password;
                else
                    buf_size = (uint8_t) c;

                if (buf_size > 0) {
                    uint64_t hamming_string_bit_length = (buf_size << 3) + hamming_bits(buf_size);
                    char *buf = new char[buf_size];
                    uint64_t sz = hamming_string_length(buf_size);
                    char *ham_buf = new char[sz];

                    arc_stream.read(ham_buf, sz);

                    std::string tmp;

                    for (uint64_t i = 0; i < sz; ++i)
                        tmp += to_binary(ham_buf[i]);

                    tmp.erase(0, (sz << 3) - hamming_string_bit_length);

                    tmp = hamming_r(tmp);

                    to_bytes(tmp, buf);
                    arc_entry.write(buf, buf_size);

                    delete [] buf;
                    delete [] ham_buf;
                }
            } while (buf_size > 0);

            arc_entry.close();
        }
        else {
            unsigned buf_size;

            do {
                arc_stream.get(c);
                buf_size = ((uint8_t) c) - password;

                if (buf_size > 0)
                    arc_stream.seekg(hamming_string_length(buf_size), std::ios::cur);
            } while (buf_size > 0);
        }
    }

    arc_stream.close();
}

void write_to_archive(std::vector<std::string> &file_names, std::string &result_arc, std::ios::openmode mode, int frequency, int password) {
    std::ofstream arc(result_arc, std::ios::binary | mode);

    frequency = (uint8_t) frequency;

    char *buffer = new char[(uint8_t) frequency];

    uint64_t buffer2_size = hamming_string_length(frequency);
    char *buffer2 = new char[buffer2_size];

    for (std::string &file_name: file_names) {
        arc.write(file_name.c_str(), (uint64_t) file_name.size() + 1);
        std::ifstream file(file_name, std::ios::binary);

        while (!file.eof() && file.good()) {
            memset(buffer, 0, frequency);
            file.read(buffer, frequency);
            std::string tmp;

            uint8_t bytes = 0;
            std::streamsize read_bytes = file.gcount();

            while (bytes < read_bytes)
                tmp += to_binary(buffer[bytes++]);

            if (!tmp.empty()) {
                std::string h_w = hamming_w(tmp);
                buffer[0] = (char) (bytes + password);

                arc.write(buffer, 1);

                h_w = complete_string(h_w);
                uint64_t buf2_sz = (uint64_t) h_w.size() >> 3;
                memset(buffer2, 0, buffer2_size);

                to_bytes(h_w, buffer2);
                arc.write(buffer2, buf2_sz);
            }
        }

        char zero = 0;
        arc.write(&zero, 1);

        file.close();
    }

    delete [] buffer2;
    delete [] buffer;

    arc.close();
}

void del(std::vector<std::string> &file_names, std::string &arc) {
    FILE* temp_file = std::tmpfile();
    char *buffer;

    if (temp_file != nullptr) {
        std::ifstream arc_rstream(arc, std::ios::binary);

        while (!arc_rstream.eof() && arc_rstream.good()) {
            std::string filename;
            char c;

            do {
                arc_rstream.get(c);

                if (c != 0)
                    filename += c;
            } while (c != 0);

            bool contains_file = std::find(file_names.begin(), file_names.end(), filename) == file_names.end();

            if (contains_file) {
                fputs(filename.c_str(), temp_file);
                fputc(0, temp_file);

                unsigned buf_size;

                do {
                    arc_rstream.get(c);
                    buf_size = (uint8_t) c;
                    fwrite(&c, sizeof(char), 1, temp_file);

                    if (buf_size > 0) {
                        uint64_t sz = hamming_string_length(buf_size);
                        buffer = new char[sz];

                        arc_rstream.read(buffer, sz);

                        fwrite(buffer, sizeof(char), arc_rstream.gcount(), temp_file);

                        delete [] buffer;
                    }
                } while (buf_size > 0);
            }
            else {
                unsigned buf_size;

                do {
                    arc_rstream.get(c);
                    buf_size = (uint8_t) c;

                    if (buf_size > 0)
                        arc_rstream.seekg(hamming_string_length(buf_size), std::ios::cur);
                } while (buf_size > 0);
            }
        }

        arc_rstream.close();

        fseek(temp_file, 0, SEEK_SET);
        std::ofstream arc_wstream(arc, std::ios::binary);
        buffer = new char[4096];

        while (!feof(temp_file)) {
            size_t bytes = fread(buffer, sizeof(char), 4096, temp_file);

            arc_wstream.write(buffer, (std::streamsize) bytes);
        }

        arc_wstream.close();

        delete [] buffer;

        fclose(temp_file);
    }
}

void concatenate(std::vector<std::string> &file_names, std::string &arc) {
    FILE* temp_file = std::tmpfile();

    if (temp_file != nullptr) {
        char *buffer = new char[4096];

        for (std::string &file: file_names) {
            std::ifstream filestream(file, std::ios::binary);

            while (!filestream.eof() && filestream.good()) {
                memset(buffer, 0, 4096);
                filestream.read(buffer, 4096);
                std::streamsize sz = filestream.gcount();

                fwrite(buffer, sizeof(char), sz, temp_file);
            }

            filestream.close();
        }

        fseek(temp_file, 0, SEEK_SET);
        std::ofstream arc_stream(arc, std::ios::binary);

        while (!feof(temp_file)) {
            size_t bytes = fread(buffer, sizeof(char), 4096, temp_file);

            arc_stream.write(buffer, (std::streamsize) bytes);
        }

        arc_stream.close();

        delete [] buffer;

        fclose(temp_file);
    }
}

void todo(std::vector<std::string> &file_names, const bool *params, std::string &result_arc, int frequency, int password) {
    if (params[0])
        write_to_archive(file_names, result_arc, std::ios::trunc, frequency, password);

    if (params[2])
        list(result_arc);

    if (params[3]){
        extract(file_names, result_arc, password);
    }

    if (params[4])
        write_to_archive(file_names, result_arc, std::ios::app, frequency, password);

    if (params[5])
        del(file_names, result_arc);

    if (params[6])
        concatenate(file_names, result_arc);
}
