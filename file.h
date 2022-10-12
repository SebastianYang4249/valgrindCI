//
// Created by oushu on 2022/9/8.
//

#ifndef VALGRIND_MEM_FILE_H
#define VALGRIND_MEM_FILE_H

#include <errno.h>

#include "utils.h"

#define ASSERT(expr, log) do { if(!!(expr)) ; else std::cerr << log << std::endl; } while(0)

void FileTreeDfs(std::string dir, std::unordered_map<std::string, std::string>& files, std::unordered_set<std::string> ignoreFiles, std::vector<std::string> mask);
void FileTree(std::unordered_map<std::string, std::string> &files, std::string dir, std::unordered_set<std::string> ignores, std::vector<std::string> masks);

#endif // VALGRIND_MEM_FILE_H
