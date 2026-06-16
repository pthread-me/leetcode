#include <bits/stdc++.h>
#include <iostream>
#include <numeric>
#include <queue>
#include <utility>

using namespace std;
using ll =  long long;
using ull =  unsigned long long;

using vs = vector<string>;
using vl = vector<ll>;
using vvl = vector<vector<ll>>;

namespace srv = ranges::views;
namespace sr = ranges;
namespace sv = views;

auto solve(vvl& A, ll n) -> void {
  auto q = queue<pair<ll, ll>>(); 
  q.push(make_pair(0, 0));
  
  array<ll,8> dx = {-1, -1, 1, 1, -2, -2, 2, 2};
  array<ll,8> dy = {-2, 2, -2, 2, -1, 1, -1, 1};

  auto knight_move = [&](pair<ll,ll> p) -> vector<pair<ll,ll>>{
    vector<pair<ll,ll>> res; res.reserve(8);
    for(auto i: srv::iota(0, 8)){
      if(-1<p.first+dx[i] && p.first+dx[i]<n && -1<p.second+dy[i] && p.second+dy[i]<n){
        res.push_back(make_pair(p.first+dx[i], p.second+dy[i]));    
      }
    }
    return res;
  };

  while(!q.empty()){
    auto cur = q.front();
    q.pop();
    for(auto p: knight_move(cur)){
      if(A[p.first][p.second] == -1){
        A[p.first][p.second] = A[cur.first][cur.second] +1;
        q.push(p);
      }
    }
  }
}



int main(){
  string line;
  getline(cin, line);
  ll n = stoll(line);

  auto A = vvl(n, vl(n, -1));
  A[0][0] = 0; 

  solve(A, n);

  for(auto r: A){
    cout << r[0];
    for(auto i: srv::iota(1, n)){
      cout << " " << r[i];
    }
    cout << "\n";
  }
}
