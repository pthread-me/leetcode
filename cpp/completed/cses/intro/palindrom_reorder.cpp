#include <algorithm>
#include <format>
#include <bits/stdc++.h>
#include <charconv>
#include <iostream>
#include <iterator>
#include <numeric>
#include <ranges>
#include <string>

using namespace std;
using ll =  long long;
using ull =  unsigned long long;

using um = unordered_map<char, ull>; 

namespace srv = ranges::views;
namespace sr = ranges;
namespace sv = views;


auto solve(string& s, um& map) -> void {
  ull odd_count = count_if(map.begin(), map.end(), [](auto&& p){
    return p.second %2 == 1;
    });

  if(s.size()%2 == 0 && odd_count>0 || s.size()%2==1 && odd_count>1){
    cout << "NO SOLUTION\n";
    return;
  }


  auto middle = find_if(map.begin(), map.end(), [](auto&& p)->bool{
    return p.second%2 == 1ull;
      });
  
  string res;
  if(middle == map.end()){
    res = ""; 
  }else{
    res= string{middle->first};
    map[middle->first] = map[middle->first]-1;
  }

  for(auto [c,v]: map | srv::filter([](auto&& p){return p.second > 1;})){
    string temp = string(v/2, c); 
    temp.append(res);
    temp.append(string(v/2, c));

    res = temp;
  }

  cout << res;

}

int main(){
  string line;
  getline(cin, line);
  
  um map{};

  for(char c: line){
    map[c] += 1;
  }
  solve(line, map);

}
