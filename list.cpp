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

void ListStorage::CreateNewList(const std::vector<std::string> &list) {
  List *l = new List;
  for (const std::string &s : list) {
    l->PushBack(s);
  }
  for ( int i = 0; i< list.size() - 2; ++i){
    mmap[list[i]].push_back(list[i+1]);
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