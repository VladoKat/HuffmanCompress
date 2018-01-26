#ifndef FREQUENCYTABLE_H
#define FREQUENCYTABLE_H

#include<map>

//class HuffmanTree;

class FrequencyTable{
private:
  std::map<unsigned char, int> table;
public:
  FrequencyTable();
  int& operator[] (unsigned char);
  void print();
  int size();
};

#endif
