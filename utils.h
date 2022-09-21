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

std::pair<std::string, std::string> StrSplit(std::string str, const char ch = ' ');
bool IsBackend(std::string file, std::string backend);
int FindNum(std::string s, char ch);
std::vector<std::string> StrToVec(std::string s , char divide);

#endif // VALGRIND_MEM_UTILS_H
