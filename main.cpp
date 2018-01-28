#include<iostream>
#include<fstream>
#include<string>
#include<stack>

#include "frequency_table.cpp"
#include "huffman_tree.cpp"
#include "map.cpp"


void compress(std::string fileToComp = "text3.txt", std::string compressedFile = "compressed.txt"){
  std::ifstream in;
  in.open(fileToComp, std::ios::binary);
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
  HuffmanTree tree(table);
  std::string compressed = tree.compress(myString);
  std::ofstream out;
  out.open(compressedFile, std::ios::binary);
  for(unsigned char el : compressed){
    out << el;
  }
  out.close();
}

void  decompress(std::string fileToDec = "compressed.txt", std::string resultFile = "result.txt") {
  std::ifstream input;
  input.open(fileToDec , std::ios::binary);
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
  std::ofstream output;
  output.open(resultFile, std::ios::binary);
  output << decompressed;
  output.close();
}

void UI(){
  std::string command;
  std::getline(std::cin, command);
  int compressPos = command.find("-c ");
  int decompressPos = command.find("-d ");
  bool isCompress = compressPos != std::string::npos;
  bool isDecompress = decompressPos != std::string::npos;
  std::string inputFile;
  std::string outputFile;
  int inputFilePos = command.find("-i ");
  int outputFilePos = command.find("-o ");
  bool foundInput = false;
  bool foundOutput = false;

  if(inputFilePos != std::string::npos){
    foundInput = true;
    inputFilePos += 3;
    int i = inputFilePos;
    while(command[i] != ' ' && command.size()){
      inputFile.push_back(command[i]);
      i++;
    }
  }
  if(foundInput && outputFilePos != std::string::npos){
      foundOutput = true;
      outputFilePos+=3;
      int i = outputFilePos;
      while(command[i] != ' ' && i < command.size()){
        outputFile.push_back(command[i]);
        i++;
      }
  }

  if(!foundInput){
    std::cout << "No file to do smth with\n";
  } else {
    if(!foundOutput){
      if(isCompress){
        compress(inputFile);
      } else if (isDecompress){
        decompress(inputFile);
      } else {
        std::cout << "No mode pointed to work with\n";
      }
    } else {
      if(isCompress){
        compress(inputFile, outputFile);
      } else if (isDecompress){
        decompress(inputFile, outputFile);
      } else {
        std::cout << "No mode pointed to work with\n";
      }
    }
  }
}


int main(){
  UI();
  //compress();
  //decompress();
}
