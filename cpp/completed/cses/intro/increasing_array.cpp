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


auto solve(vector<ull>& nums) -> ull {
  ull cout = 0;
  for(auto&& l=nums.begin(), r = next(l); r != nums.end(); ++l, ++r){
    if(*l > *r){
      auto diff = (*l - *r); 
      *r = (*r) + diff;
      cout += diff;
    }
  }

  return cout;
}




int main(){
  string line;
  getline(cin, line);
  ll n = stoll(line);
  
  vector<ull> nums;

  getline(cin, line);

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
  
  cout << solve(nums);
}
