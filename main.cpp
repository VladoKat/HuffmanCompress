#include<iostream>
#include<fstream>
#include<string>
#include<stack>

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
  in.open("text3.txt", std::ios::binary);
  std::string myString;
  FrequencyTable table;
  char symb;
  bool eof = false;
  while (!eof){
    in.get(symb);
    if(in.eof()){
      eof = true;
    } else {
      table[symb]++;
      myString.push_back(symb);
    }
  }
  in.close();
  std::cout << myString << "\n";

  table.print();
  std::cout << "\n";
  HuffmanTree tree(table);
  tree.printLeaves();
  //Map map(tree);
  //map.print();
  std::string compressed = tree.compress(myString);
  std::ofstream out;
  out.open("compressed.txt", std::ios::binary);
  //out << tree;
  for(unsigned char el : compressed){
    out << el;
  }
  out.close();
}

void  decompress() {
  std::ifstream input;
  input.open("compressed.txt", std::ios::binary);
  HuffmanTree tree = HuffmanTree();
  std::string lastBins;
  unsigned char someChar = '0';
  while(someChar == '0' || someChar == '1'){
    someChar = input.peek();
    if(someChar == '0' || someChar == '1'){
        lastBins.push_back(someChar);
        input >> someChar;
    } else {
      someChar = 0;
    }
  }
  tree.read(input);
  tree.print();
  std::string textToDecompress, temp;
  bool eof = input.eof();
  while(!eof){
    std::getline(input, temp);
    textToDecompress = textToDecompress + temp;
    if(input.eof()){
      eof = true;
    }
  }
  input.close();
  std::string decompressed = tree.decompress(textToDecompress, lastBins);
  //std::cout << decompressed << " - result\n";
  std::ofstream output;
  output.open("result.txt", std::ios::binary);
  output << decompressed;
  output.close();
}

std::string reconvert2(unsigned char symbol){
  std::string result;
  std::stack<unsigned char> buffer;
  unsigned char toPush;
  while(symbol > 0){
    toPush = symbol % 2 + 48;
    symbol /= 2;
    buffer.push(toPush);
  }
  while(!buffer.empty()){
    result.push_back(buffer.top());
    buffer.pop();
  }
  return result;
}
int main(){
  compress();
  decompress();
  // std::string str = "a";
  // std::cout << str.substr(1, 2) << " - ";
 //std::cout << reconvert2('g') << "\n";
// std::ifstream input;
// input.open("compressed.txt", std::ios::binary);
// HuffmanTree tree = HuffmanTree();
// tree.read(input);
// tree.print();
  //std::cout << convert2("01101110") << " " << convert2("10001010") << " " << convert2("1101110") << "\n";

  //std::cout << std::to_string(42) << "\n";
}
