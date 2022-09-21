//
// Created by oushu on 2022/9/8.
//

#include "file.h"

void FileTreeDfs(std::string dir,
                 std::unordered_map<std::string, std::string> &files,
                 std::unordered_set<std::string> ignoreFiles,
                 std::vector<std::string> mask) {
  DIR *dp;
  struct dirent *dirp;
  struct stat fileStat;
  std::string filePath;

  dp = opendir(dir.c_str());

  ASSERT(dp != NULL, "cannot open folder " + dir);

  while (dirp = readdir(dp)) {
    filePath = dir + "/" + dirp->d_name;
    std::string fileName = std::string(dirp->d_name);

    if (ignoreFiles.find(fileName) != ignoreFiles.end()) {
      continue;
    }

    if (stat(filePath.c_str(), &fileStat)) {
      continue;
    }

    if (S_ISDIR(fileStat.st_mode)) {
      FileTreeDfs(filePath, files, ignoreFiles, mask);
    }

    for (auto it = mask.begin(); it != mask.end(); ++it) {
      if (IsBackend(fileName, *it)) {
        files[fileName] = filePath;
      }
    }
  }
}

std::unordered_map<std::string, std::string> FileTree(std::string dir) {
  std::unordered_map<std::string, std::string> files;
  std::unordered_set<std::string> ignores = {".", "..", ".git"};
  std::vector<std::string> masks = {".c", ".cpp", ".h", ".hpp"};
  FileTreeDfs(dir, files, ignores, masks);
  return files;
}
