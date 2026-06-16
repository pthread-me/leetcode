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


/*
 * the number of trailing 0s is = to the number of 5*2 in the prime factors
 * of n!. since the # of 2s will always be <= 5s in the factors we can
 * only count the number of 5s. To do that we calculate the multiples of 5
 * until N
 *
 */
auto solve(ull n) -> ull {
  ull cur = n;
  ull res = 0;

  while(cur > 0){
    res += cur/5;
    cur /= 5;
  }

  return res;
}

int main(){
  string line;
  getline(cin, line);

  ll n = stoll(line); 

  cout << solve(n);
}
