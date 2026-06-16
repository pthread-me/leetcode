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



// manual scan and solve, n^3
// Can be done in n^2 using game theory stuff related to Nimbers and the 
// size of each heap/pile

int main(){
  string line;
  getline(cin, line);
  ll n = stoll(line);

  vvl nums = vector(n, vl(n));

  for(ull i=0; i<n; ++i){
    for(ull j=0; j<n; ++j){
      vl seen(2*n);
      for(ull k=0; k<j; ++k){
        seen[nums[i][k]] = 1;
      }
      for(ull k=0; k<i; ++k){
        seen[nums[k][j]] = 1;
      }
      ll x = 0;
      while(seen[x] == 1) x++;

      nums[i][j] = x;
    }
  }

  for(auto r: nums){
    print_vec(r);
  }
}
