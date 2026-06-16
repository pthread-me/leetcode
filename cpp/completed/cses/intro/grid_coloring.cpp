#include <bits/stdc++.h>

using namespace std;


using ll =  long long;
using ull =  unsigned long long;
using vs = vector<string>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vvs = vector<vs>;

namespace srv = ranges::views;
namespace sr = ranges;
namespace sv = views;

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
    cout << "" << *it;
  }
  cout << "\n";
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// SOLUTIONS BELLOW
////-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


const string ops{"ABCD"};


auto sol(vs& grid, ll n, ll m) -> void {
  for(ll i=0; i<n; ++i){
    for(ll j=0; j<m; ++j){
      if( (i+j) % 2 == 0){
        if(grid[i][j] == 'A') grid[i][j] = 'C';
        else grid[i][j] = 'A'; 
      }else{
        if(grid[i][j] == 'B') grid[i][j] = 'D';
        else grid[i][j] = 'B'; 
      }
    }
  }

  for(auto r: grid){
    cout << r << "\n";
  }
}

// TOO SLOW
// This is correct but slow
auto backtrack(vs& grid, ll i, ll j) -> bool{
  if(i == grid.size()) return true;
  
  char org = grid[i][j];
  auto check = [&grid, &i, &j](char c) -> bool{
    bool left = (i-1>-1) ? grid[i-1][j] != c : true;
    bool top = (j-1>-1) ? grid[i][j-1] != c : true;
    bool top_left = (j-1>-1)&&(i-1>-1) ? grid[i-1][j-1] != c : true;
    return left && top && top_left;
  };
  
  for(char c: ops){
    if(c == grid[i][j] || !check(c)) continue;
    grid[i][j] = c;

    ll next_i = (j+1 == grid[0].size()) ? i+1 : i; 
    ll next_j = (j+1 == grid[0].size()) ? 0 : j+1; 
    
    if(backtrack(grid, next_i, next_j)) return true;
    grid[i][j] = org;
  }
  
  return false;
}

int main(){
  ll n, m;
  cin >> n >> m;
  vs grid = vs(n);

  for(auto i: srv::iota(0, n)){
    string s;
    cin >> s;
    grid[i] = s;
  }
  
  sol(grid, n, m);
}
