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

/**
 *  We use a brute force method of iterating over all possible values x.
 *  checking x's multiples and if any 2 are present in the set of seen elems
 *  then x is a common divisor. I do some precalc for duplicates since those can
 *  be the starting gcd. And by iterating from max->min we can early exit once
 *  an x is found or x<max_gcd(that was acquired while reading is vals as a result of dups)
 *
 *
 *  The runtime is fun:
 *    Let x_bound = n. then we know that we are doing an n loop over the numbers.
 *    in each loop
 *      for i in [1, n]:
 *        we iterate over all elements 1*i, 2*i, 3*i ... (j+1)*i>n
 *        This gives an n/i number of internal iterations.
 *
 *    Thus we have: Sum_i_to_n(n/i) = n*Sum_i=1_to_n(1/i) = n*H_n (the harmonic number)
 *    Which is approximated to n*log(n)
 *
 *    So O(nlogn)
 *
 *
 */


const ull mod = 1'000'000'007;
const ll x_bound = 1'000'000;

int main() {
  fast_io;
  ll n;
  cin >> n;
  unordered_set<ll> nums{}; nums.reserve(n);
  ll max_n = NINF;
  ll max_gcd = 1;

  for(ll i=0; i<n; ++i){
    ll cur; cin >> cur;
    if(nums.contains(cur)){
      max_gcd = max(max_gcd, cur); 
    }else{
      nums.insert(cur);
      max_n = max(max_n, cur);
    }
  }

  for(ll x=x_bound; x>max_gcd; --x){
    ll cnt = 0;
    for(ll i=1; x*i<=max_n && cnt<2; ++i){
      if(nums.contains(i*x)) ++cnt;
    }
    if(cnt>1){
      max_gcd = max(max_gcd, x);
      break;
    } 
  }

  cout << max_gcd;
}
