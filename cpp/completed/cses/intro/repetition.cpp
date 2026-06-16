#include <bits/stdc++.h>
#include <iostream>
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


// recall xor identity, a xor a = 0, so by xoring all the elements in arr
// then xoring the result of all the elements 1..n, we get (1 x 3 x 4..) x (1 x 2 x 3 x 4 ...)
// each number will cancel itself except 2, which is the missing val
auto solve(string& line) -> ll{
}

int main(){
  string line;
  getline(cin, line);

  getline(cin, line);
  
  srv::split(line);
}
