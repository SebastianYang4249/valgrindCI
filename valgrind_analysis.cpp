//
// Created by oushu on 2022/9/7.
//

#include "valgrind_analysis.h"

void ReadReport(ListStorage &ls, std::string reportFile,
                std::unordered_map<std::string, std::string> files) {
  std::ifstream fin(reportFile);

  ASSERT(fin.good(), "open report file " + reportFile + " failed");

  std::string buffer;
  std::unordered_map<std::string, LeakType> typeMap = {
      {"definitely lost", DefinitelyLost},
      {"indirectly lost", IndirectlyLost},
      {"possibly lost", PossiblyLost},
      {"still reachable", StillReachable}};
  while (getline(fin, buffer)) {
    for (const auto p : typeMap) {
      if (buffer.find(p.first) != std::string::npos) {
        std::vector<std::string> list;
        getline(fin, buffer);
        while (buffer.find(":") != std::string::npos) {
          std::string func = StrSplit(buffer, ':').second;
          std::string fileName =
              StrSplit(StrSplit(func, '(', END).second, ':').first;
          if (files.find(fileName) != files.end())
            list.push_back(StrSplit(func, '(', BEGIN).first);
          getline(fin, buffer);
        }
        ls.CreateNewList(list, p.second);
      }
    }
  }
}

int main(int argc, char *argv[]) {
  ASSERT(argc >= 2, "At least two parameters needed : source code directory "
                    "and memcheck report file");

  std::unordered_map<std::string, std::string> files = FileTree(argv[1]);
  /*
  for (const auto &it : files) {
    std::cout << "file : " << it.first << ", directory : " << it.second
              << std::endl;
  }
   */

  std::string reportFile(argv[2]);
  ListStorage ls;

  ReadReport(ls, reportFile, files);

  /*
  std::vector<std::string> res = ls.GetAllLists();
  for (const auto &s : res) {
    std::cout << s << std::endl;
  }
   */

  ls.getMermaid();
}
