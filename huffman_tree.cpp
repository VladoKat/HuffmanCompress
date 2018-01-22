#include "huffman_tree.h"
#include<vector>



HuffmanTree::TreeNode::~TreeNode(){
  if(left)
  delete left;
  if(right)
  delete right;
}

HuffmanTree::~HuffmanTree(){
  if(root)
  delete root;
}
HuffmanTree::HuffmanTree():root(nullptr){}

void HuffmanTree::printHelper(TreeNode* curr){
  if(curr){
    std::cout << curr->symbol << " - " << curr->numOcc << "  ";
    printHelper(curr->left);
    printHelper(curr->right);
  }
}
void HuffmanTree::print(){
  printHelper(root);
  std::cout << "\n";
}

void HuffmanTree::printLeavesHelper(TreeNode* curr){
  if(curr && !curr->left && !curr->right){
    std::cout << curr->symbol << " - " << curr->numOcc << "\n";
  }
  if(!curr){
    return;
  }
  printLeavesHelper(curr->left);
  printLeavesHelper(curr->right);
}
void HuffmanTree::printLeaves(){
  printLeavesHelper(root);
  std::cout << "\n";
}
HuffmanTree::TreeNode* HuffmanTree::copyFrom(TreeNode* crr){
  if(!crr){
    return nullptr;
  }
  return new HuffmanTree::TreeNode(crr->numOcc, crr->symbol,
                      copyFrom(crr->left), copyFrom(crr->right));
}
HuffmanTree::HuffmanTree(const HuffmanTree& other){
  root = copyFrom(other.root);
}

HuffmanTree::HuffmanTree(int numOcc, char symbol) {
  root = new HuffmanTree::TreeNode(numOcc, symbol);
}

HuffmanTree HuffmanTree::findMin(std::vector<HuffmanTree*> trees){
  //std::cout << "findingMIn\n";
  int min = trees[0]->root->numOcc;
  HuffmanTree* minTree = trees[0];
  for(HuffmanTree* tree : trees){
    if(tree->root->numOcc < min){
      min = tree->root->numOcc;
      minTree = tree;
    }
  }
  return *minTree;
}

void HuffmanTree::remove(std::vector<HuffmanTree*>& trees, const HuffmanTree& toRemove){
  std::vector<HuffmanTree*> result;
  for(HuffmanTree* tree : trees){
    if(!(tree->root->numOcc == toRemove.root->numOcc &&
       tree->root->symbol == toRemove.root->symbol)){
         result.push_back(tree);
    } else {
      delete tree;
    }
  }
  trees = result;
}

void HuffmanTree::makeTree(std::vector<HuffmanTree*>& trees){
  if(trees.size() == 1){
    return;
  }
  HuffmanTree min1 = findMin(trees);
  HuffmanTree::remove(trees, min1);
  HuffmanTree min2 = findMin(trees);
  HuffmanTree::remove(trees, min2);
//  std::cout << "removed\n";
  //creating new tree
  HuffmanTree* toPush = new HuffmanTree(min1.root->numOcc + min2.root->numOcc,min1.root->symbol);
  toPush->root->left = copyFrom(min1.root);
  toPush->root->right = copyFrom(min2.root);
  //end of creating new tree
  trees.push_back(toPush);
  // for(int i = 0 ; i < trees.size(); i++){
  //   trees[i]->print();
  // }
  // std::cout << "\n\n";
  makeTree(trees);
}

HuffmanTree::HuffmanTree(FrequencyTable table){
  std::vector<HuffmanTree*> trees;
  for(int i = 0; i < table.table.size(); i++){
    trees.push_back(new HuffmanTree(table.table[i].numOcc, table.table[i].symbol)) ;
  }
  makeTree(trees);
  root = copyFrom(trees[0]->root);
  //trees[0]->printLeaves();
}
