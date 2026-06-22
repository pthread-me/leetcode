#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
 
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL);
 
using namespace std;
 
using ll =  long long;
using ull =  unsigned long long;
using vs = vector<string>;
using vl = vector<ll>;
using vull = vector<ull>;
using vvl = vector<vl>;
using vvs = vector<vs>;
 
namespace srv = ranges::views;
namespace sr = ranges;
namespace sv = views;
 
using namespace __gnu_pbds;
 
template<typename T>
using multiset_index = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
 
static const ll INF = numeric_limits<ll>::max() - 1'000'000'001; // offset possible addition issues
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


/**
 *  This is a super interesting question:
 *
 *  take the game 4513:
 *    at the first round the player can take 4 and let opp play on 513
 *            or take 3 and let opp play on 451
 *    continue recursivly.
 *
 *
 *  Note: S1 is the player currently playing the role (so roles reverse every turn)
 *
 *  The key observation we need are:
 *    1) the final res of the players S1 and S2 -> S1+S2 = Total
 *    2) out of the 2 choices we clearlt want to choose the one that maxs our S1
 *      Now since the Total is constant this means increasing S1 => reducing S2
 *
 *    3) keeping track of exact scores is difficult, instead we keep track of 
 *      "how much ahead  the cur player is after this play" aka S1-S2
 *
 *  We keep a 2D dp of the games starting from i and ending at j, initially the
 *  diagonal dp[i][i] = A[i] since S1 takes A[i] and S2 has nothing so A[i]-0
 *
 *  for j-i>1 the recurence is what we described above so:
 *    dp[i][j] = max(A[i]-dp[i+1][j],  A[j]-dp[i][j-1])
 *
 *    so its what S1 gets now - what S2 gets from the remaining interval
 *
 *    Since we need i+1 we iter i from n-1 to 0 while j from 0 to n-1
 *
 *  Finally after the last iteration we are left with obsv 3) for the interval
 *  [0,n-1] aka how much ahead is S1 to S2 on the entire array. 
 *  aka dp[0][n-1] = S1-S2 for the full range.
 *
 *  Finally since we have:
 *  S1+S2 = total
 *  S1-S2 = dp[0][n-1]
 *
 *  we get 2*S1 = total + dp[0][n-1] 
 *  S1 = (total + dp[0][n-1])/2
 *
 *
 *
 * Final note, the dp is only half filled starting from the diagonal
 *
 */

int main(){
  ll n;
  cin >> n;

  vl A{};
  for(ll i=0; i<n; ++i){
    ll c; cin >> c;
    A.push_back(c);
  }


  vvl dp(n, vl(n, 0));

  //init the diag
  for(ll i=0; i<n; ++i){
    for(ll j=0; j<n; ++j){
      if(i==j) dp[i][j] = A[i];
    }
  }

  for(ll i=n-1; i>=0; --i){
    for(ll j=i+1; j<n; ++j){
      dp[i][j] = max(A[i]-dp[i+1][j], A[j]-dp[i][j-1]);
    }
  }

  // s1-s2 = dp[0][n-1]
  ll equation1 = dp[0].back();

  // s1+s2 = total
  ll total = accumulate(A.begin(), A.end(), 0ll);

  //2*s1 = (total+dp[0][n-1])/2
  cout << (equation1 + total) /2;
}
