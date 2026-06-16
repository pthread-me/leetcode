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

auto solve(ull y, ull x) -> ull {
  ull m = max(y, x);
  if(m+1 == 1) return 1;

  ull prev_dim = (m) * (m);
  ull offset{};
  bool down_left = true;
  
  if(m%2 == 0) down_left = false;

  if(down_left){
    offset = y + (m - x);
  }else{
    offset = x + (m - y);
  }

  return prev_dim + offset + 1;
}




int main(){
  string line;
  getline(cin, line);
  ll n = stoll(line);
  

  for(auto _ : srv::iota(0ll, n)){
    getline(cin, line);
    vector<ull> nums{};
    for(auto&& sub: srv::split(line, ' ')){
       char* b = &(*sr::begin(sub));
       char* e = &(*sr::end(sub));
       ull i;
       auto [ptr, err] = from_chars(b, e, i);

       if(err == errc::invalid_argument){
        cout << "invalid arg" << endl; return 1;
       }else if (err == errc::result_out_of_range){
        cout << "parly invalid" << endl; return 1;
       }
       nums.push_back(i);
    }

    cout << solve(nums[0]-1, nums[1]-1) << endl;
  }
  
  
}
