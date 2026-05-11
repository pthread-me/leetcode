#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)

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

template<typename T>
using multiset_index = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;


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
 *  PBDS my beloved
 *  classic successor predecessor, get their order then subtract
 *
 *  We can also solve this using an "offline" segment ttree: https://cses.fi/problemset/model/1144/
 *
 */

auto pbds_solution() -> void{
  multiset_index<pair<ll,ll>> stat{};
  vl nums{};

  ll n, q;
  cin >> n >> q;

  for(ll i=0; i<n; ++i){
    ll val;
    cin >> val;
    nums.push_back(val);
    stat.insert(pair(val, i));
  }

//  println("statistic: {}", stat);
  for(ll i=0; i<q; ++i){
    char t; cin >> t;
    if(t == '?'){
      ll l, r; cin >> l >> r;

      // pred is not actually a pred, its the first valid elemnt in the range
      auto pred = stat.upper_bound({l-1, INF});
      auto succ = stat.upper_bound({r, INF});
      ll pred_order = stat.order_of_key(*pred);
      if(pred->first < l && pred != stat.begin()){
        ++pred_order;
      }
      // placing the successor at the actual successor or having it be the upper bound
      // of the seq size
      ll succ_order;
      if(succ == stat.end()){
        succ_order = stat.size();
      }else{
        succ_order = stat.order_of_key(*succ);
      }
     cout << (succ_order - pred_order) << "\n";
    }else{
      ll i, x;
      cin >> i >> x;
      --i;
      ll old_x = nums[i];
      stat.erase({old_x, i});
      stat.insert({x, i});
      nums[i] = x;
    }
  }
}


auto offline_segment_tree() -> void{
 
}

int main() {
  fast_io;

}
