// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  <vector>
#include  <algorithm>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);

  if (!file) {
    std::cout << "File error!" << std::endl;
    return;
  }

  std::string word;

  while (!file.eof()) {
    int ch = file.get();

    if ((ch >= 'A' && ch <= 'Z') ||
        (ch >= 'a' && ch <= 'z')) {
      if (ch >= 'A' && ch <= 'Z') {
        ch = ch - 'A' + 'a';
      }

      word += static_cast<char>(ch);
    } else {
      if (!word.empty()) {
        tree.insert(word);
        word.clear();
      }
    }
  }

  if (!word.empty()) {
    tree.insert(word);
  }

  file.close();
}

void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> arr;

  arr = tree.getData();

  std::sort(arr.begin(),
            arr.end(),
            [](const std::pair<std::string, int>& a,
               const std::pair<std::string, int>& b) {
      return a.second > b.second;
    });

  std::ofstream fout("result/freq.txt");

  for (size_t i = 0; i < arr.size(); i++) {
    std::cout << arr[i].first
              << " "
              << arr[i].second
              << std::endl;

    fout << arr[i].first
         << " "
         << arr[i].second
         << std::endl;
  }

  fout.close();
}
