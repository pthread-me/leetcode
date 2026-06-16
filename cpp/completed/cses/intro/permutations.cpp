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


int main(){
  string line;
  getline(cin, line);
  ll n = stoll(line);
  
  if(n == 1){
    cout << 1 << endl;
    return 0;
  } else if(n<4){
    cout << "NO SOLUTION";
    return 0;
  }


  vector<ll> res{};
  res.reserve(n);

  for(ll e=2; e<=n; e+=2){
    res.push_back(e);
  }
  for(ll e=1; e<=n; e+=2){
    res.push_back(e);
  }
  
  
  cout << res[0];
  for_each(res.begin()+1, res.end(), [](auto e){
    cout << " " << e;
  });
  
  cout << endl;
}
