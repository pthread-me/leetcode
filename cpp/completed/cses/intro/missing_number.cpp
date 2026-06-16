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


// recall xor identity, a xor a = 0, so by xoring all the elements in arr
// then xoring the result of all the elements 1..n, we get (1 x 3 x 4..) x (1 x 2 x 3 x 4 ...)
// each number will cancel itself except 2, which is the missing val
auto solve(vector<ll>& nums, ll n) -> ll{
  ll actual = accumulate(nums.begin(), nums.end(), 0, [](ll acc, ll e){
    return acc ^ e;
    });

  
  ll expected = 0;
  for(auto&& e: srv::iota(1, n+1)){
    expected ^= e;
  }

  return actual ^ expected;
}

int main(){
  string line;
  getline(cin, line);
  ll n = stoll(line);

  getline(cin, line);
  
  vector<ll> nums{};
  for(auto&& sub: line | srv::split(' ')){
    auto first = sr::begin(sub);
    auto last = sr::end(sub);
    auto d = sr::size(sub);

    const char* b = &*first;
    const char* e = &*first + d;
    int i{};
    auto [ptr, err] = from_chars(b, e, i, 10);

    if(err == errc::invalid_argument){
      cerr << "Invalid arg" << endl;
    }else if(err == errc::result_out_of_range){
      cerr << "too big" << endl;
    }else{
      nums.push_back(i);
    }
  }
  
  cout << solve(nums, n);

}
