#include "RandomSet.hpp"
#include <algorithm>


using rs = RandomSet;

rs::RandomSet(){
  engine = std::default_random_engine();  
  dist = std::uniform_int_distribution(0, 10000);
  
  set = std::unordered_set<int>();
  hasher = set.hash_function();
  keys = std::vector<size_t>();
}

bool rs::insert(int val){
  if(set.contains(val)){
    return false;
  }

  set.insert(val);
  keys.push_back(hasher(val));

  return true;
}


bool rs::remove(int val){
  if(!set.contains(val)){
    return true;
  }

  set.erase(val);
  auto e = std::find(keys.begin(), keys.end(), val);
  keys.erase(e);

  return true;
}


int rs::getRandom(int val){
  
}
