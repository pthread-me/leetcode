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

// obs:
// 1) node degree < 3 is req
// 2) all connected components conforming to 1) are either a chain or 
//    a circle. 
// 3) odd cycles are not allowed, but we can figure that out while coloring

/**
 * I know its ugly, this is a trivial question that is reduced to vertex color
 * with C=2 so its solved with simple dfs and visited/colored vectors
 */

auto color(map<ll,vl>& lookup, vl& visited, vl& res, ll cur) -> bool {
  if(visited[cur]) return true;
  visited[cur] = 1;

  vl available{1, 2};
  for(auto a: lookup[cur]){
    if(res[a] == available[0]) available[0] = -1;
    if(res[a] == available[1]) available[1] = -1;
  }
  auto c = sr::find_if(available.begin(), available.end(), [](auto e){return e>0;});
  if(c == available.end()) return false;

  res[cur] = * c;
  bool depth_res = true;
  for(auto a: lookup[cur]){
    if(visited[a]) continue;
    depth_res &= color(lookup, visited, res, a);
  }

  return depth_res;
}



int main(){
  ll n, m;
  cin >> n >> m;

  vl visited(n, 0);
  vl res(n, -1);
  map<ll, vl> lookup{};

  for(auto v: srv::iota(0, n)){
    lookup[v] = vector<ll>{};
  }
  for(auto _: srv::iota(0, m)){
    ll a, b;
    cin >> a >> b;
    lookup[a-1].push_back(b-1);
    lookup[b-1].push_back(a-1);
  }


  bool colored = true;
  for(auto& [k, v]: lookup){
    colored &= color(lookup, visited, res, k);
  }

  if(colored){
    print_vec(res);
  }else{
      cout << "IMPOSSIBLE\n";
  }

}
