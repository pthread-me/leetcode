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
 *  The main observation we want to make in the question is the following.
 *    Assume that we already know which edge to dicount, then the total cost
 *    of the path is the min cost of s to u + mincost of v to t + (u,v)/2 
 *
 *  With that all we really need to is to test all edges with the above condition.
 *  to get the min costs we run dikjstras alg from s to all e and all e to v
 *  the second is equivalemt to v to all e where the edges are reversed
  */

template <typename T>
using _3dvec = vector<vector<vector<T>>>;
using edge = pair<ll,ll>;

auto dij(vector<vector<edge>>& adj, set<edge> q, vl& state){
  vl vis(state.size(), 0);

  while(!q.empty()){
    ll s, cw;
    tie(cw, s) = *q.begin();
    q.erase(q.begin());
    vis[s] = 1;
    
    for(auto [w, d]: adj[s]){
      if(vis[d]) continue;

      if(state[d] > cw + w){
        edge old = {state[d], d};
        q.erase(old);
        state[d] = cw + w;
        q.insert({cw+w, d});
      } 
    }
  }
}

int main(){
  fast_io;
  ll n, m;
  cin >> n >> m;
  
  _3dvec<edge> adj(2, vector<vector<edge>>(n, vector<edge>{}));
  vector<set<edge>> queue(2, set<edge>{});
  vector<vector<ll>> state(2, vector<ll>(n, INF));

  state[0][0] = 0;
  state[1][n-1] = 0;
  queue[0].insert({0,0});
  queue[1].insert({0,n-1});
  for(ll i=1; i<n; ++i){
    queue[0].insert({INF, i}); 
    queue[1].insert({INF, (n-1)-i}); 
  }

  for(ll i=0; i<m; ++i){
    ll s,d,w;
    cin >> s >> d >> w;
    adj[0][s-1].push_back({w, d-1});
    adj[1][d-1].push_back({w, s-1});
  }


  dij(adj[0], queue[0], state[0]);
  dij(adj[1], queue[1], state[1]);


  ll ans{INF};
  for(ll u=0; u<n; ++u){
    for(auto [w,v]: adj[0][u]){
      ans = min(ans, state[0][u] + state[1][v] + w/2);
    }
  }

  cout << ans;
}
