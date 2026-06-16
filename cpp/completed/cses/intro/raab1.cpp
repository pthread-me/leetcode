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

// This one was actually really fun, we dont use lists to create game examples.
// instead notice that if n = 5, the we have 3,2 (after filtering draws)
// so we start from index i=0 until n
// loser wins 2 out of 3 so the win the 4,1 and 5,2 but lose the 1,3 - 2,4 - 3,5
// This can we done by modulo. look at the code

int main(){
  string line;
  getline(cin, line);

  ll t = stoull(line);

  for(auto _: srv::iota(0, t)){
    auto nums = read_line<ll>();
    ll won = *max_element(next(nums.begin()), nums.end());
    ll lost = *min_element(next(nums.begin()), nums.end());
    ll n = accumulate(next(nums.begin()), nums.end(), 0);

    //cout << "n " << n << " won " << won << " lost " << lost << "\n";
    if(n > *nums.begin()){
      cout << "NO\n";
      continue;
    }else if(n>0 && !(won<n && n==(won+lost))){
       cout << "NO\n";
      continue;
    }
    cout << "YES\n";

    vl loser{};
    vl winner{};
    loser.reserve(*nums.begin());
    winner.reserve(*nums.begin());

    for(ll i=0; i<n; i++){
      loser.push_back((i+won)%n + 1);
      winner.push_back(i + 1);
    }

    for(ll j=n+1; j<=*nums.begin(); j++){
      loser.push_back(j);
      winner.push_back(j);
    }

    if(nums[1] < nums[2]){
      print_vec(loser);
      print_vec(winner);
    }else{
      print_vec(winner);
      print_vec(loser);
    }
  }
}
