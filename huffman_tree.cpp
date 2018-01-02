#include "huffman_tree.h"
#include<vector>

HuffmanTree::HuffmanTree(int rootNumOcc, char rootSymbol){
  root = new TreeNode (rootNumOcc, rootSymbol);
}
HuffmanTree::HuffmanTree(FrequencyTable freqTable){
  std::vector<HuffmanTree> *trees = new std::vector<HuffmanTree>;

  //filling trees with 1-root trees;
  for(int i = 0; i < (*(freqTable.table)).size(); i++){
    (*trees).push_back(HuffmanTree((*(freqTable.table))[i].second, (*(freqTable.table))[i].first));
    //std::cout << (*trees)[i].root -> numOcc << " " << (*trees)[i].root -> symbol << "\n";
  }

  // TODO: copy constructor !!
  HuffmanTree min = (*trees)[0];
  for(int i = 0; i < trees->size(); i ++){
    if(min > (*(freqTable.table))[i].numOcc) {
      min = (*(freqTable.table))[i].numOcc;
    }
  }
  std::vector<HuffmanTree>::iterator newEnd = std::remove((*trees).begin(),
                                                   (*trees).end(),
                                                   min);
  (*(trees)).erase(newEnd, (*trees).end());



  FrequencyTable::pair secondMin = (*(trees))[0];
  for(int i = 0; i < (*(trees)).size(); i++){
    if(secondMin > (*(trees))[i].numOcc) {
      secondMin = (*(trees))[i].numOcc;
    }
  }

  std::vector<pair>::iterator newEnd = std::remove((*(trees)).begin(),
                                                   (*(trees)).end(),
                                                   secondMin);
  (*(trees)).erase(newEnd, (*(trees)).end());




}
