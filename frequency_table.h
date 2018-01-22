#ifndef FREQUENCYTABLE_H
#define FREQUENCYTABLE_H

#include <string>
#include <vector>

class HuffmanTree;

class FrequencyTable{
private:
  friend class HuffmanTree;
  struct pair {
    char symbol;
    int numOcc;

    pair(char _symbol, int _numOcc) : symbol(_symbol), numOcc(_numOcc){}
  };

  std::vector<pair> table;
public:
  FrequencyTable(std::string);
  void print();
};

#endif
