#include <algorithm>
#include <bitset>
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


auto solve(ull n) -> void {
  auto to_bits = [&n] (ull c) -> void {
    string s = string(n, '0');
    if(c==0){
      cout << s << "\n";
      return;
    }

    ull i = 0;
    while(c>0){
      if(c%2 == 1){
        s[i] = '1';
      }
      c /= 2;
      ++i;
    }

    cout << s << "\n";
  };
  
  to_bits(0);
  for(ull i=1; i< pow(2, n); ++i){
    to_bits(i^(i>>1));
  }
}

int main(){
  string line;
  getline(cin, line);
  ull n = stoll(line);


  solve(n);
}
