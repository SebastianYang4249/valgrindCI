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
               list[i + 1]) == this->LeakMap[list[i]].end()) {
        this->LeakMap[list[i]].push_back(list[i + 1]);
      }
    }
  }

  for (const std::string &s : list) {
    if (find(this->TypeMap[t].begin(), this->TypeMap[t].end(), s) ==
        this->TypeMap[t].end()) {
      this->TypeMap[t].push_back(s);
    }
  }

  if (this->ListSet.find(l->GetList()) == this->ListSet.end()) {
    this->ListSet.insert(l->GetList());
  }
}

void ListStorage::CreateNewLeakPos(const std::string FuncName,
                                   const std::string Pos) {
  if (find(this->PosMap[FuncName].begin(), this->PosMap[FuncName].begin(),
           Pos) == this->PosMap[FuncName].end())
    this->PosMap[FuncName].push_back(Pos);
}

void ListStorage::SetSize(const std::string FuncName, int Size) {
  this->SizeMap[FuncName] += Size;
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
          FindNum(value, "operator") == -1) {
        if (this->PosMap.find(it.first) != this->PosMap.end()) {
          std::cout << "    " << it.first << "(" << it.first;
          for (const std::string &s : this->PosMap[it.first]) {
            std::cout << "<br>" << s;
          }
          std::cout << "<br>" << "Leak Size : " << this->SizeMap[it.first];
          std::cout << ")"
                    << " --> " << value << std::endl;
        } else{
          std::cout << "    " << it.first ;
          std::cout << "(" << "<br>Leak Size : " << this->SizeMap[it.first] << ")";
          std::cout << " --> " << value << std::endl;
        }
      }
    }
  }

  std::cout << std::endl;
  std::cout << "    classDef DefinitelyLost fill:#C5211C" << std::endl;
  std::cout << "    classDef IndirectlyLost fill:#E4443F" << std::endl;
  std::cout << "    classDef PossiblyLost fill:#F59B65" << std::endl;
  std::cout << "    classDef StillReachable fill:#F7BA79" << std::endl;
  std::cout << std::endl;

  std::vector<std::string> Type = {"DefinitelyLost", "IndirectlyLost",
                                   "PossiblyLost", "StillReachable"};
  for (const auto p : this->TypeMap) {
    std::cout << "    class ";
    if (FindNum(p.second[0], '<') == 0 && FindNum(p.second[0], '?') == 0 &&
        FindNum(p.second[0], '.') == 0 && FindNum(p.second[0], '@') == 0 &&
        FindNum(p.second[0], "operator") == -1)
      std::cout << p.second[0];
    for (int i = 1; i < p.second.size(); ++i) {
      if (FindNum(p.second[i], '<') > 0 || FindNum(p.second[i], '?') > 0 ||
          FindNum(p.second[i], '.') > 0 || FindNum(p.second[i], '@') > 0 ||
          FindNum(p.second[i], "operator") != -1)
        continue;
      std::cout << "," << p.second[i];
    }
    std::cout << " " << Type[p.first] << ";" << std::endl;
  }
}

std::vector<std::vector<std::string>> ListStorage::GetAllVecs() {
  std::vector<std::vector<std::string>> res;
  for (const std::string &s : this->ListSet) {
    res.push_back(StrToVec(s, '#'));
  }
  return res;
}
