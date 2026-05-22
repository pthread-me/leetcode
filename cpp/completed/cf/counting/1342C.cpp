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
constexpr auto fast_pow(T b, T p, T const m) -> T {
  T res = 1;
  while(p){
    if(p&1) res = ((res%m) * (b%m)) % m;
    b = ((b%m)*(b%m)) % m;
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

template<number T>
auto mylcm(T a, T b) -> T{
  return (a*b) / gcd(a, b);
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// SOLUTIONS BELLOW
////-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/*
 *  The question is a bit hard so my explaination might not be the best:
 *  
 *  Question given a range [l,r] and two numbers a,b find the number of elemns
 *  x in the range such that: (x%a)%b != (x%b)%a
 *
 *  Observations:
 *    1) if a<b then (x%a)%b = x%a -> so we swap if needed
 *    2) x can be writter as qb+r so:
 *      LHS goes from x%a to (bq+r)%a
 *      RHS goes from (x%b)%a to (bq+r % b)%a = r%a
 *
 *    3) now observe that we have r%a and bq+r%a, we ask the question:
 *      When are these 2 equations equal?
 *      A) when bq%a = 0 aka when q % LCM(a,b) = 0
 *
 *    4) The domain of the question turns from the integers to integeres modulo LCM(a,b)
 *      This is because we now consider the values that q%LCM(a,b) might take. which
 *      forms a "period" that repeats every LCM(a,b) elems
 *
 *      We then solve for [0, LCM(a,b)] the equation (x%a)%b != (x%b)%a.
 *      then answer the question, how many valid entries are in [0,r] - [0,l-1]
 *
 *      We note that since the period repeats, we can find the # of period in the range,
 *      then add that to the number in the last period
 *
 *
 *  NOTE:
 *    There is a patterns for the period vector, which you should look into, the first b-1 elems are 
 *    always 0
 */
auto f(vl& period, ll x, ll lcm) -> ll {
  if(x<0) return 0;
  return period.back() * (x/lcm) + period[x%lcm];
}


int main() {
  ll t; cin >> t;

  for(ll i{0}; i<t; ++i){
    ll a, b, q, lcm, ans{0};
    cin >> a >> b >> q; 
    lcm = mylcm(a, b);

    if(a>b) swap(a,b);

    vl period(lcm, 0);
    for(ll j{1}; j<lcm; ++j){
      period[j] = period[j-1] + ( (j%a) != ((j%b)%a) );
    }

    for(ll j{0}; j<q; ++j){
      ll l, r; cin >> l >> r;
      ans = f(period, r, lcm) - f(period, l-1, lcm); 
      cout << ans << ' ';
    }
    cout << '\n';
  }
}
