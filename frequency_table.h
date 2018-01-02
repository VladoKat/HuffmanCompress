#ifndef FREQUENCYTABLE_H
#define FREQUENCYTABLE_H

#include <string>
#include <vector>

class FrequencyTable{
private:
  struct pair {
    char first;
    int second;

    pair(char _first, int _second) : first(_first), second(_second){}
  };

  std::vector<pair> *table;
public:
  FrequencyTable(std::string);
  void print();
};

#endif
