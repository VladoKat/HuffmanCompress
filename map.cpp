#include "map.h"
#include<cstring>
//#include<pair>
//#include<cmath>

void Map::fillHelper(HuffmanTree::TreeNode* curr, std::string label){
  if(curr && !curr->left && !curr->right){
    table.insert(std::pair<char, std::string>(curr->symbol, label));
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
  return table[symbol];
}



// void Map::print() {
//   std::cout << "size = " << table.size() << "\n";
//   for(int i = 0 ; i < table.size(); i++){
//     std::cout << table[i].symbol << " - " << table[i].label << "\n";
//   }
//   std::cout << "\n";
// }
