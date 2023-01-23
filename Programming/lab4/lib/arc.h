#ifndef LABWORK_4_RISKMAN5_ARC_H
#define LABWORK_4_RISKMAN5_ARC_H

#endif //LABWORK_4_RISKMAN5_ARC_H

#include <vector>
#include <string>
#include <iostream>

void todo(std::vector<std::string>& file_names, const bool* params, std::string& result_arc, int frequency, int password);

void write_to_archive(std::vector<std::string>& file_names, std::string& result_arc, std::ios::openmode mode, int frequency, int password);

void list(std::string &arc);

void extract(std::vector<std::string>& file_names, std::string &arc, int password);

void del(std::vector<std::string>& file_names, std::string& result_arc);

void concatenate(std::vector<std::string> &file_names, std::string &arc);

std::string hamming_w(const std::string &buffer);

std::string hamming_r(const std::string &buffer);



