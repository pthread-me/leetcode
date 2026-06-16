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

template <integral T>
constexpr auto mylog2(T n){
  ull largest_power = (sizeof(declval<T>()) * 8) - 1;
  return largest_power - countl_zero(n);
}

template <integral T>
constexpr auto mylog10(T n) -> T{
  return mylog2(n) * numbers::ln2;
}



//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// SOLUTIONS BELLOW
////-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


using ll = long long;
using ull =unsigned long long;
auto order_partitition(vl& A, ll l, ll r, ll p) -> ll {
  ll pval = A[p];

  while(true){
    while(l<=r && A[l]<pval) ++l;
    while(r>=l && A[r]>pval) --r;
    if(l>=r) return r;
    swap(A[l], A[r]);
    --r, ++l;
  }
}

auto quicksort(vl& A, ll l, ll r, mt19937& gen) -> void {
  if(l>=r){
    return;
  }

  ull p = l + (gen() % (r-l+1));
  ll m = order_partitition(A, l, r, p);
  quicksort(A, l, m, gen);
  quicksort(A, m+1, r, gen);
}


int main() {
  mt19937 gen(random_device{}()); 
  vl A{5,2,3,1};
  quicksort(A, 0, A.size()-1, gen);
  println("{}", A);
}
