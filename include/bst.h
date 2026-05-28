// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>
#include <utility>

template<typename T>
class BST {
 private:
  struct Node {
    T key;
    int count;
    Node *left;
    Node *right;

    explicit Node(T val) {
      key = val;
      count = 1;
      left = nullptr;
      right = nullptr;
    }
  };

  Node *root;

  void addNode(Node **tmp, T val) {
    if (*tmp == nullptr) {
      *tmp = new Node(val);
      return;
    }

    if (val == (*tmp)->key) {
      (*tmp)->count++;
    } else if (val < (*tmp)->key) {
      addNode(&((*tmp)->left), val);
    } else {
      addNode(&((*tmp)->right), val);
    }
  }

  bool find(Node *tmp, T val) {
    if (tmp == nullptr) {
      return false;
    }

    if (tmp->key == val) {
      return true;
    }

    if (val < tmp->key) {
      return find(tmp->left, val);
    }

    return find(tmp->right, val);
  }

  int calcDepth(Node *tmp) {
    if (tmp == nullptr) {
      return 0;
    }

    int l = calcDepth(tmp->left);
    int r = calcDepth(tmp->right);

    if (l > r) {
      return l + 1;
    }

    return r + 1;
  }

  void fill(Node *tmp,
            std::vector<std::pair<T, int>> *arr) {
    if (tmp == nullptr) {
      return;
    }

    fill(tmp->left, arr);

    arr->push_back(std::make_pair(tmp->key,
                                  tmp->count));

    fill(tmp->right, arr);
  }

 public:
  BST() {
    root = nullptr;
  }

  void insert(T val) {
    addNode(&root, val);
  }

  bool search(T val) {
    return find(root, val);
  }

  int depth() {
    return calcDepth(root);
  }

  std::vector<std::pair<T, int>> getData() {
    std::vector<std::pair<T, int>> arr;

    fill(root, &arr);

    return arr;
  }
};

#endif  // INCLUDE_BST_H_
