#include<string>
#include<vector>
#include "huffman_tree.h"
class Map {
private:
  //friend class HuffmanTree;
  struct lspair{
    std::string label;
    char symbol;

    lspair(const std::string& _label, char _symbol) : label(_label), symbol(_symbol){}
  };
  std::vector<lspair> table;
  void fillHelper(HuffmanTree::TreeNode*, std::string);
public:
  std::string operator[] (char);
  std::vector<unsigned char> compress (const std::string&);
  Map (const HuffmanTree&);
  void print();
};
