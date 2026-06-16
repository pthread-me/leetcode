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



// Observation: 
//  if we are at a cell A and have the following choice:
//      x
//    _ A _
//      x
//  so 2 positions are blocked and 2 are open in a prependicular maner, then
//  there is no solution since taking one will create an island, thus not all
//  of the 48 steps can be taken without visiting an already touched cell
//
//  Another observation is that if we are at a cell A, and there is some cell B
//  where B!=A and B!=END and B only has only empty neighbor while being unvisited
//  then once we get to B, we wont be able to leave and its not the end so its a 
//  failed path

const ll N = 7;
const ll CELLS = 48;
string path;
vvl visited(N, vl(N, 0));
vvl const dir{{0, 1}, {0, -1},{1,0},{-1, 0}};

inline auto available(ll i, ll j) -> bool{
  return 0<=min(i,j) && N>max(i, j) && !visited[i][j];
}


// checks if a cell has only one open neighboor while not being visited
inline auto isolated = [](ll x, ll y) -> bool {
  return (x!=N-1 && y!=0) && available(x, y) && 
    (available(x-1, y)+available(x+1, y)+available(x, y-1)+available(x, y+1) == 1);
};
inline auto isolated_neighboor(ll const i, ll const j)-> bool{
  for(auto d: vvl{{-1,-1}, {-1,1}, {1,-1},{1,1}}){
    if(isolated(i+d[0], j+d[1])) return true;
  }
  return false;
}

inline auto L_split(ll const i, ll const j) -> bool{
  return (available(i-1, j) && available(i, j+1) && !available(i-1, j+1)) ||
          (available(i-1, j) && available(i, j-1) && !available(i-1, j-1))||
          (available(i+1, j) && available(i, j+1) && !available(i+1, j+1))||
          (available(i+1, j) && available(i, j-1) && !available(i+1, j-1));
}

auto sol(ll i, ll j, ll s) -> ll {
  if(s==CELLS && i==N-1 && j==0) return 1;

  // Checking the cross pattern in obs 1
  if(available(i+1, j) && available(i-1, j) && !available(i, j-1) && !available(i, j+1)){
    return 0;
  } 
  if(!available(i+1, j) && !available(i-1, j) && available(i, j-1) && available(i, j+1)){
    return 0;
  }
  if( L_split(i, j) || isolated_neighboor(i, j)) return 0;

  

  ll res = 0;
  if(path[s] == '?'){
    for(auto d: dir){
      if(available(i+d[0], j+d[1])){
        visited[i+d[0]][j+d[1]] = 1;
        res += sol(i+d[0], j+d[1], s+1);
        visited[i+d[0]][j+d[1]] = 0;
      }
    }
  }else{
    ll di = 0;
    ll dj = 0;
    if(path[s] == 'R') ++dj;
    if(path[s] == 'L') --dj;
    if(path[s] == 'U') --di;
    if(path[s] == 'D') ++di;

    if(available(i+di, j+dj)){
      visited[i+di][j+dj] = 1;
      res += sol(i+di, j+dj, s+1);
      visited[i+di][j+dj] = 0;
    }
  }
  return res;
}

int main(){
  cin >> path;
  visited[0][0] = 1;
  cout << sol(0, 0, 0);
}
