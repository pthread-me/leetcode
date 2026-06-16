#include <bits/stdc++.h>

using namespace std;

struct pairhash {
public:

  // literally stolen word for word
  template <typename T, typename U>
  std::size_t operator()(const std::pair<T, U> &x) const
  {
    auto mix = [](size_t x) -> size_t {
      x ^= x >> 30;
      x *= 0xbf58476d1ce4e5b9ULL;
      x ^= x >> 27;
      x *= 0x94d049bb133111ebULL;
      x ^= x >> 31;
      return x;
    };
    return mix(hash<T>()(x.first) ^ mix(hash<T>()(x.second)));
  }
};



using ll =  long long;
using ull =  unsigned long long;
using us = unordered_set<string>;
using um = unordered_map<char, ull>;
using vs = vector<string>;
using vl = vector<ll>;
using vvl = vector<vl>;

using pair_set = unordered_set<pair<ll,ll>, pairhash>;


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
    cout << " " << *it;
  }
  cout << "\n";
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

auto sol(ull i, vector<pair<ll,ll>>& blocked, vector<pair<ll,ll>>& used, ull ldiag, ull rdiag) -> ull {
  auto get_ldiag = [](ull i, ull j) -> ull{return  1 << (i-j+7) ;};
  auto get_rdiag = [](ull i, ull j) -> ull{return  1 << (i+j)   ;};

  if(i==8) return 1;

  ull res = 0;
  for(ull j=0; j<8; ++j){ 
    auto pos = make_pair(i, j); 

    if(find_if(blocked.begin(),blocked.end(), [&pos](auto e){
          return e.first==pos.first && e.second == pos.second;}) != blocked.end()) continue;
    if(find_if(used.begin(),used.end(), [&pos](auto e){
          return e.first==pos.first || e.second == pos.second;}) != used.end()) continue;
    if(get_ldiag(i, j) & ldiag || get_rdiag(i, j) & rdiag) continue;

    used.push_back(make_pair(i, j));
    ldiag |= get_ldiag(i, j);
    rdiag |= get_rdiag(i, j);

    res += sol(i+1, blocked, used, ldiag, rdiag);

    used.pop_back();
    ldiag ^= get_ldiag(i, j);
    rdiag ^= get_rdiag(i, j);
  }
  return res;
}

int main(){
  string line;
  vector<vector<string>> grid{};
  for(auto _: srv::iota(0,8)){
    getline(cin, line);
    vs r{};
    for(auto c: trim(line)){
      r.push_back(string(1, c));
    }
    grid.push_back(r);
  }

  vector<pair<ll,ll>> used{};
  vector<pair<ll,ll>> blocked{};
  ull ldiag = 0ull;
  ull rdiag = 0ull;

  for(ull i: srv::iota(0, 8)){
    for(ull j: srv::iota(0, 8)){
      if(grid[i][j] == "*"){
        blocked.push_back(make_pair(i, j));
      }
    }
  }

  cout << sol(0, blocked, used, ldiag, rdiag);
}
