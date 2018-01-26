#ifndef MAP_H
#define MAP_H

#include<string>
#include<vector>
#include "huffman_tree.h"

class Map {
private:
  struct lspair{
    std::string label;
    char symbol;

    lspair(const std::string& _label, char _symbol) : label(_label), symbol(_symbol){}
  };
  std::vector<lspair> table;
  void fillHelper(HuffmanTree::TreeNode*, std::string);
public:
  std::string operator[] (char);
  Map (const HuffmanTree&);
  void print();
};

#endif
