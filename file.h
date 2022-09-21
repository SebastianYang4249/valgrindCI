//
// Created by oushu on 2022/9/8.
//

#ifndef VALGRIND_MEM_FILE_H
#define VALGRIND_MEM_FILE_H

#include <errno.h>

#include "utils.h"

#define ASSERT(expr, log) do { if(!!(expr)) ; else std::cerr << log << std::endl; } while(0)

void FileTreeDfs(std::string dir, std::unordered_map<std::string, std::string>& files, std::unordered_set<std::string> ignoreFiles, std::vector<std::string> mask);
std::unordered_map<std::string, std::string> FileTree(std::string dir);

#endif // VALGRIND_MEM_FILE_H
