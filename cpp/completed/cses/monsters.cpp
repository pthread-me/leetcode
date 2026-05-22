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
  for(auto& e: v){
    cout << e << " ";
  }
  cout <<"\n";
}

template<number T>
constexpr auto mypow(T a, T b) -> T {
  T res = 1;
  for(;b>0;--b){
    res *= a; 
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


const vector<tuple<ll,ll,ll>> dir{{0,-1,'L'},{0,1,'R'}, {-1,0,'U'}, {1,0,'D'}};
auto valid_move(ll y, ll x, ll n, ll m) -> bool {
  return y>=0 && y<n && x>=0 && x<m; 
}


int main() {
  fast_io;

  ll n,m;
  char cur;
  cin >> n >> m;

  pair<ll,ll> player;
  deque<pair<ll,ll>> q{};
  vector<vector<char>> parent(n, vector<char>(m, '\0'));
  vector<vector<char>> grid(n, vector<char>(m, '\0'));
  
  for(ll i=0; i<n; ++i){
    for(ll j=0; j<m; ++j){
      cin >> cur;
      grid[i][j] = cur;
      if(cur=='M')q.push_back({i,j});
      if(cur=='A') player = {i,j};
    }
  }

  q.push_back({player.first, player.second});

  pair<ll,ll> res{-1,-1};
  while(!q.empty()){
    ll y,x;
    tie(y,x) = q.front(); q.pop_front();
    for(auto [dy, dx, d]: dir){
      if(valid_move(y+dy, x+dx, n, m) && grid[y+dy][x+dx] == '.'){
        grid[y+dy][x+dx] = grid[y][x];
        q.push_back({y+dy, x+dx});

        if(grid[y][x] == 'A'){
          parent[y+dy][x+dx] = d;
        }
      }
    }

    if(grid[y][x] == 'A' && (y==0 || y==n-1 || x==0 || x==m-1)){
      res = {y, x};    
      break;
    }
  }

  if(res.first == -1){
    cout << "NO\n";
  }else{
    ll y,x;
    tie(y,x) = res;
    vector<char> path;

    while(y!=player.first || x!=player.second){
      path.push_back(parent[y][x]);
      tuple<ll,ll,ll> path_dir;
      ll dy,dx, ignore;
      if(parent[y][x] == 'D') path_dir = dir[3];
      else if(parent[y][x] == 'U') path_dir = dir[2];
      else if(parent[y][x] == 'R') path_dir = dir[1];
      else if(parent[y][x] == 'L') path_dir = dir[0];
      else exit(1);

      tie(dy,dx, ignore) = path_dir;
      y-=dy;
      x-=dx;
    }

    reverse(path.begin(), path.end());
    cout << "YES\n";
    cout << path.size() << "\n";
    cout << string(path.begin(), path.end());
  }
 
}
