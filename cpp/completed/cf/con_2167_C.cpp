#include <algorithm>
#include <array>
#include <bits/stdc++.h>
#include <numeric>
#include <optional>
#include <print>
#include <ranges>
#include <string>
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


auto solve(vector<ll>& nums) -> void{
  if (sr::any_of(nums, [](auto e){return e%2 == 0;}) 
      && sr::any_of(nums, [](auto e){return e%2 != 0;})){
    sort(nums.begin(), nums.end());
  }
}

int main(){
  string line;
  getline(cin, line);
  ll inputs = stoll(line);


  for (auto _ : srv::iota(0, inputs)){
    getline(cin, line); // ignored
    getline(cin, line);
    auto nums = line 
      | sv::split(' ') 
      | sr::to<vector<string>>() 
      | srv::transform([](auto e){return stoll(e);})
      | sr::to<vector<ll>>();

    solve(nums);
    sr::for_each_n(nums.begin(), nums.size()-1, [](auto e){
      print("{} ", e);
    });
    println("{}", *(nums.cend()-1));
  }
}
