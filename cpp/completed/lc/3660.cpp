#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

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

using namespace __gnu_pbds;
using multiset_index = tree<ll, null_type, less_equal<ll>, rb_tree_tag, tree_order_statistics_node_update>;


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


/**
 *  given that we can jump left if nums[left] > nums[cur]
 *  and jump right if nums[right] < nums[cur]
 *
 *  Observation:
 *    We divide the array into connected components where a jump can occur 
 *    meaning 2 components can be connected.
 *
 *    When can a jump not occur ? 
 *    A) given 2 segements one on the left and the other on the right, if
 *    the max elem in the left seg < min elem in the right. Then there is
 *    no way to go from right to left.
 *
 *
 *    With this we keep 2 structs a prefix max array and a suffix min array
 *    Scanning right to left pref[i] represents the left seg and suffix[i+1]
 *    is the left.
 *
 *    if prefix[i] < suffix[i+1] then we cannot reach the max val at i+1
 *    so res[i] = prefix[i]
 *    otherwise we can jump from segment where i is to the segment where i+i is
 *    so res[i] = res[i+1];
 *
 *
 *    Final observation, the lest element will always be able to reach the max,
 *    this guarantees the moving right to left gives max vals
 *    */

class Solution {
public:
  vector<int> maxValue(vector<int>& nums) {
    int n = nums.size();
    vector<int> pref_max{nums[0]};   
    vector<int> suff_min(n, 0);
    suff_min[n-1] = nums.back();

    vector<int> res(n, 0);

    for(int i=1; i<n; ++i) pref_max.push_back(max(nums[i], pref_max[i-1]));
    for(int i=n-2; i>=0; --i) suff_min[i] =  min(nums[i], suff_min[i+1]);

    res[n-1] = pref_max[n-1];
    for(int i=n-2; i>=0; --i){
      if(pref_max[i] <= suff_min[i+1]) res[i] = pref_max[i];
      else res[i] = res[i+1];
    }

    return res;
  }
};

int main(){
  Solution S{};
  vector<int> nums{11,18,11};
  println("{}", S.maxValue(nums));
}
