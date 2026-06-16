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

using vl = vector<ull>;
using vvl = vector<vl>;

namespace srv = ranges::views;
namespace sr = ranges;
namespace sv = views;


auto hanoi(ull n, ll src, ll dst) -> void {
  if(n==0) return;

  ll new_dst = (dst+1)%3;
  if(new_dst == src) new_dst = (new_dst+1)%3;
//  cout << "n=" << n <<" src=" << src << " dst=" << dst << "\n";
  hanoi(n-1, src, new_dst);
  cout << src+1 << " " << dst+1 << "\n";
  hanoi(n-1, new_dst, dst);
}

int main(){
  string line;
  getline(cin, line);
  ull n = stoll(line);


  vl A{};
  A.reserve(n);
  auto nums = srv::iota(0ull, n+1) | srv::reverse;
  for(auto e: nums){
    A.push_back(e);
  }

  cout << (ull)pow(2, n)-1 << "\n";
  hanoi(n, 0, 2);
  
}
