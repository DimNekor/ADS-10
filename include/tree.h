// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>
#include <iostream>

struct Node {
  char digit = '\0';
  std::vector<Node*> derivatives;
};

class Tree {
 public:
  Tree(const std::vector<char>&);
  std::vector<std::vector<char>> getRearr() const;
  void Rearr(Node*, std::vector<char>);

 private:
  std::vector<char> info;
  Node* head = nullptr;
  std::vector<std::vector<char>> list_vec;
  Node* Tree_create(Node*, const std::vector<char>&);
  Node* Node_create(char);
};

inline Node* Tree::Node_create(char info) {
    Node* interim = new Node;
    interim->digit = info;
    return interim;
}

void EraseVec(std::vector<char> vec, const std::vector<char>& info,
              int iterator) {
    vec.erase(std::find(vec.begin(), vec.end(), info[iterator]));
}

void pushBack(Node* point_tree, Node* head) {
    head->derivatives.push_back(point_tree);
}

inline Node* Tree::Tree_create(Node* head, const std::vector<char>& info) {
    if (nullptr == head) {
      head = new Node;
    }
    for (int i = 0; i < info.size(); i++) {
      int k = 0;
      Node* pointer = Node_create(info[i]);
      head->derivatives.push_back(pointer);
      std::vector<char> levels(info);
      levels.erase(std::find(levels.begin(), levels.end(), info[i]));
      Tree_create(pointer, levels);
      k++;
    }
    return head;
}

inline std::vector<std::vector<char>> Tree::getRearr() const {
    return list_vec;
}

Tree::Tree(const std::vector<char>& vec) {
  head = Tree_create(head, vec);
  Rearr(head, {});
}
void Tree::Rearr(Node* head, std::vector<char> rec) {
  if ('\0' != head->digit && head) {
    rec.push_back(head->digit);
  }
  if (0 == head->derivatives.size()) {
    list_vec.push_back(rec);
  }
  for (Node* derivative : head->derivatives) 
    Rearr(derivative, rec);
}
#endif  // INCLUDE_TREE_H_
