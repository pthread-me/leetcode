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

static const ll INF = numeric_limits<ll>::max() - 100^000; // offset possible addition issues
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
  cout << *v.begin();
  for(auto it = next(v.begin()); it!=v.end(); ++it){
    cout << " " << *it;
  }
  cout << "\n";
}

template<number T>
constexpr auto mypow(T a, T b) -> T {
  T res = 1;
  for(;b>0;--b){
    res *= a; 
  }
  return res;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// SOLUTIONS BELLOW
////-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

constexpr ll N = 1'000'000;
constexpr ll mod = 1'000'000'007;

/*
 *  Look at T for the recurence:
 *  The dp approach is super simple once we undertsand T, all we do is save
 *  the solutions for both split and not split in a 2xn table. then when filling
 *  up we look back for the solution.
 *
 *  A bottom up approach is the best. and a possible optimization is to consteval
 *  the table as we know the max n
 *
 *  dp[0] is not split, dp[1] is split
 */
auto init_dp() -> auto {
  vector<vector<ull>> dp(2, vector<ull>(N+1)); 
  dp[0][1] = 1;
  dp[1][1] = 1;    

  for(ll i=2; i<N+1; ++i){
    dp[0][i] = (2*dp[0][i-1] + dp[1][i-1]) % mod;
    dp[1][i] = (4*dp[1][i-1] + dp[0][i-1]) % mod;
  }
  return dp;
}

auto D(ll n, auto & dp) -> ll {
  return (dp[0][n] + dp[1][n]) % mod;
}


/*
 *  Given a 2x1 rectangle, we have 2 cases, either its split in the middle or not:
 *  If u draw all possible L1 rectangle and extend them, you'll find that when
 *  we are split, then there are 5 possibilities, on of which is not split.
 *  When we are not split then there are 3 possibilities on of which is split
 *
 *  The improtant thing here is the first case, we do not know which L1 we get,
 *  so we start with both then recurse on n-1
 */

auto T_rec(ll n, bool split) -> ll {
  if(n==0) return 1;

  if(split){
    return 4*T_rec(n-1, true) + T_rec(n-1, false);
  }else{
    return 2*T_rec(n-1, false) + T_rec(n-1, true);
  }
}
auto T(ll n) -> ll {
  return (T_rec(n-1, false) + T_rec(n-1, true) );
}

int main(){
  ll t; 
  cin >> t;

  auto dp = init_dp();
  for(auto _: srv::iota(0, t)){
    ll n; cin >> n;
    cout << D(n, dp) << "\n";
  }
}
