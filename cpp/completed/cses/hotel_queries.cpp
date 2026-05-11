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
 *  A qlogn solution using segment trees, Im only searching for cells so np intervals
 *  and am biasing left branches. basic update and build, only diff is update
 *  prints the position of the cell that fits the predicate val<=nums[cell].
 *  Once it finds the cell it decrements the val and propagates changes upwards.
 */

auto B(vl& seg, vl& nums, ll v, ll tl, ll tr) -> void {
  if(tl == tr) {
    seg[v] = nums[tl];
    return;
  }
  ll tm = midpoint(tl, tr);
  B(seg, nums, v+1, tl, tm);
  B(seg, nums, v+2*(tm-tl+1), tm+1, tr);

  seg[v] = max(seg[v+1], seg[v+2*(tm-tl+1)]);
}

auto segement(vl& nums) -> vl{
  vl seg(2*nums.size()-1,0);
  B(seg, nums, 0, 0, nums.size()-1);
  return seg;
};


auto LU(vl& seg, ll v, ll tl, ll tr, ll val) -> void {
  if(tl == tr){
    assert(seg[v]>=val);
    cout << (tl + 1) << " ";
    seg[v]-=val;
    return;
  }

  ll tm = midpoint(tl, tr);
  if(seg[v+1] >= val){
    LU(seg, v+1, tl, tm, val); 
  }else{
    LU(seg, v+2*(tm-tl+1), tm+1, tr, val); 
  }
  seg[v] = max(seg[v+1], seg[v+2*(tm-tl+1)]);
}

int main() {
  ll n, q;
  cin >> n >> q;
  vl nums{};

  for(ll i=0; i<n; ++i){
    ll cur; cin >> cur;
    nums.push_back(cur);
  }

  vl seg = segement(nums);
     
  for(ll i=0; i<q; ++i){
    ll query; cin >> query;
    if(seg[0]<query){
      cout << "0 ";
    }else{
      LU(seg, 0, 0, nums.size()-1, query);
    }
  }

}
