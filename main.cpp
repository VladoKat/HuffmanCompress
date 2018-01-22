#include<iostream>
#include<fstream>
#include<string>

#include "frequency_table.cpp"
#include "huffman_tree.cpp"

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

void frequencyTableTest(){
  std::ifstream in;
  in.open("text.txt");
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
}
int main(){

  frequencyTableTest();
}
