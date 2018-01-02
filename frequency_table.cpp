#include "frequency_table.h"

FrequencyTable::FrequencyTable(std::string str){
  table = new std::vector<pair>;
  for(int i = 0; i < str.size(); i++){
    char current = str[i];
    bool exists = false;
    for(int j = 0; j < table->size(); j++){
      if(current == (*table)[j].first){
        exists = true;
        (*table)[j].second++;
      }
    }
    if(!exists){
      (*table).push_back(pair(current, 1));
    }
  }
}

void FrequencyTable::print(){
  for(int i = 0; i < (*table).size(); i++){
    std::cout << (*table)[i].first << " - " << (*table)[i].second << "\n";
  }
}
