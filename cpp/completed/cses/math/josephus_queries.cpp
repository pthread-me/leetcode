#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)

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


/**
 *  Observe that for k < n/2 the kth deletion is in n, so we can just return it.
 *  otherwise, we recurse after deleting all possible elements:
 *    here we notice that at each round we delete even numbers, this gives us
 *    2 cases when n is even or odd.
 *
 *   Case 1: n is even
 *    - we can delete n/2 elements, leaving us with k-n/2 positions
 *    - for example n=6 k=5 we start with:
 *      round 1: 1 2 3 4 5 6 -> 1 _ 3 _ 5 _
 *      round 2: 1 2 3 -> 1 _ 3
 *      round 3: 1 2 -> 1 _
 *
 *      at each round > 1, the pos x maps to 2*x -1, so we can recurse until a 
 *      base case then map postions as we move up the call stack.
 *
 *   Case 2: n is odd:
 *    - This case is very similar except now, the mapping is shifted by one position
 *    - for example n=7 k=5 we start with:
 *      round 1: 1 2 3 4 5 6 7 -> 1 _ 3 _ 5 _ 7
 *      round 2: 1 2 3 4 -> 1 _ 3 _
 *
 *      observe that in round 2, case 2 postion 2 maps to 1 instead of 3.
 *
 *    Final note:
 *      - we do n+1/2 to find the number of elems remaining, and n/2 for the valid
 *      numbers removed at each round
 *
 */


auto T(ll n, ll k) -> ll {
  if(n==1)    return 1;
  if(k<= n/2) return 2*k;

  ll pos = T((n+1)/2, k-n/2);
  if(n%2 == 1){
    if(pos == 1)  return n;
    else          return 2*(pos-1) -1;
  }
  return 2*pos - 1;
}

int main() {
  ll t;
  cin >> t;
  for(ll i=0; i<t; ++i){
    ll n,k;
    cin >> n >> k;
    cout << T(n, k) << "\n";
  }
}
