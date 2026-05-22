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


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// SOLUTIONS BELLOW
////-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


// Naive
auto T_dumb(ull n) -> ull {
  ull res = 0;
  ull i=1;
  for(; i*i<n; ++i){
    if((n%i)==0)res+=2;
  } 
  return i*i==n ? res +1 : res;
}

/**
 *  Here we aim to find all the prime factors and the number each contributes e_i.
 *  so starting from res = 1 which is the number 1, since 1 | n
 *
 *  at i = 2 is n is even then 2 contrubutes to n as many times as n/2 is even,
 *  which is what the inner loop calculates. By modifying n, we avoid double counting 
 *  at say i=4, since i=2 handled all those cases and stops once n is odd.
 *
 *  we continue to do this to find all prime factors pi and their freq ei.
 *
 *  given 2 primes p1 and p2 with e1 and e2, we can form e1*e2 subsets aka (p1,p2,p1,p1...)
 *  all of which will divide n. But since we also need to acount for 1:
 *    aka p1*p2 | n and 1*p1*p2 | n. so we have (e1+1)*(e2+1).
 *
 *  This scales to any number of prime factors
 *
 */
auto T(ull n) -> ull {
  ull res = 1;
  for(ull i=2; i*i <= n; ++i){
    if(n%i == 0){
      ull ei = 1;
      n /= i;
      while(n%i == 0){
        ++ei;
        n /= i;
      }

      res *= (ei+1);
    }
  }

  // if n>1 then we still have a prime factor that contributes once so it has the
  // seq 1,p_i -> e_i = 1 so res *= 2
  if(n>1){
    res *= 2;
  }
  return res;
}

const ull mod = 1'000'000'007;
int main() {
  fast_io;
  ull t;
  cin >> t;
  for (ull i=0; i<t; ++i){
    ull n; 
    cin >> n;
    cout << T(n) << ' ';
  }
}
