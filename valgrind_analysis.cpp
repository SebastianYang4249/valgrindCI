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
        std::string leakSizeRaw = RemoveSpace(
            StrSplit(StrSplit(buffer, '=', END).second, 'b', BEGIN).first);
        int leakSize;
        if (FindNum(leakSizeRaw, ',') > 0) {
          leakSize = stoi(RemoveCharInString(leakSizeRaw, ','));
        } else {
          leakSize = stoi(leakSizeRaw);
        }
        getline(fin, buffer);
        while (buffer.find(":") != std::string::npos) {
          std::string Str = StrSplit(buffer, ':').second;
          std::string fileName =
              StrSplit(StrSplit(Str, '(', END).second, ':').first;
          if (FindNum(fileName, '/') != 0) {
            fileName = StrSplit(fileName, '/', END).second;
          }
          if (files.find(fileName) != files.end()) {
            std::string funcName = RemoveSpace(StrSplit(Str, '(', BEGIN).first);
            list.push_back(funcName);
            std::string filePos =
                StrSplit(StrSplit(Str, '(', END).second, ')').first;
            if (FindNum(filePos, '/')) {
              ls.CreateNewLeakPos(
                  funcName,
                  StrSplit(StrSplit(Str, '(', END).second, ')').first);
            } else {
              ls.CreateNewLeakPos(
                  funcName,
                  "/src/" + StrSplit(files[fileName], "src").second + ":" +
                      StrSplit(StrSplit(filePos, ':').second, ')').first);
            }
            ls.SetSize(funcName, leakSize);
          }
          getline(fin, buffer);
        }
        ls.CreateNewList(list, p.second);
      }
    }
  }
}

std::unordered_map<std::string, std::vector<std::string>>
GetArgs(int argc, char *argv[]) {
  std::unordered_map<std::string, std::vector<std::string>> args;
  for (int i = 1; i < argc; ++i) {
    std::string option = StrSplit(std::string(argv[i]), '=').first;
    std::string value = StrSplit(std::string(argv[i]), '=').second;
    args[option].push_back(value);
  }
  return args;
}

int main(int argc, char *argv[]) {
  if (argc == 1 && argv[1] == "help") {
    std::cout
        << "    -c=xxx to add your source code directory    [at least one]"
        << std::endl;
    std::cout
        << "    -o=xxx to add your old reports directory    [at least one]"
        << std::endl;
    std::cout
        << "    -n=xxx to add your new reports directory    [at least one]"
        << std::endl;
    std::cout
        << "    -f=xxx to custom your own svg colors        [not necessary]"
        << std::endl;
    std::cout << "        choice : sunset / posicle / cranberry / warming"
              << std::endl;
  }

  std::unordered_map<std::string, std::vector<std::string>> args =
      GetArgs(argc, argv);
  ASSERT(args.size() >= 2,
         "At least two parameters needed : source code directory, "
         "new memcheck report directory, old report directory");

  std::unordered_map<std::string, std::string> files;
  for (const std::string &s : args["-c"]) {
    FileTree(files, s, {".", "..", ".git"},
             {".c", ".cc", ".h", ".cpp", ".hpp"});
  }
  ASSERT(files.size() > 0, "source code directory has no files in it");

  std::unordered_map<std::string, std::string> reportFiles;
  for (const std::string &s : args["-o"]) {
    FileTree(reportFiles, s, {".", "..", ".git"}, {".log"});
  }
  ASSERT(reportFiles.size() > 0, "reports directory has no files in it");

  ListStorage ls;
  ListStorage OldLS;

  for (const auto &p : reportFiles) {
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

  std::unordered_map<std::string, Colors> cPairs = {{"sunset", sunset},
                                                    {"posicle", posicle},
                                                    {"cranberry", cranberry},
                                                    {"warming", warming}};
  Colors c = (args.find("-f") == args.end()) ? warming : cPairs[args["-f"][0]];
  ls.getMermaid(c);
}
