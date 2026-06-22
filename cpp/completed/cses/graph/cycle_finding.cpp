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
using vvul = vector<vul>;
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
 *  This question introduces one improtant observation, but first:
 *    1) the finding of neg cycles is trivial via bellman ford
 *    2) it makes sense on the Nth iter to keep tract of an updated
 *        vertex, save it as an anchor then walk back.
 *
 *  Notice that 2) makes a slight mistake, a vertex gets relaxed not necessarly
 *  for being in a neg cycle, but simply by being reachable from one.
 *  The solution to this is to walk back n steps from an updated vertex since
 *  at worst its in the cycle and we get to it else it goes back to a vertex in 
 *  the cycle.
 *
 *  Finally I usually make the condition when dealing with (u,v,w) , if state[u] == INF
 *  then skip, but this doesnt make sense when searching for a cycle since
 *  say a vertex x is unreachable from s,but x has an edge (x,x,-2)
 *  So there is a neg cycle between itself.
 *
 */


using edge = tuple<ll,ll,ll>;

int main(){
  ll n, m;
  cin >> n >> m;

  vector<edge> adj(m); adj.reserve(m);
  vl state(n, INF);
  vl parent(n,0);
  vl ans{}; ans.reserve(n);

  for(ll i=0; i<n; ++i) parent[i] = i;
  state[0]=0;


  for(ll i=0; i<m; ++i){
    ll u, v, w; 
    cin >> u >> v >> w;
    adj.push_back(tuple{u-1,v-1,w});
  }

  for(ll i=0; i<n; ++i){
    bool change = false;
    for(auto [u,v,w]: adj){
      if(state[u]+w < state[v]){
        change = true;
        state[v] = state[u]+w;
        parent[v] = u;
      }
    }
    if(!change) break;
  }


  ll anchor = INF;
  for(auto [u,v,w]: adj){
    if(state[u]+w < state[v]){
      anchor = v;
      state[v] = state[u]+w;
      parent[v]=u;
    }
  }

  if(anchor == INF){
    cout << "NO";
  }else{
    for(ll i=0; i<n; ++i) anchor = parent[anchor]; 


    cout << "YES\n";
    ll cur = anchor;
    ans.push_back(cur+1);
    cur = parent[cur];
    while(cur != anchor){
      ans.push_back(cur+1);
      cur = parent[cur];
    }
    ans.push_back(anchor+1);


    for(auto rit= ans.rbegin(); rit != ans.rend(); rit = next(rit)){
      cout << *rit << ' ';
    }
    
  }
}
