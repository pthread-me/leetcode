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


const ll mod = 1'000'000'007;
const ll exp_mod = mod - 1;

auto sos(ll i) -> ll {
  ll a = i;
  ll b = (i+1);

  if(a%2 == 0) a/=2;
  else b/=2;

  return ((a%exp_mod)*(b%exp_mod)) % exp_mod;
}

auto geometric_sum(ll r, ll n) -> ll {
  ll power = (n+1) % exp_mod;
  ll denominator = fast_pow(r-1, mod-2, mod);

  return (((fast_pow(r, power, mod) - 1) % mod) * denominator) % mod;
}



/*
 *  Here tp is the last cumm prime while te is the NUMBER of exponents;
 *  so if e_i = 4 te = 5, this is why in sumOfSeries function we pass in te-1.
 *  (all e's in primes are offset by +1 to rep the count and not the actual power)
 *
 *  
 *  The formula is п_{i=0}^e1 п_{j=0}^e2 (p_1^i * p_2^j)
 *  since the products are independant we can split them ot get
 *
 *  п_{i=0}^e1 п_{j=0}^e2 (p_1^i) * п_{i=0}^e1 п_{j=0}^e2 (p_2^j)
 *
 *  the lhs the j is equal to (e2+1) while in rhs i is equal to (e1+1)
 *  the for lhs i can be the sos for e1 and in rhs j is the sos of e2
 *  
 *  so you end up with:
 *
 *  (p_1^((e1*(e1+1))/2  * (e2+1))) * (p_2^((e2*(e2+1))/2  * (e1+1)))
 *  
 *  we just keep repeating this for all p in primes
 *
 *  Note that for the LHS we start with the cumm product of 1 prime, so inside the
 *  loop we only raise it to e2 since the sos(e1) is applied either before the loop
 *  or in the prev iteration.
 *
 */
auto P(vector<pair<ll,ll>>& primes){
  ll tp, te;
  tie(tp, te) = primes[0]; 

  tp = fast_pow(tp, sos(te-1)%exp_mod, mod);

  for(auto [p, e]: srv::drop(primes, 1)){
    ll lhs_power = (e%exp_mod);
    ll lhs = fast_pow(tp, lhs_power, mod);

    ll rhs_power = ((sos(e-1)%exp_mod) * (te%exp_mod)) % exp_mod;
    ll  rhs = fast_pow(p, rhs_power, mod); 

    tp = ((lhs % mod) * (rhs % mod) ) % mod;
    te = ((te % exp_mod) * (e%exp_mod)) % exp_mod;
  }

  return tp;
}


auto S(vector<pair<ll,ll>>& primes) -> ll {
  ll tp, te;
  tie(tp, te) = primes[0];
  tp = geometric_sum(tp, te-1);

  for(auto [p, e]: srv::drop(primes, 1)){
    tp = ((tp%mod) * (geometric_sum(p, e-1)%mod) ) % mod;
  }
  return tp;
}

int main() {
  ll n; cin >> n;
  vector<pair<ll,ll>> primes{};

  ll count = 1;
  for(ll i=0; i<n; ++i){
    ll p, e; cin >> p >> e;
    primes.push_back({p,((e%mod)+1)%mod});
    count = ((count%mod) * (((e%mod)+1)%mod)) % mod;
  }

  cout << count << ' ';
  cout << S(primes) << ' ';
  cout << P(primes);



}
