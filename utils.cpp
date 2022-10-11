//
// Created by oushu on 2022/9/7.
//

#include "utils.h"

std::pair<std::string, std::string> StrSplit(const std::string &str, char ch,
                                             SpiltMode mode) {
  int pivot;
  if (mode == BEGIN)
    pivot = str.find(ch);
  else
    pivot = str.rfind(ch);
  std::string s1 = str.substr(0, pivot);
  std::string s2 = str.substr(pivot + 1, str.size() - 1);
  return {s1, s2};
}

bool IsBackend(const std::string &file, const std::string &backend) {
  if (file.find('.') == std::string::npos)
    return false;
  return file.substr(file.find('.'), file.size() - 1) == backend;
}

int FindNum(const std::string &s, char ch = ' ') {
  int res = 0;
  for (char c : s) {
    if (c == ch) {
      res++;
    }
  }
  return res;
}

int FindNum(const std::string &s, const std::string &k) { return s.find(k); }

std::vector<std::string> StrToVec(const std::string &s, char divide = ' ') {
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

std::string RemoveSpace(std::string s) {
  if (FindNum(s) > 0) {
    int left = 0, right = s.size() - 1;
    while (left < right) {
      if (s[left] == ' ')
        left++;
      break;
    }
    while (right > left) {
      if (s[right] == ' ')
        right--;
      break;
    }
    return s.substr(left, right);
  }
}