#include <algorithm>
#include <array>
#include <bits/stdc++.h>
#include <numeric>
#include <optional>
#include <print>
#include <ranges>
#include <string>
#include <string_view>
#include <tuple>
#include <unistd.h>
#include <vector>

using namespace std;
namespace srv = ranges::views;
namespace sr = ranges;
namespace sv = views;
using ll =  long long;

//-----------------------------------------------------------------------------
// Solution
//-----------------------------------------------------------------------------

auto can_sum(vector<ll>& nums, ll t, ll x) -> bool{
  auto diff = t - accumulate(nums.begin(), nums.end(), 0);

  if (diff<0) return false;
  if(diff % x == 0) return true;

  return false;
}

int main(){
  string line;
  getline(cin, line);
  ll t = stoll(line);
  
  for(auto _ : srv::iota(0, t)){
    getline(cin, line);
    auto param = line 
      | srv::split(' ')
      | srv::transform([](auto e){return string(string_view(e));})
      | srv::transform([](auto s){return stoll(s);})
      | sr::to<vector<ll>>();

    getline(cin, line);
    vector<ll> nums = line 
      | srv::split(' ') 
      | srv::transform([](auto rng){return string(string_view(rng));})
      | srv::transform([](string a){return stoll(a);})
      | sr::to<vector<ll>>();
  
    
    println("{}", can_sum(nums, param[1], param[2]) ? "YES" : "NO");
    }
}
