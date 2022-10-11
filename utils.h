//
// Created by oushu on 2022/9/7.
//

#ifndef VALGRIND_MEM_UTILS_H
#define VALGRIND_MEM_UTILS_H

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <algorithm>

#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include <string>
#include <fstream>
#include <stack>

enum SpiltMode{
  BEGIN,
  END
};

std::pair<std::string, std::string> StrSplit(const std::string& str, char ch = ' ', SpiltMode mode = BEGIN);
bool IsBackend(const std::string& file, const std::string& backend);
int FindNum(const std::string& s, char ch);
int FindNum(const std::string& s, const std::string& k);
std::vector<std::string> StrToVec(const std::string& s , char divide);
std::string RemoveSpace(std::string s);

#endif // VALGRIND_MEM_UTILS_H
