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
static const ull PRIME_PRE_CAL = 100;

template<typename T>
concept printable =  requires (ostream& os, T const& t) {
  {os << t} -> same_as<ostream&>;
};

template<integral T>
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


template<integral T>
constexpr auto fast_pow(T b, T p, T const m) -> T {
  T res = 1;
  while(p){
    if(p&1) res = ((res%m) * (b%m)) % m;
    b = ((b%m)*(b%m)) % m;
    p >>= 1;
  }
  return res;
}


template<integral T, typename ...Rest>
auto mymin(T a, T b, Rest...args){
  T res = min(a, b);
  for(auto p: {args...}){
    res = min(res, p); 
  }
  return res;
}


template<integral T, typename ...Rest>
auto mymax(T& a, T& b, Rest&...args){
  T res = max(a, b);
  for(auto p: {args...}){
    res = max(res, p); 
  }
  return res;
}

template <integral T>
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

template<integral T>
auto mylcm(T a, T b) -> T{
  return (a*b) / gcd(a, b);
}

constexpr auto mylog2(ull n){
  ull largest_power = (sizeof(declval<ull>()) * 8) - 1;
  return largest_power - countl_zero(n);
}

constexpr auto mylog10(ull n) -> ull{
  return mylog2(n) * numbers::ln2;
}

template<integral T>
constexpr auto trial_div(T n) -> bool{
  if(n==2) return true;
  if(n%2 == 0) return false;

  for(T i=3; i*i<=n; i+=2){
    if(n%i == 0) return false;
  }
  return true;
}

template<integral T> 
constexpr auto prime_count_estm(T n) -> T{
  return (n/mylog10(n)) + 1;
}

template<integral T>
consteval auto small_prime_init() -> pair<array<T, prime_count_estm(PRIME_PRE_CAL)>, ull>{
  T c{0};
  constexpr T s = prime_count_estm(PRIME_PRE_CAL);
  array<T, s> nums{};
  for(ull i=2; i<=PRIME_PRE_CAL && c<s; ++i){
    if(trial_div(i)) nums[c] = i, ++c;
  }
  return {nums, c};
}


template<ull confidence, integral T > 
  requires (confidence < small_prime_init<ull>().second)
constexpr auto miller_rabin(T input) -> bool {
  if(input %2 == 0) return false;

  ull n;
  if(input<0) n = static_cast<ull>(input*-1);
  else n = static_cast<ull>(input);
  if(n == 1) return false;
  
  constexpr ull largest_power = (sizeof(declval<T>()) * 8) -1;
  constexpr auto witnesses = small_prime_init<ull>().first;
  ull s = largest_power - countl_zero(n);
  ull d = (n-1)/(1<<s);

  for(auto a: witnesses 
      | srv::filter([](auto e){return e>0;}) 
      | srv::drop(confidence))
  {
    if(fast_pow(a, d, n) == 1) continue; 
    bool found_flag = false;
    for(auto r: srv::iota(0ull, s)){
      ull t2pow = (((1<<r)%(n-1)) * d) % (n-1);
      if(fast_pow(a, t2pow, n) == (n-1)){
        found_flag = true; break; 
      }
    }
    if(!found_flag) return false; 
  }
  return true;
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// SOLUTIONS BELLOW
////-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

int main() {
  vl res{};
  for(ull i=0; i<100; ++i){
    if(miller_rabin<4>(i)) res.push_back(i);
  }

  println("{}", res);
}
