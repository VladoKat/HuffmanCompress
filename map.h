#ifndef MAP_H
#define MAP_H

#include<string>
#include<map>
#include "huffman_tree.h"

class Map {
private:
  std::map<char, std::string> table;
  void fillHelper(HuffmanTree::TreeNode*, std::string);
public:
  std::string operator[] (char);
  Map (const HuffmanTree&);
  void print();
};

#endif
