#include <algorithm>
#include <bitset>
#include <cstring>
#include <format>
#include <bits/stdc++.h>
#include <charconv>
#include <iostream>
#include <iterator>
#include <numeric>
#include <ranges>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;
using ll =  long long;
using ull =  unsigned long long;

using us = unordered_set<string>;
using um = unordered_map<char, ull>;
using vl = vector<ull>;
using vvl = vector<vl>;

namespace srv = ranges::views;
namespace sr = ranges;
namespace sv = views;


/*
 *  Finding the string is easy, just like how we do permutations but keep a set
 *  to see which we already added.
 *
 *  To find the count first: we know that all possible permutations is n!
 *  since some characters are repeated we have their count! possible instances
 *  which are the same, so for every count c_i
 *
 *  k = n!/c_i! for all i in the Alphabet
 *
 *
 */

auto solve(string& s, string& temp, us& set) -> void {
  if(temp.size()==s.size() && !set.contains(temp)){
    cout << temp << "\n"; 
    set.insert(temp);
    return;
  }

  
  for(ull i=0; i<s.size(); ++i){
    if(s[i] == '$') continue;
    char cur = s[i];

    s[i] = '$';

    temp.append(string{cur});
    solve(s, temp, set);
    temp.pop_back();
    s[i] = cur;
  }

}

int main(){
  
  string line;
  getline(cin, line);

  ull n = line.size();
  um count{};
  for(auto e: line){
    count[e] = count[e] + 1;
  }

  ull r = count.size();

  auto factorial = [](ull n) -> ull {
    ull res = 1;
    for(auto e: srv::iota(1ull, n+1)){
      res *= e;
    }
    return res;
  };

  ull all_posible = factorial(n);
  ull repeated = 1;
  for(auto [k, v]: count){
    repeated *= factorial(v);
  }

  cout << all_posible/repeated << "\n";
  
  string temp{};
  us set{};

  // The sort is because the cses judge is dogshit and expects it to be assending
  sort(line.begin(), line.end());
  solve(line,temp, set);
  
}
