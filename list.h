//
// Created by oushu on 2022/9/15.
//

#ifndef VALGRIND_MEM_LIST_H
#define VALGRIND_MEM_LIST_H

#include <utility>

#include "utils.h"

enum LeakType {
  DefinitelyLost,
  IndirectlyLost,
  PossiblyLost,
  StillReachable,
};

class List {
public:
  ~List();
  void PushBack(std::string s);
  std::string GetList();
  std::string GetFront();
  int ListLen();

private:
  char split = '#';
  std::string ListStr;
};

class ListStorage {
public:
  void CreateNewList(const std::vector<std::string> &list, LeakType t);
  std::vector<std::string> GetAllLists();
  std::vector<std::vector<std::string>> GetAllVecs();
  void getMermaid();

private:
  std::unordered_set<std::string> ListSet;
  std::unordered_map<std::string, std::vector<std::string>> LeakMap;
  std::unordered_map<std::string, LeakType> TypeMap;
};

class Tree {
public:
  Tree(std::string s);
  void AddChild(std::string s);

private:
  std::string value;
  std::unordered_map<std::string, Tree *> childs;
};

#endif // VALGRIND_MEM_LIST_H
