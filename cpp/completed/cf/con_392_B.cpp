#include <algorithm>
#include <array>
#include <bits/stdc++.h>
#include <numeric>
#include <optional>
#include <print>
#include <ranges>
#include <string>
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

/*
 *  This is an extension to the tower of hanoi where every move cost a specific 
 *  non negative amount, a 3x3 grid has the costs. 
 *
 *  We only deal with the case of moving a single disk (in this case the actual
 *  nth disk and the n-1 disks that we treat as a single block). 
 *  Recurrsing on the two paths and taking the min.
 *
 *  DP is via memoization on (n, from, to) -> total cost 
 */


auto hanoi(vector<vector<ll>>const & cost, ll n, ll from, ll to, ll temp, map<tuple<ll,ll,ll>,ll>& dp) -> ll{
  if(n == 1){
   return min(cost[from][to], cost[from][temp] + cost[temp][to]);
  }
 
  auto target = make_tuple(n, from, to);
  if(dp.contains(target)){
    return dp[target]; 
  }

  ll r1 = 0;
  ll r2 = 0;
  r1 =  (hanoi(cost, n-1, from, temp, to, dp)
          + cost[from][to]
          + hanoi(cost, n-1, temp, to, from, dp));

  r2 = (hanoi(cost, n-1, from, to, temp, dp)
        + cost[from][temp]
        + hanoi(cost, n-1, to, from, temp, dp)
        + cost[temp][to]
        + hanoi(cost, n-1, from, to, temp, dp));
  
  dp[target] = min(r1, r2);
  return min(r1, r2); 
}


int main(){
  string line;
  auto cost = vector<vector<ll>>();

  for (auto _ : srv::iota(0, 3)){
    getline(cin, line); 
    cost.push_back(line 
      | sv::split(' ')
      | sr::to<vector<string>>()
      | srv::transform([](auto e){return stoll(e);})
      | sr::to<vector<ll>>()
    );
  }

  getline(cin, line);
  ll n(stoll(line)); 
  auto dp = map<tuple<ll, ll, ll>, ll>();

  auto res = hanoi(cost, n, 0, 2, 1, dp);
  println("{}", res);


}
