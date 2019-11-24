#ifndef SPLIT_H
#define SPLIT_H

#include "globals.h"
#include <iostream>
#include <vector>

#include "..\\..\\Graph_lib\\Graph.h"
#include "..\\..\\Graph_lib\\Simple_window.h"

std::vector<std::string> split(std::string s, char c = ' ');

bool in(const std::string &src, const char c);

bool in(const std::vector<std::string> &names, const std::string &s);

std::pair<std::string, int> separate(std::string s);

#endif // SPLIT_H
