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


// we are looking for 3x2 and 2x3 grids 
// observe that there are (n-3 + 1)*(n-2 + 1) = (n-2)*(n-1) such 3x2
// and (n-1)*(n-2) 2x3 grids 
// so: 2(n-2)(n-1) since each grid can have 2 different placements (switching the knights)
// we have 4(n-2)(n-1)
//
// The total number of possible possitions is the combination of all the n*n positions
// so: (n^2)C2 = (n^2)!/2!(n^2-2)! = n^2(n^2-1)/2
auto solve(ll last) -> void { 

  for(ull n: srv::iota(1, last+1)){
    cout << ((n*n)*(n*n -1) / 2) - (4*(n-2)*(n-1)) << "\n";
  }
}

int main(){
  string line;
  getline(cin, line);
  ll n = stoll(line);
  solve(n);
}
