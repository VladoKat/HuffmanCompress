#include<iostream>
#include<fstream>
#include<string>

#include "frequency_table.cpp"
#include "huffman_tree.cpp"
#include "map.cpp"

// void fullTest(){
//   std::ifstream in;
//   in.open("text.txt");
//   std::string myString;
//   std::string line;
//   while (getline (in,line)){
//     myString += line;
//   }
//   in.close();
//   std::cout << myString << "\n";
//
//   FrequencyTable table(myString);
//   HuffmanTree tree(table);
//   std::ofstream out;
//   out.open("compressed_" + name);
//   out << tree.getInfo();
//   out.close();
// }

void compress(){
  std::ifstream in;
  in.open("text.txt", std::ios::binary);
  std::string myString;
  std::string line;
  while (getline (in,line)){
    myString += line;
  }
  in.close();
  std::cout << myString << "\n";

  FrequencyTable table(myString);
  table.print();
  std::cout << "\n";
  HuffmanTree tree(table);
  tree.printLeaves();
  Map map(tree);
  map.print();
  std::vector<unsigned char> compressed = map.compress(myString);
  std::ofstream out;
  out.open("compressed.txt", std::ios::binary);
  out << tree;
  for(unsigned char el : compressed){
    out << el;
  }
  out.close();
}

int main(){
  compress();
  //std::cout << convert2("01101110") << " " << convert2("10001010") << " " << convert2("1101110") << "\n";

  //std::cout << std::to_string(42) << "\n";
}
