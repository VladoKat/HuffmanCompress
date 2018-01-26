#include "frequency_table.h"

FrequencyTable::FrequencyTable(){
  for(int i =0; i < 256; i++){
    table[i] = 0;
  }
}

int& FrequencyTable::operator[] (unsigned char symbol){
  return table[symbol];
}
void FrequencyTable::print(){
  for(int i = 0; i < table.size(); i++){
    if(table[i] > 0){
      std::cout << (unsigned char)i << " " << table[i];
    }
  }
  std::cout << "\n";
}
int FrequencyTable::size(){
  return table.size();
}
