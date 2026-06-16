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

static const ll INF = numeric_limits<ll>::max();
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

/**
 * Observation:
 *  Given a number N, we can think of blocks x and the number of arangments, for example
 *  if N = 3 we can:
 *    - take 1 block x then see how many ways we can arrange 2 blocks
 *    - take 2 blocks xx then see how many ways we can arrange 1 block
 *    - take 3 blocks xxx then see how many ways we can arrange 0 blocks
 *
 *  Notice also that we can only take N blocks if N<=6
 *  The base case for arranging 1 and 0 is = 1
 */


ll modulo = 1000*1000*1000 + 7;
vl base{1,1,2,4,8,16,32};

auto T(ll n)-> ll{
  if(n<=6) return base[n];
  ll res = 0;
  for(auto b: srv::iota(1, 6+1)){
    res += (T(n-b) % modulo);
  }
  return res;
}

auto T_dp(ll n) -> ll{
  if(n<base.size()) return base[n];  
  
  ll res = 0;
  res = (T_dp(n-1) +T_dp(n-2) +T_dp(n-3) +T_dp(n-4) +T_dp(n-5) +T_dp(n-6)) % modulo;
  base.push_back(res);
  return res;
}

int main(){
  ll n;
  cin >> n;
  base.reserve(n);
  cout << T_dp(n);
}
