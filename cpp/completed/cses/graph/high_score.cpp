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
 
struct edge {
  ll a,b,w;
};


// modified bellman ford + pred array for inifite cycles

int main(){
  fast_io;

  ll n, m;
  cin >> n >> m;
  vector<ll> vertex_cost(n, NINF); vertex_cost[0] = 0;
  vector<edge> edges{};
  vector<ll> pred(n);
  for(ll i=0; i<n; ++i) pred[i] = i;


  for(ll i=0; i<m; ++i){
    ll a, b, w;
    cin >> a >> b >> w;
    edges.push_back(edge{a-1,b-1,w});
  }
  

  for(ll i=0; i<n-1; ++i){
    bool change_flag = false;
    for(auto e: edges){
      if(vertex_cost[e.a] > NINF && vertex_cost[e.b] < vertex_cost[e.a] + e.w){
        change_flag = true;
        vertex_cost[e.b] = vertex_cost[e.a] + e.w;
        pred[e.b] = e.a;
      }
    }
    if(!change_flag) break;
  }

  // finds infinite cycles
  for(auto e: edges){
    if(vertex_cost[e.a] > NINF && vertex_cost[e.b] < vertex_cost[e.a] + e.w){
      vertex_cost[e.b] = INF;
      pred[e.b] = e.a;
    }
  }

  // checking if any vertex along the path from 0 to n-1 is reached via an INF path
  bool inifitite_path = false;
  ll cur = n-1;
  while(cur != 0){
    if(vertex_cost[cur] == INF){
      inifitite_path = true;
      break;
    }
    cur = pred[cur];
  }

  // final check for the 0 vertex aswell for INF paths
  if(inifitite_path || vertex_cost[0] == INF){
    cout << -1;
  }else{
    cout << vertex_cost[n-1];
  }
}
