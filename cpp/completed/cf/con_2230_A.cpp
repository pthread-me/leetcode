#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL);

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

template<number T>
constexpr auto mypow(T a, T b) -> T {
  T res = 1;
  for(;b>0;--b){
    res *= a; 
  }
  return res;
}

template<number T>
constexpr auto fast_pow(T b, T p) -> T {
  T res = 1;
  while(p>0){
    if(p&1){
      res *= b;
    }
    b *= b;
    p >>= 1;
  }
  return res;
}


template<number T>
constexpr auto fast_pow(T b, T p, T m) -> T {
  T res = 1;
  while(p){
    if(p&1) res = (res * b) % m;
    b = (b*b) % m;
    p >>= 1;
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

template <number T>
auto mygcd(T a, T b) -> T{
  if(a<b) swap(a,b);
  if(b == 0) return a;
  if(a<0) a*=-1;
  if(b<0) b*=-1;

  T r = b;
  while(a%b){
    r = a%b;
    a = b;
    b = r;
  }
  return r;
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// SOLUTIONS BELLOW
////-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


auto T(ll n, ll a, ll b) -> ll{
  ll res{0};

  if(n>=3 && a>b/3){
    res += b*(n/3);
    n = n%3;
  }
  if(n>=2 && a>b/2){
    res += b*(n/2);
    n = n%2;
  }

  if(a>b){
    res += b*n;
  }else{
    res += n*a;
  }

  return res;
}

int main() {
  ll t;
  cin >> t;

  for(ll i=0; i<t; ++i){
    ll n, a, b;
    cin >> n >> a >> b;

    cout << T(n, a, b)<< "\n";
  }
}
