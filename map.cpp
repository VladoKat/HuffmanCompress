#include "map.h"
#include<cstring>
//#include<cmath>

void Map::fillHelper(HuffmanTree::TreeNode* curr, std::string label){
  if(curr && !curr->left && !curr->right){
    table.push_back(lspair(label, curr->symbol));
  }
  if(!curr){
    return;
  }
  fillHelper(curr->left, label+"0");
  fillHelper(curr->right, label+"1");
}

Map::Map(const HuffmanTree& tree){
  fillHelper(tree.root, "");
}

std::string Map::operator[] (char symbol){
  for(int i = 0; i < table.size(); i++){
    if(table[i].symbol == symbol){
      return table[i].label;
    }
  }
  return 0;
}



void Map::print() {
  std::cout << "size = " << table.size() << "\n";
  for(int i = 0 ; i < table.size(); i++){
    std::cout << table[i].symbol << " - " << table[i].label << "\n";
  }
  std::cout << "\n";
}
