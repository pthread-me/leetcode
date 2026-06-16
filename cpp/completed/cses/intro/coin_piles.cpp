#include <algorithm>
#include <format>
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


/*
 * If the diff between i,j > j then its not solvable.
 * we reduce the values of i,j until they are either equal or are 2,1 or 1,2
 * if they are equal and are divisible by 3 then its clearly correct
 */
auto solve(ull a, ull b) -> void {
  ull i = max(a, b);
  ull j = min(a, b);

  if(i-j > j){
    cout << "NO\n";
    return;
  }

  ull diff = i-j;
  i = i-2*diff;
  j = j-diff;

  if(i == j && i%3==0){
    cout << "YES\n";
  }else if(max(i,j)/min(i,j) == 2){
    cout << "YES\n";
  }else{
    cout << "NO\n";
  }
}

int main(){
  string line;
  getline(cin, line);

  ull n = stoll(line); 

  for (auto _: srv::iota(0ull, n)){
    getline(cin, line);
    vector<ull> vals{};
    vals.reserve(2);


    for(auto sub: line | srv::split(' ')){
      auto b = &*sub.begin();
      auto e = &*sub.end();

      ull val;
      auto [ptr, err] = from_chars(b, e, val);
      if(err == errc::invalid_argument){
        cout << "not a valid number\n";
        return 1;
      }else if(err == errc::result_out_of_range){
        cout << "partially invalid";
        return 1;
      }
      vals.push_back(val);
    }

    solve(vals[0], vals[1]);

  }

}
