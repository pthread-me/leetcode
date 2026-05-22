#include <algorithm>
#include <bits/stdc++.h>
#include <optional>
#include <print>
#include <ranges>
#include <string>
#include <unistd.h>

using namespace std;

namespace srv = ranges::views;
namespace sr = ranges;
namespace sv = views;

using ll =  long long;


auto fn(ll n, vector<ll>& nums, vector<ll>& a) -> bool{
  auto write_to_nums = [&](ll i, ll r, ll dir){
    //println("nums: {}", nums);
    for (ll k = i; k<r; k += dir){
      nums[k] = nums[k+dir];
    }
    //println("nums: {}", nums);
  };


  auto scan = [&](ll i) -> optional<ll>{
    ll l = i;
    ll r = i;
    bool can_l = true;
    bool can_r = true;

    while (can_l or can_r){
      if(r<n-1 and a[r] == a[r+1]){
        r++;
      }else {
        can_r = false;
      }
      if(l>0 and a[l] == a[l-1]){
        l--;
      }else {
        can_l = false;
      }

      if (nums[r] == a[i]){
        write_to_nums(i, r, 1);
        return make_optional(r);
      }else if (r<n-1 && nums[r+1] == a[i]){
        write_to_nums(i, r+1, 1);
        return make_optional(r+1);
      }

      if (nums[l] == a[i]){
        write_to_nums(i, l, -1);
        return make_optional(l);
      }else if(l>0 && nums[l-1] == a[i]){
        write_to_nums(i, l-1, -1);
        return make_optional(l-1);
      }
    }

    return optional<ll>();
  };


  ll i = 0;
  while (i < n){
    //println("{}\n{}", nums, a);
    if (a[i] == nums[i]){
      i ++;
      continue;
    }  

    auto scan_to = scan(i);
    if (!scan_to.has_value()){
      return false;
    } 
    auto jump = scan_to.value();    
    //println("{} to {}\n",i, jump);
    if (i<jump){
      i+= jump;
    }else{
      i++;
    }
  }
  return true;
}

int main(){
  string line;
  getline(cin, line);
  ll inputs = stoll(line);
  
  for (ll i=0; i<inputs; i++){
    getline(cin, line);
    ll n = stoll(line);

    getline(cin, line); 
    auto splits = line | sv::split(' ');
    auto strs = sr::to<vector<string>>(splits);
    auto nums = strs | srv::transform([](string& e){return stoll(e);}) | sr::to<vector<ll>>();
   
    getline(cin, line); 
    splits = line | sv::split(' ');
    strs = sr::to<vector<string>>(splits);
    auto a = strs | srv::transform([](string& e){return stoll(e);}) | sr::to<vector<ll>>();

    println("{}", fn(n, nums, a)? "YES" : "NO");
  }

}


