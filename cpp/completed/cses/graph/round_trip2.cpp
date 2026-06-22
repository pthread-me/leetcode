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
 *  DFS with coloring, we keep status that has values 0,1,2. 0 means not visited
 *  1 is in the current path, 2 means it was traversed but resulted in no cycle.
 *
 *
 *  when a neighboring node v is:
 *    0 -> we recurse
 *    1 -> found a cycle
 *    2 -> ignore
 *
 *  finally we return the cycle's anchor v (not forgetting to update parent)
 */
auto dfs(vvl& adj, vl& status, vl& parent, ll u) -> ll{
  status[u] = 1;
  ll res = -1;

  for(auto v: adj[u]){
    parent[v] = u;
    if(status[v] == 0){
      res = dfs(adj, status, parent, v);
      if(res > -1) return res;
    }else if(status[v] == 1){
      return v;
    }
  }
  status[u] = 2;
  return res;
}

int main(){
  ll n,m;
  cin >> n >> m;

  vvl adj(n, vl{});
  for(ll i=0; i<m; ++i){
    ll u,v;
    cin >> u >> v;
    adj[u-1].push_back(v-1);
  }

  vl status(n, 0);
  vl parent(n); for(ll i=0; i<n; ++i) parent[i] = i;


  for(ll i=0; i<n; ++i){
    if(status[i] > 0) continue;

    ll res = dfs(adj, status, parent, i);
    if(res > -1){
      vl ans{res};
      ll cur = parent[res];
      while(cur != res){
        ans.push_back(cur);
        cur = parent[cur];
      }
      ans.push_back(res);


      cout << ans.size() << '\n'; 
      for(auto it = ans.rbegin(); it != ans.rend(); it = next(it)){
        cout << (*it)+1 << ' ';
      }

      exit(0);
    }
  }
  cout << "IMPOSSIBLE";
}
