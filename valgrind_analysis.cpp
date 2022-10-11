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
      {"are definitely lost", DefinitelyLost},
      {"are indirectly lost", IndirectlyLost},
      {"are possibly lost", PossiblyLost},
      {"are still reachable", StillReachable}};

  while (getline(fin, buffer)) {
    for (const auto p : typeMap) {
      if (buffer.find(p.first) != std::string::npos) {
        std::vector<std::string> list;
        int leakSize = stoi(RemoveSpace(
            StrSplit(StrSplit(buffer, '=', END).second, 'b', BEGIN).first));
        getline(fin, buffer);
        while (buffer.find(":") != std::string::npos) {
          std::string Str = StrSplit(buffer, ':').second;
          std::string fileName =
              StrSplit(StrSplit(Str, '(', END).second, ':').first;
          if (files.find(fileName) != files.end()) {
            std::string funcName = RemoveSpace(StrSplit(Str, '(', BEGIN).first);
            list.push_back(funcName);
            ls.CreateNewLeakPos(
                funcName, StrSplit(StrSplit(Str, '(', END).second, ')').first);
            ls.SetSize(funcName, leakSize);
          }
          getline(fin, buffer);
        }
        ls.CreateNewList(list, p.second);
      }
    }
  }
}

int main(int argc, char *argv[]) {
  ASSERT(argc >= 2, "At least two parameters needed : source code directory, "
                    "new memcheck report directory, old report directory");

  std::unordered_map<std::string, std::string> files = FileTree(argv[1]);

  std::unordered_map<std::string, std::string> reportFiles =
      FileTree(argv[2], {".", ".."}, {".log"});
  ListStorage ls;
  ListStorage OldLS;

  for (const auto &p : reportFiles) {
    std::cout << "Reading file : " << p.second << std::endl;
    ReadReport(ls, p.second, files);
  }

  /*
  std::unordered_map<std::string, std::string> oldReports = FileTree(argv[3]);

  for (const auto & p : oldReports){
    ReadReport(OldLS, p.second, files);
  }
  std::unordered_set<std::string> Fixed;
  std::unordered_set<std::string> Created;

   */

  ls.getMermaid();
}
