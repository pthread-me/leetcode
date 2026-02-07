#include <algorithm>
#include <iterator>
#include <print>
#include <ranges>
#include <sstream>
#include <utils.hpp>
#include <bits/stdc++.h>



class Solution {
public:

  string preprocess(string& input){
    auto builder = stringstream();
    builder.put('#');
    rs::for_each(input, [&builder](char c){
      builder.put(c); builder.put('#');    
    });

    return builder.str();
  }  



  string longestPalindrome(string input) {
    string s = preprocess(input);
    vector<ll> dp = vector<ll>(s.length());
    ll l{0}, r{1};

    auto naive = [&](ll i) {
      while (i - dp[i] and i+dp[i]<s.length() and s[i-dp[i]] == s[i+dp[i]]) {
        dp[i] ++;
      } 
    };

    for(ll i: rsv::iota(1ll, static_cast<ll>(s.length()) - 1) | rs::to<vector<ll>>()){
      if (i<r){
        ll j = l+ (r-i);
        dp[i] = min(dp[j], j-l);
        naive(i);
      }else{
        naive(i);
      }
    }
    
    auto max_pos = rs::max_element(dp);
    ll m = distance(dp.begin(), max_pos);
    ll radius = *max_pos -1;
    string res = s.substr(m-radius, radius*2 + 1);
    res = res | rsv::filter([](char c){return c!='#';}) | rs::to<string>();

    return res;
  }
};

int main(){
  auto s = Solution();
  auto res=s.longestPalindrome("caaaa");
  println("{}", res);
}
