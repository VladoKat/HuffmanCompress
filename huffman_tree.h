#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include "frequency_table.h"
class Map;
class HuffmanTree {
private:
  friend class Map;
  struct TreeNode {
    int numOcc;
    char symbol;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int _numOcc, char _symbol) : symbol(_symbol),
                                          numOcc(_numOcc),
                                          left(nullptr),
                                          right(nullptr) {}
    TreeNode(int _numOcc, char _symbol, TreeNode* _left, TreeNode* _right) : symbol(_symbol),
                                          numOcc(_numOcc),
                                          left(_left),
                                          right(_right) {}
    ~TreeNode();
  };

  void makeTree(std::vector<HuffmanTree*>&);
  HuffmanTree findMin(std::vector<HuffmanTree*>);
  static void remove(std::vector<HuffmanTree*>&, const HuffmanTree&);
  void printHelper(TreeNode*);
  void printLeavesHelper(TreeNode*);
  static std::vector<HuffmanTree>* remove (const HuffmanTree &, std::vector<HuffmanTree> *);
  TreeNode* copyFrom (TreeNode*);
  static void writeHelper (std::ostream&, TreeNode*);
  TreeNode* readFromStream(std::istream&);
  void getFromTree(TreeNode*, std::string&, unsigned char&);
  void traverse(std::string, std::string&);
  std::string strPrint(TreeNode*);
  TreeNode *root;

public:
  HuffmanTree();
  HuffmanTree(FrequencyTable);
  HuffmanTree(int, char);
  HuffmanTree(const HuffmanTree&);
  ~HuffmanTree();
  void print();
  void printLeaves();
  friend std::ostream& operator<< (std::ostream&, const HuffmanTree&);

  std::string decompress(const std::string&, const std::string&);
  void read(std::istream&);
  std::string compress (const std::string&);
};
std::ostream& operator<< (std::ostream&, const HuffmanTree&);
#include "map.h"
#endif
