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

auto hanoi(vector<vector<ll>>& T, ll from, ll to, ll temp, ll n, ll res, vector<ll>& dp) -> ll{
  println("dp: {}", dp);
  if (n==0){
    return 0;
  };
  if(dp[n] > 0){
    return dp[n];
  }
  

  res += hanoi(T, from, temp, to, n-1, 0, dp);
  auto nth = T[from].back();
  T[from].pop_back();
  T[to].push_back(nth);
  res += hanoi(T, temp, to, from, n-1, 0, dp);
  
  dp[n] = res +1;
  return res + 1;
}

int main(){
  ll disks = 6;

  auto A =  srv::reverse(srv::iota(0, disks)) | sr::to<vector<ll>>(); 
  vector<ll> B = vector<ll>();
  vector<ll> C = vector<ll>();
  auto T = vector{A,B,C};
  
  auto dp = srv::iota(0, disks+1) | srv::transform([](auto e){
      return 0;
      }) | sr::to<vector<ll>>();

  println("{}", dp);
  ll res = hanoi(T,0,2,1, A.size(), 0, dp);

  println("Result = {}", res);
  println("dp: {}", dp);
}
