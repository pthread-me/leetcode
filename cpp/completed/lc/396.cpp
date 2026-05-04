#include <bits/stdc++.h>

using namespace std;

using ll =  long long;
using ull =  unsigned long long;
using vs = vector<string>;
using vl = vector<ll>;
using vul = vector<ull>;
using vvl = vector<vl>;
using vvs = vector<vs>;

namespace srv = ranges::views;
namespace sr = ranges;
namespace sv = views;

static const ll INF = numeric_limits<ll>::max() - 100'000; // offset possible addition issues
static const ll NINF = numeric_limits<ll>::min();

inline auto ltrim(string_view s) -> string_view {
  if(s.size() == 0) return string_view{s};
  auto it=s.find_last_not_of(" \n\t\f\r\v");
  return s.substr(0, it+1);
}
inline auto rtrim(string_view s) -> string_view {
  if(s.size()==0) return s;
  auto it=s.find_first_not_of(" \n\t\f\r\v");
  return s.substr(it);
}
inline auto trim(string_view s) -> string_view{
  return ltrim(rtrim(s));
}


template<typename T>
concept number = is_integral_v<T>;
template<typename T>
concept printable =  requires (ostream& os, T const& t) {
  {os << t} -> same_as<ostream&>;
};

template<typename T>
auto read_line() -> vs {
  string line;
  getline(cin, line);
  
  vs res{};
  auto x = trim(line) | srv::split(' ') 
    | srv::transform([](auto&& sub) -> string{
      return std::string(sub.begin(), sub.end());
      });
  
  sr::for_each(x.begin(), x.end(), [&res](string s){res.push_back(s);}); 

  return res;
}

template<number T>
auto read_line() -> vector<T> {
  string line;
  getline(cin, line);

  vector<T> res{};
  auto x = trim(line) | srv::split(' ') 
    | srv::transform([](auto&& sub) -> T{
        auto b = &*sub.begin();
        auto e = &*sub.end();
        T i{};

        auto [ptr, err] = from_chars(b, e, i);
        if(err == errc::result_out_of_range || err == errc::invalid_argument){
          cerr << "Error in line to vector<{}> read " <<  typeid(T).name() << "\n";
          exit(1);
        }
        return i;
      });

  sr::for_each(x.begin(), x.end(), [&res](auto&& a){res.push_back(a);}); 
  return res;
}

template<printable T>
auto print_vec(vector<T>& v) -> void{
  for(auto& e: v){
    cout << e << " ";
  }
  cout <<"\n";
}

template<number T>
constexpr auto mypow(T a, T b) -> T {
  T res = 1;
  for(;b>0;--b){
    res *= a; 
  }
  return res;
}

template<number T, typename ...Rest>
auto mymin(T a, T b, Rest...args){
  T res = min(a, b);
  for(auto p: {args...}){
    res = min(res, p); 
  }
  return res;
}


template<number T, typename ...Rest>
auto mymax(T& a, T& b, Rest&...args){
  T res = max(a, b);
  for(auto p: {args...}){
    res = max(res, p); 
  }
  return res;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// SOLUTIONS BELLOW
////-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/*
 *  We observe the relation between iterations f(0) and f(1) then generalize.
 *  take nums = a,b,c,d
 *  then 
 *  f(0) = a0 + b1 + c2 + d3
 *  f(1) = a4 + b0 + c1 + d2
 *
 *  now f(0) - f(1) = -4a + b + c + d which is equal to -5a + (a+b+c+d)
 *  so f(k+1) = f(k) + -n*r + sum(a..d)
 *  here r is the removed element to r = nums[n-1-k]
 *
 *  in the impl I start k from 1 since we precal the base case so r = nums[n-k]
 *
 */

class Solution {
public:
  int ninf = numeric_limits<int>::min();
  int brute_maxRotateFunction(vector<int>& nums) {
    int n = nums.size(); 
    int max_val = ninf;

    for(int r=0; r<n; ++r){
      int cur = 0;
      for(int i=0; i<n; ++i){
        cur += nums[(i+r)%n] * ((i+r)-r);
      }
      max_val = max(max_val, cur);
    }
    return max_val;
  }


  int maxRotateFunction(vector<int>& nums){
    int n = nums.size();
    int sum = accumulate(nums.begin(), nums.end(), 0);  
    vector<int> dp(n, 0);
    for(int i=0; i<n; ++i) dp[0]+=nums[i]*i;

    for(int k=1; k<n;++k){
      dp[k] = dp[k-1] + sum - (n*nums[n-k]);
    }

    println("{}", dp);
    return *max_element(dp.begin(), dp.end());
  }

};

int main(){
  Solution s{};
  vector<int> nums = {4,3,2,6};
  cout << s.maxRotateFunction(nums);
}
