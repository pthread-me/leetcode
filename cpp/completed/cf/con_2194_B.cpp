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

/*
 *
 * This question requires a greedy approach:
 *  First observe that since y <= x any transfer beyond the minimum will either
 *  reduce the total or leave it unchanged.
 *
 *  For each position, i, we need to find the maximum number we can make it be
 *  which is just the number of transfers from all other positions j*y.
 *
 *  We calculate the number of transfers T[i] = B[i]/x
 *  Given the total over all pos in B, we have T[i] = Total - B[i]
 *
 *  Then its just a "find the max value we can get from B[i] + (All T[j], j!=i)*y"
 *  */


auto solve(ll x, ll y, vector<ll>& nums) -> ll{
  auto max_transfers = nums 
    | srv::transform([&](auto e){return e/x;})
    | sr::to<vector<ll>>(); 
  ll t_sum = accumulate(max_transfers.begin(), max_transfers.end(), 0);
  
  auto totals = srv::zip_transform([&](ll val, ll cur_lim){
        return val + (t_sum-cur_lim)*y; 
        }, 
        nums, max_transfers)
    | sr::to<vector<ll>>();



  return *sr::max_element(totals);
}

int main(){
  string line;
  getline(cin, line);
  ll inputs = stoll(line);

  for (auto _ : srv::iota(0, inputs)){
    getline(cin, line); 
    auto params = line 
      | sv::split(' ')
      | sr::to<vector<string>>()
      | srv::transform([](auto e){return stoll(e);})
      | sr::to<vector<ll>>()
      | srv::drop(1)
      | srv::take(2);
    

    getline(cin, line);
    auto nums = line 
      | sv::split(' ') 
      | sr::to<vector<string>>() 
      | srv::transform([](auto e){return stoll(e);})
      | sr::to<vector<ll>>();

    println("{}", solve(params[0], params[1], nums));
  }
}
