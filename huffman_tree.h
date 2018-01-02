#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include "frequency_table.h"

class HuffmanTree {
private:
  struct TreeNode {
    int numOcc;
    char symbol;
    *TreeNode left;
    *TreeNode right;

    TreeNode(int _numOcc, char _symbol) : symbol(_symbol),
                                          numOcc(_numOcc),
                                          left(nullptr),
                                          right(nullptr) {}
  };

  TreeNode *root;

public:
  //HuffmanTree() : root(nullptr);
  HuffmanTree(FrequencyTable);
  

};


#endif
