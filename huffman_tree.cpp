#include "huffman_tree.h"
#include<vector>

HuffmanTree::HuffmanTree(int rootNumOcc, char rootSymbol){
  root = new TreeNode (rootNumOcc, rootSymbol);
}

HuffmanTree::TreeNode::TreeNode(const TreeNode& other){
  this->numOcc = other.numOcc;
  symbol = other.symbol;
  left = other.left;
  right = other.right;
}

HuffmanTree::TreeNode::~TreeNode(){
  delete left;
  delete right;
}
HuffmanTree::HuffmanTree(const HuffmanTree &left, const HuffmanTree &right){
  root = new HuffmanTree::TreeNode(left.root->numOcc + right.root->numOcc, left.root->symbol);
  root->left = new HuffmanTree::TreeNode(*(left.root));
  root->right = new HuffmanTree::TreeNode(*(right.root));
}

HuffmanTree::HuffmanTree(const HuffmanTree& other){
  root = new HuffmanTree::TreeNode(*(other.root));
}

HuffmanTree::~HuffmanTree(){
  delete root;
}

HuffmanTree HuffmanTree::operator= (const HuffmanTree& other){
  if (this != &other){
      root = new HuffmanTree::TreeNode(*(other.root));
  }
  return *this;
}

std::vector<HuffmanTree>* HuffmanTree::remove (const HuffmanTree &el, std::vector<HuffmanTree> *all){
  std::cout << "1.Remove starts with size " << all->size() << "\n";
  int index = 0;
  bool found = false;
  for(int i = 0; i < all->size() && !found; i++){
    if(el.root->symbol == (*all)[i].root->symbol && el.root->numOcc == (*all)[i].root->numOcc){
      found = true;
      index = i;
    }
  }
  if(found){
    std::cout <<"2.Element found - " << (*all)[index].root->symbol << " " << (*all)[index].root->numOcc << " at " << index << "\n";
  }
  std::vector <HuffmanTree> buffer;
  for (int i = 0; i < all->size(); i++){
    if(i != index ){
      std::cout << "3." << i << "pushed into buffer\n";
      buffer.push_back((*all)[i]);
    }
  }
  *all = buffer;
  return all;

}
HuffmanTree::HuffmanTree(FrequencyTable freqTable){
  std::vector<HuffmanTree> *trees = new std::vector<HuffmanTree>;

  //-------------------filling trees with 1-root trees;
  for(int i = 0; i < (*(freqTable.table)).size(); i++){
    (*trees).push_back(HuffmanTree((*(freqTable.table))[i].numOcc, (*(freqTable.table))[i].symbol));
    //std::cout << (*trees)[i].root -> numOcc << " " << (*trees)[i].root -> symbol << "\n";
  }
  for(int i = 0; i < trees->size(); i++){
    std::cout << (*trees)[i].root -> numOcc << " " << (*trees)[i].root -> symbol << "\n";
  }

  while (trees -> size() > 2){
    HuffmanTree min = (*trees)[0];
    for (int i = 0; i < trees->size(); i++){
      if(min.root->numOcc > (*trees)[i].root->numOcc){
        std::cout << "FINDING AN ELEMENT\n";
        min = (*trees)[i];
      }
    }
    trees = HuffmanTree::remove(min, trees);
    for(int i = 0; i < trees->size(); i++){
      std::cout << (*trees)[i].root -> numOcc << " " << (*trees)[i].root -> symbol << "\n";
    }
    std::cout << "\n";




    HuffmanTree secondMin = (*trees)[0];
    for (int i = 0; i < trees->size(); i++){
      if(secondMin.root->numOcc > (*trees)[i].root->numOcc){
        std::cout << "FINDING AN ELEMENT\n";
        secondMin = (*trees)[i];
      }
    }
    trees = HuffmanTree::remove(secondMin, trees);
    for(int i = 0; i < trees->size(); i++){
      std::cout << (*trees)[i].root -> numOcc << " " << (*trees)[i].root -> symbol << "\n";
    }
    std::cout << "\n";



    trees->push_back(HuffmanTree(min, secondMin));

    for(int i = 0; i < trees->size(); i++){
      std::cout << (*trees)[i].root -> numOcc << " " << (*trees)[i].root -> symbol << "\n";
    }
    std::cout << "\n";

  }
}
