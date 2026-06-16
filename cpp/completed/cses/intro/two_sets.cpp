#include <algorithm>
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

using vs = vector<string>;
using vl = vector<ll>;
using vvl = vector<vector<ll>>;

namespace srv = ranges::views;
namespace sr = ranges;
namespace sv = views;

auto solve(ull n) -> void {
  ull S = n*(n+1)/2; 
  if(S %2 == 1){
    cout << "NO\n";
    return;
  }

  ull target = S/2;
  ull cur = 0;

  vector<ull> v1{};
  vector<ull> v2{};

  for(auto&& e: srv::iota(1ull, n+1) | sv::reverse){
    if(cur+e <= target){
      v1.push_back(e);
      cur += e;
    }else{
      v2.push_back(e);
    }
  }

  cout << "YES\n";
  cout << v1.size() << "\n";
  cout << v1[0];
  for(auto&& it = next(v1.begin()); it != v1.end(); ++it){
    cout << " " << *it;
  }
  cout << "\n";


  cout << v2.size() << "\n";
  cout << v2[0];
  for(auto&& it = next(v2.begin()); it != v2.end(); ++it){
    cout << " " << *it;
  }
  cout << "\n";
}




int main(){
  string line;
  getline(cin, line);
  ll n = stoll(line);
  
  solve(n);
}
