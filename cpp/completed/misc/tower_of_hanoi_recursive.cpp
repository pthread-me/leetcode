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


auto print_tower(vector<vector<ll>>& T){
  auto A = T[0];
  auto B = T[1];
  auto C = T[2];
  auto max_len = max(A.size(), max(B.size(), C.size())) - 1;

  for(ll i = max_len; i>-1; i--){
    if(i<A.size()){
      print("{:1}{:5}", A[i], "");
    }else{
      print("{:6}", "");
    }
    if(i<B.size()){
      print("{:1}{:5}", B[i], "");
    }else{
      print("{:6}", "");
    }
    if(i<C.size()){
      print("{:1}{:5}", C[i], "");
    }else{
      print("{:6}", "");
    }
    println();
  }
    println("A{:5}B{:5}C{:5}", "", "", "");
    println();
}



auto hanoi(vector<vector<ll>>& T, ll from, ll to, ll temp, ll n, ll res) -> ll{

  if (n==0){
    return res;
  };

  res += hanoi(T, from, temp, to, n-1, 0);
  println("n: {}, val: {}, From: {}, To: {}", n, T[from].back(), from, to);
  print_tower(T);
  auto nth = T[from].back();
  T[from].pop_back();
  T[to].push_back(nth);
  res += hanoi(T, temp, to, from, n-1, 1);
  return res;
}

int main(){
  /*
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
  */

  vector<ll> A{6,5,4,3,2,1};
  vector<ll> B = vector<ll>();
  vector<ll> C = vector<ll>();
  auto T = vector{A,B,C};

  auto res = hanoi(T,0,2,1, A.size(), 0);
  print_tower(T);

  println("Result = {}", res);
}
