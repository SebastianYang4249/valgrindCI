//
// Created by oushu on 2022/9/7.
//

#ifndef VALGRIND_MEM_UTILS_H
#define VALGRIND_MEM_UTILS_H

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <dirent.h>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

enum SpiltMode { BEGIN, END };

std::pair<std::string, std::string>
StrSplit(const std::string &str, char ch = ' ', SpiltMode mode = BEGIN);

std::pair<std::string, std::string>
StrSplit(const std::string &str, const std::string &k, SpiltMode mode = BEGIN);

bool IsBackend(const std::string &file, const std::string &backend);

int FindNum(const std::string &s, char ch);

int FindNum(const std::string &s, const std::string &k);

std::vector<std::string> StrToVec(const std::string &s, char divide);

std::string RemoveSpace(std::string s);

std::string RemoveCharInString(std::string &s, const char &ch);

#endif // VALGRIND_MEM_UTILS_H
