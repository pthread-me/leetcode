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

const ull b = 1000 * 1000 * 1000;

auto solve(ull n) -> ull{
  vector<ull> nums{n};

  auto mul = [&](ull m){
    cout << m << "\n";
    ll carry = 0;
    for(ll i=0; i<nums.size() || carry; ++i){
      if(i == nums.size()){
        nums.push_back(0);
      }
      ll cur = carry + nums[i] * m;
      nums[i] = cur%b;
      carry = cur/b;
    } 
  };


  for(ll m = n-1; m>0; --m){
    mul(m);
  }
  
  ull res = 0;
  for(auto r: nums){
    if(r == 0) res += 4;
    else{
      for(ull i =10; i<b+1; i*=10){
        if(r%i == 0) res += 1;
        else break;
      }
      break;
    }
  }

  return res;
}

int main(){
  string line;
  getline(cin, line);

  ll n = stoll(line); 

  cout << solve(n);
}
