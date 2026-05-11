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
 *  We use a 2d prefix sum where pref[i][j] stores the number of * from 0,0
 *  to i,j inclusive. then to get an arbitrary rectangle at pos x,y we need 
 *  to get the pref[y][x] and subtract from it 2 rectangle (to the left and above)
 *  the left is easyily acuired from the prefixsum, the top needs to avoid double
 *  counting, this can be done either by subtracting or adding what would've been 
 *  double deleted. I go with the prior approach.
 *
 *  Can be solved using 2d segment trees (i think) but would be q*log^2(n) so prob fails
 *  on time. as opposed to O(q) for this question, plus the O(n) dp construction
 *
 */

int main() {
  ll n, q;
  char c;
  ll y1, x1, y2, x2;

  cin >> n >> q;

  vector<vector<ll>> pref(n+1, vector<ll>(n+1, 0));

  for(ll i=1; i<=n; ++i){
    for(ll j=1; j<=n; ++j){
      cin >> c;
      pref[i][j] = pref[i][j-1] + (pref[i-1][j] - pref[i-1][j-1]);
      if(c != '.') ++pref[i][j];
    }
  }

  for(ll i=0; i<q; ++i){
    cin >> y1 >> x1 >> y2 >> x2;
    ll res = pref[y2][x2] - pref[y2][x1-1] - (pref[y1-1][x2]-pref[y1-1][x1-1]);
    cout << res << "\n";
  }

}
