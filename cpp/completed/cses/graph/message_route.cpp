#include <bits/stdc++.h>

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

static const ll INF = numeric_limits<ll>::max();
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

template<typename T>
auto read_line() -> vs {
  string line;
  getline(cin, line);
  
  vs res{};
  auto x = trim(line) | srv::split(' ') 
    | srv::transform([](auto&& sub) -> string{
      return std::string(sub.begin(), sub.end());
      });
  
  sr::for_each(x.begin(), x.end(), [&res](string s){res.push_back(s);}); 

  return res;
}

template<number T>
auto read_line() -> vector<T> {
  string line;
  getline(cin, line);

  vector<T> res{};
  auto x = trim(line) | srv::split(' ') 
    | srv::transform([](auto&& sub) -> T{
        auto b = &*sub.begin();
        auto e = &*sub.end();
        T i{};

        auto [ptr, err] = from_chars(b, e, i);
        if(err == errc::result_out_of_range || err == errc::invalid_argument){
          cerr << "Error in line to vector<{}> read " <<  typeid(T).name() << "\n";
          exit(1);
        }
        return i;
      });

  sr::for_each(x.begin(), x.end(), [&res](auto&& a){res.push_back(a);}); 
  return res;
}

template<printable T>
auto print_vec(vector<T>& v) -> void{
  cout << *v.begin();
  for(auto it = next(v.begin()); it!=v.end(); ++it){
    cout << " " << *it;
  }
  cout << "\n";
}

template<number T>
constexpr auto mypow(T a, T b) -> T {
  T res = 1;
  for(;b>0;--b){
    res *= a; 
  }
  return res;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// SOLUTIONS BELLOW
////-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/**
 *  Very similar to prev BFS + path algs, except now we use a map of node->nieghboors
 *  which turns runtime into V+H instead of n^2
 */


auto sol(ll n, ll m, map<ll, vl>& neighboors){
  ll target = n-1;

  vl parent(n, -1);
  vl visited(n, 0);
 
  bool found = false;
  queue<ll> q;
  q.push(0);
  visited[0] = 1;

  while(!q.empty() && !found){
    ll a = q.front();
    q.pop();

    for(auto b: neighboors[a]){
      if(!visited[b]){
        q.push(b);
        visited[b] = 1;
        parent[b] = a;
        if(b == target) found = true;
      }
    }
  }

  //walk back step
  if(!visited[target]){
    cout << "IMPOSSIBLE\n";
    return;
  }

  ll cur = target;
  vl ans{target+1};
  while(cur > 0){
    ans.push_back(parent[cur] + 1);
    cur = parent[cur];
  }

  reverse(ans.begin(), ans.end());
  cout << ans.size() << "\n";
  print_vec(ans);
}

int main(){
  ll n, m, target;
  cin >> n >> m;

  map<ll, vl> nieghboors{};
  for(auto _: srv::iota(0, m)){
    ll a, b;
    cin >> a >> b;
    nieghboors[a-1].push_back(b-1);
    nieghboors[b-1].push_back(a-1);
  }
 

  sol(n, m, nieghboors);
}
