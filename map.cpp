#include "map.h"
#include<cstring>
#include<cmath>

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

unsigned char convert(const std::string& str){
  unsigned char result;
  int exponent = str.length();
  for(int i = 0; i < exponent; i++){
    result += (str[i]-48)*pow(2, (exponent-i-1));
  }
  return result;
}
std::vector<unsigned char> Map::compress (const std::string& textToCompress){
  std::string result;
  for(int i = 0; i < textToCompress.size(); i++){
    result = result + (*this)[textToCompress[i]];
  }
  int index = 0;
  std::vector<unsigned char> realResult;
  do{
    std::cout << result.substr(index, 8) << " ";
    unsigned char num = convert(result.substr(index, 8));
    std::cout << num << "\n";
    index += 8;
    realResult.push_back(num);
  } while(index < result.size());

  return realResult;
}


void Map::print() {
  std::cout << "size = " << table.size() << "\n";
  for(int i = 0 ; i < table.size(); i++){
    std::cout << table[i].symbol << " - " << table[i].label << "\n";
  }
  std::cout << "\n";
}
