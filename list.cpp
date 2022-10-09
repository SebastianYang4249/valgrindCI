//
// Created by oushu on 2022/9/15.
//

#include "list.h"

List::~List() {}

void List::PushBack(std::string s) {
  this->ListStr += s;
  this->ListStr += this->split;
}

std::string List::GetList() { return this->ListStr; }

std::string List::GetFront() {
  return StrSplit(this->ListStr, this->split).first;
}

int List::ListLen() {
  int res = FindNum(this->ListStr, this->split) - 1;
  return res < 0 ? 0 : res;
}

void ListStorage::CreateNewList(const std::vector<std::string> &list,
                                LeakType t) {
  if (!list.size())
    return;
  List *l = new List;
  for (const std::string &s : list) {
    l->PushBack(s);
  }

  if (list.size() >= 2) {
    for (int i = 0; i < list.size() - 2; ++i) {
      if (find(this->LeakMap[list[i]].begin(), this->LeakMap[list[i]].end(),
               list[i + 1]) == this->LeakMap[list[i]].end())
        this->LeakMap[list[i]].push_back(list[i + 1]);
    }
  }

  for (const std::string &s : list) {
    this->TypeMap[s] = t;
  }

  if (this->ListSet.find(l->GetList()) == this->ListSet.end()) {
    this->ListSet.insert(l->GetList());
  }
}

std::vector<std::string> ListStorage::GetAllLists() {
  std::vector<std::string> res;
  for (const std::string &s : this->ListSet) {
    res.push_back(s);
  }
  return res;
}

void ListStorage::getMermaid() {
  std::cout << "graph LR" << std::endl;
  for (const auto &it : this->LeakMap) {
    if (FindNum(it.first, '<') > 0 || FindNum(it.first, '?') > 0 ||
        FindNum(it.first, '.') > 0 || FindNum(it.first, '@') > 0 ||
        FindNum(it.first, "operator") != -1)
      continue;
    for (const auto &value : it.second) {
      if (FindNum(value, '<') == 0 && FindNum(value, '?') == 0 &&
          FindNum(value, '.') == 0 && FindNum(value, '@') == 0 &&
          FindNum(value, "operator") == -1)
        std::cout << it.first << " --> " << value << std::endl;
    }
  }

  std::vector<std::string> TypeColor = {"#C848B9", "#F962A7", "#FD836D",
                                        "#FFBA69"};
  for (const auto p : this->TypeMap) {
    if (FindNum(p.first, '<') > 0 || FindNum(p.first, '?') > 0 ||
        FindNum(p.first, '.') > 0 || FindNum(p.first, '@') > 0 ||
        FindNum(p.first, "operator") != -1)
      continue;
    std::cout << " style" << p.first << " fill:" << TypeColor[p.second] << ";"
              << std::endl;
  }
}

std::vector<std::vector<std::string>> ListStorage::GetAllVecs() {
  std::vector<std::vector<std::string>> res;
  for (const std::string &s : this->ListSet) {
    res.push_back(StrToVec(s, '#'));
  }
  return res;
}

Tree::Tree(std::string s) { this->value = s; }

void Tree::AddChild(std::string s) {
  Tree *root = new Tree(s);
  this->childs.insert(std::make_pair(s, root));
}