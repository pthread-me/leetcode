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

static const ll INF = numeric_limits<ll>::max() - 100^000; // offset possible addition issues
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
auto mymin(T& a, T& b, Rest&...args){
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


/**
 *  The explaination to this is a bit weird for me, see: 
 *  https://people.engr.tamu.edu/andreas-klappenecker/csce411-f11/csce411-set8.pdf
 *
 *  What we basically do is the following: given 2 seq X and Y, and an LCS Z
 *  then given X_k being the seq from X[0:k] inclusive, then Z_k must
 *  include either X_k or Y_k or both. 
 *
 *  if X[k] == Y[k] then we know that Z_k = Z_(k-1) + 1 since we are adding to it
 *
 *  The hard to see part is when they are not equal, in this case we have 2 choices
 *  the longest seq is either in X_k and Y_(k-1) OR X_(k-1) and Y_k. Both cant be
 *  at k since they are not equal at that element.
 *
 *  an m*n dp is used to save the Z for every X_i Y_j pair
 *
 *
 *  re-building the sol is my work. observe that if all 3 prev states are less than
 *  dp[i][j] then it must be that we added a new element, that gives us the e to add.
 *  which must be a[i] == b[j] so we assert.
 *
 *  if dp[i][j] is not > than the left, right and top-left then no e was added,
 *  so we just move to that state.
 */



int main(){
  ll n, m;
  cin >> n >> m;

  vl a{}, b{};
  for(auto _: srv::iota(0, n)){
    ll val; cin >> val;
    a.push_back(val); 
  }
  for(auto _: srv::iota(0, m)){
    ll val; cin >> val;
    b.push_back(val); 
  }


  // accounting for the empty subarray
  vvl dp(n+1, vl(m+1, 0));

  for(ll i=1; i<n+1; ++i){
    for(ll j=1; j<m+1; ++j){
      if(a[i-1] == b[j-1]){
        dp[i][j] = dp[i-1][j-1]+1;
      }
      else{
        dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
      }
    }
  }

  // reconstructing result
  ll y = n;
  ll x = m;
  vl res{};
  while(y>0 && x>0 && dp[y][x] > 0){
    ll max_elem = mymax(dp[y-1][x-1], dp[y-1][x], dp[y][x-1]); 
    if(dp[y][x] > max_elem){
      assert(a[y-1] == b[x-1]);
      res.push_back(a[y-1]);
    }
    if(dp[y-1][x-1] == max_elem){
      --y; --x;
    }else if(dp[y-1][x] == max_elem){
      --y;
    }else{
      --x;
    }
  }


  cout << dp[n][m] << "\n";
  reverse(res.begin(), res.end());
  print_vec(res);
}
