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


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// SOLUTIONS BELLOW
////-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


const ll p = 1'000'000'007;
const ll two_inverse = fast_pow(2ll, p-2, p);

auto count(vector<pair<ll,ll>>& primes) -> ll {
  ll res = 1;
  for(auto& [x, e]: primes){
    res *= (e+1) % p;
  }
  return res;
}

/*
 *  given p1^e1 and p2^e2 obsevre that the total sum is:
 *    Sum_(i=0 to e1) Sum_(j=0 to e2) of p1^i * p2^j
 *
 *    aka 2 nested independant sums so we can instead do:
 *    (Sum_(i=0 to e1) p1^i) * (Sum_(j=0 to e2) p2^j)
 *
 *   Then scalling for pn and en is easy
 *
 *   We use the trick for modul div: a/b % p = a*b^(p-2) % p 
 *   inv of b is b^(p-1) so b^(p-2)*b = b^(p-1) = 1%p
 */
auto sum(vector<pair<ll,ll>>& primes) -> ll {
  ll res = 1; 
  for(auto& [x, e]: primes) {
    ll numerator = ((fast_pow(x, e+1, p)-1)%p);
    ll denominator = (fast_pow((x-1),p-2, p)%p);
    
    ll temp = ((numerator%p) * (denominator%p)) % p;
    res = (res * temp) % p;
  }
  return res;
}


/**
 *  explaination here: https://usaco.guide/problems/cses-2182-divisor-analysis/solution
 *
 *  think of a table that we keep increasing by dimension
 *
 *  it starts of as the prod of x1^0 * x1^1 * ... x1^e1
 *  then turns into a table:
 *  (x1^0 * x2^0) * (x1^1 * x2^0) ... (x1^e1 * x2^0)
 *  *
 *  (x1^0 * x2^1) * (x1^1 * x2^1) ... (x1^e1 * x2^1)
 *  *
 *  (x1^0 * x2^2) * (x1^1 * x2^2) ... (x1^e1 * x2^2)
 *  ...
 *  (x1^0 * x2^e2) * (x1^1 * x2^e2) ... (x1^e1 * x2^e2)
 *
 *
 *  Then it becomes 3d -> 4d ....
 *
 *
 */
auto prod(vector<pair<ll,ll>>& primes) -> ll{
    auto sum_of_series = [](ll e) -> ll {
    return ( (((e+1)%p * (e%p)) %p) * (two_inverse)) % p;
  };

  ll prev_prod = fast_pow(primes[0].first, primes[0].second, p);
  ll prev_count = primes[0].second + 1;

  for(auto& [x, e]: srv::drop(primes, 1)) {

    ll x_col_contrb = fast_pow(x, sum_of_series(e), p);
    ll x_total_contrib = fast_pow(x_col_contrb, prev_count, p);

    prev_prod = (fast_pow(prev_prod, e+1, p) * x_total_contrib) % p;
    prev_count = prev_count * (e+1) % (p-1);
  }


  return  prev_prod;
}

int main() {
  ll n;
  cin >> n;

  vector<pair<ll,ll>> primes{}; primes.reserve(n);

  for(ll i=0; i<n; ++i){
    ll x, e; cin >> x >> e;
    primes.push_back({x, e});
  }

  cout << count(primes) << ' ' <<  sum(primes) << ' '  << prod(primes);

  

 
}
