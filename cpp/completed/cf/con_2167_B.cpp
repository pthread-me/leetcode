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

auto solve(vector<string>& names) -> bool{
  auto src = names[0]; 
  auto dst = names[1]; 
  auto universe = array<ll, 26>(); 

  sr::for_each(src, [&universe](char c ){
      ll index = static_cast<ll>(c) - 97;
      universe[index] ++;
  });
  sr::for_each(dst, [&universe](char c){
      ll index = static_cast<ll>(c) - 97;
      universe[index] --;
  }); 
  
  return all_of(universe.begin(), universe.end(), [](auto e){return e == 0;});
}

int main(){
  string line;
  getline(cin, line);
  ll inputs = stoll(line);


  for (auto _ : srv::iota(0, inputs)){
    getline(cin, line); // ignored
    getline(cin, line);
    auto names = line | sv::split(' ') | sr::to<vector<string>>();
    println("{}", solve(names) ? "YES" : "NO");
  }
}
