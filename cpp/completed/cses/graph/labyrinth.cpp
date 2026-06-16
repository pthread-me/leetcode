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

/*
  We do normal BFS until we hit the target B, since its BFS this means 
  the first hit is the min, while traversing we keep 2 matricies, a 
  generic visited, and a matrix n*m of pairs that stores the parent of
  each visited cell. once we hit B we can use the parrent matrix to reconstruct
  the path.
 */


vector<tuple<ll,ll,string>> dir{{0,-1,"L"}, {0,1,"R"}, {-1,0,"U"}, {1,0,"D"}};

inline auto valid(vvs& grid, vvl& visited, ll i, ll j) -> bool{
  return min(i,j)>=0 && i<grid.size() && j<grid[0].size() && !visited[i][j] && grid[i][j] != "#";
}


int main(){
  string line;
  ll n, m;
  cin >> n >> m;
  getline(cin, line); // move past \n
  
  pair<ll,ll> start;
  pair<ll,ll> end;
  vvs grid(n, vector<string>(m, ""));
  vvl vis(n, vl(m, 0));
  vector<vector<pair<ll, ll>>> par(n, vector<pair<ll,ll>>(m, make_pair(INF, INF)));
  queue<pair<ll,ll>> q;

  for(auto x: srv::iota(0, n)){
    getline(cin, line);
    for(auto y: srv::iota(0, m)){
      grid[x][y] = line[y];
      if(line[y] == 'A') start = make_pair(x, y);
      if(line[y] == 'B') end = make_pair(x, y);
    }
  }



  q.push(start);
  vis[start.first][start.second] = 1;
  while(!q.empty()){
    auto cur = q.front();
    q.pop();

    if(grid[cur.first][cur.second] == "B") break;

    for(auto [dy, dx, D]: dir){
      if(valid(grid, vis, cur.first+dy, cur.second+dx)){
        vis[cur.first+dy][cur.second+dx] = 1;
        par[cur.first+dy][cur.second+dx] = make_pair(cur.first, cur.second);
        q.push(make_pair(cur.first+dy, cur.second+dx));
      }
    }
  }

  if(!vis[end.first][end.second]){
    cout << "NO\n";
  }else{
    cout << "YES\n";
    auto cur = end;
    vs answer{};
    answer.reserve(n*m);

    while(cur != start){
      auto cur_p = par[cur.first][cur.second];
      for(auto [dx, dy, D]: dir){
        if(cur.first - cur_p.first == dx && cur.second - cur_p.second == dy){
          answer.push_back(D);
          cur = cur_p;
          break;
        }
      }
    }
    cout << answer.size() << "\n";
    reverse(answer.begin(), answer.end());
    for(auto c: answer) cout << c;
    cout << "\n";
  }

}
