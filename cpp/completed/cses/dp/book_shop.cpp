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

static const ll INF = numeric_limits<ll>::max() - 10000; // offset possible addition issues
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


/*
 * The recursive solution is very similar to prev sum questions with the sole 
 * restriction of having to avoid double counting.
 *
 * The dp is also similar, we keep a vector of the max num of pages we can achieve 
 * at each price point. To avoid double counting we replicate the coin2 questions 
 * aproach by looping through the books first, in for each we go through the levels.
 *
 * A slight diff is that in coin 2 we wanted to count say the num 2 more than once
 * but here we dont, so when looping we start from the end.
 */

auto T(vl& cost, vl& page, ll x) -> ll{
  if(x==0) return 0;

  ll res = 0;
  for(ll i=0; i<cost.size(); ++i){
    if(cost[i]>x) continue;
    ll c=cost[i];
    cost[i] = INF; // to avoid double buying
    res = max(res, page[i] + T(cost, page, x-c));
    cost[i] = c;
  }
  return res;
}


int main(){
  ll n, x;
  cin >> n >> x;

  vl cost{}; cost.reserve(n);
  vl page{}; page.reserve(n);

  for(auto _ : srv::iota(0, n)){
    ll c; cin >> c;
    cost.push_back(c);
  }
  for(auto _ : srv::iota(0, n)){
    ll p; cin >> p;
    page.push_back(p);
  }
  
  //cout << T(cost, page, x);
  
  vl dp(x+1, 0);
  for(ll book=0; book<cost.size(); ++book){
    for(ll i=dp.size()-1; i>=0; --i){
      if(cost[book]>i) continue;
      dp[i] = max(dp[i], page[book] + dp[i-cost[book]]);
    }
  }

  cout << dp.back();


}
