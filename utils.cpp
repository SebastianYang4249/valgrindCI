//
// Created by oushu on 2022/9/7.
//

#include "utils.h"

std::pair<std::string, std::string> StrSplit(std::string str, const char ch) {
  int pivot = str.find(ch);
  std::string s1 = str.substr(0, pivot);
  std::string s2 = str.substr(pivot + 1, str.size() - 1);
  return {s1, s2};
}

bool IsBackend(std::string file, std::string backend) {
  if (file.find('.') == std::string::npos)
    return false;
  return file.substr(file.find('.'), file.size() - 1) == backend;
}

int FindNum(std::string s, char ch = ' ') {
  int res = 0;
  for (char c : s) {
    if (c == ch) {
      res++;
    }
  }
  return res;
}

std::vector<std::string> StrToVec(std::string s, char divide = ' ') {
  std::vector<std::string> res;
  int l = FindNum(s, divide);
  std::pair<std::string, std::string> part;
  part = StrSplit(s, divide);
  for (int i = 0; i < l; ++i) {
    res.push_back(part.first);
    part = StrSplit(part.second, divide);
  }
  return res;
}