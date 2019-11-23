#ifndef EDITTING_FILES_H
#define EDITTING_FILES_H

#include "pictures_treatment.h"

void read_directory(const std::string &name, std::vector<std::string> &v);

void del(const std::string &path);

bool check_file(const std::string &path);

void clear();

std::vector<std::vector<std::pair<std::string, std::string>>> get_states(const std::string &src);

void cl(std::vector<std::string> &src);

#endif // EDITTING_FILES_H
