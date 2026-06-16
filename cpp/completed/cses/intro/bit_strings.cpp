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

using vs = vector<string>;
using vl = vector<ll>;
using vvl = vector<vector<ll>>;

namespace srv = ranges::views;
namespace sr = ranges;
namespace sv = views;


auto solve(ull n) -> ull {
  ull const base = 2;
  ull res = base;
  ull mod = 1000000000 + 7;

  for (ull i=0; i<n; ++i){
    res = (res * base) % (mod); 
  }

  return res;
}

int main(){
  string line;
  getline(cin, line);

  ll n = stoll(line); 

  cout << solve(n-1);
}
