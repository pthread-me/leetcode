#include <algorithm>
#include <ranges>
#include <utility>
#include <utils.hpp>
#include <bits/stdc++.h>
#include <vector>

class Solution {
public:
  string longestPalindrome(string s) {
    auto pals = rsv::iota(0ull, s.length()) 
      | rsv::transform([](ll e){return pair<ll, ll>(e, e+1);})
      | rs::to<vector<pair<ll, ll>>>();
    

    auto evaluate = [&s, &pals](auto& p) -> bool{
      auto [i, j] = p;
      println("evauate {}", p);
      bool res;

      if(i==0 or j>=s.length() or s[i-1] != s[j]){
        res = false;
      }else{
        p = make_pair(i-1, j+1);
        res = true;
      }
      if (j-i == 1 and s[i] == s[j]){
        pals.push_back(make_pair(i, j+1));
      } 
      return res;

    }; 
    

    pair<ll, ll> max = make_pair(0, 0);
    while (pals.size() > 0){
      println("{}", pals);
      for (ll i = 0; i<pals.size() && pals.size()>0;){
        bool extended = evaluate(pals[i]);
        max = (max.second - max.first) < (pals[i].second - pals[i].first) ? pals[i] : max;

        if (!extended) {
          println("erased {}", pals[i]);
          erase(pals, pals[i]); 
          println("{}", pals);
          continue;
        }

        i++;
      } 
    }

    println("{}", max);
    return s.substr(max.first, max.second-max.first);
  }
};

int main(){
  auto s = Solution();
  auto res=s.longestPalindrome("caaaaa");
  println("{}", res);

}
