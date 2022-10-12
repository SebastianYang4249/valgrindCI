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
  StillReachable
};

enum Colors {
  sunset,
  posicle,
  cranberry,
  warming
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
  // create a new list by provide list vector

  void CreateNewLeakPos(const std::string FuncName, const std::string Pos);
  // create a pair of leak function and its name

  void SetSize(const std::string FuncName, int Size);

  std::vector<std::string> GetAllLists();
  // get all list in ListSet

  std::vector<std::vector<std::string>> GetAllVecs();
  // get all list in ListSet and get a vector type

  void getMermaid(Colors c);
  // get mermaid file output

private:
  std::unordered_set<std::string> ListSet;
  // restore all leak functions call lists

  std::unordered_map<std::string, std::vector<std::string>> LeakMap;
  // restore a graph of 1 to multiple pairs

  std::unordered_map<LeakType, std::vector<std::string>> TypeMap;
  // restore classified function names by leak type

  std::unordered_map<std::string, std::vector<std::string>> PosMap;
  // restore leak functions and its position in files

  std::unordered_map<std::string, int> SizeMap;
  // restore leak functions and its leak size
};
#endif // VALGRIND_MEM_LIST_H
