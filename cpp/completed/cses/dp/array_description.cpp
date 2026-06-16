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

static const ll INF = numeric_limits<ll>::max() - 10000; // offset possible addition issues
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
 *  This vid describes the sol perfectly, I understand but cant draw here
 *  https://www.youtube.com/watch?v=PLpzng35N54
 *
 *  My explaination is the following:
 *    we divide the list of numbers into levels, so nums[0] is L1
 *  The length of each level is m, since thats our domain.
 *  
 *  starting at some position dp[L][i] we can only choose elements in the range
 *    i-1 <= i <= i+1. so the number of ways to get to dp[L][i] is the number
 *    of ways to reach it (or be reached to it) summed.
 *
 *  If nums[L] != 0 we only consider the ith element equal to nums[L].
 *
 *  In my solution im offseting i by i-1 since arrays are 0 based. but its the same
 *
 */

const ll mod = (1000'000'007);

int main(){
  ll n, m;
  cin >> n >> m;
  vl nums{};
  for(auto _: srv::iota(0, n)){
    ll c; cin >> c;
    nums.push_back(c);
  }

  vvl dp(n, vl(m, 0));
  if(nums[0] != 0){
    dp[0][nums[0]-1] = 1;
  }else{
    for(ll i=0; i<m; ++i) dp[0][i] = 1;
  }

  for(ll l=1; l<n; ++l){
    for(ll i=0; i<m; ++i){
      if(nums[l] != 0 && i+1 != nums[l]) continue;

      if(i-1>=0) dp[l][i] = (dp[l-1][i-1] + dp[l][i]) % mod; 
      if(i+1<m) dp[l][i] = (dp[l-1][i+1] + dp[l][i]) % mod; 
      dp[l][i] = (dp[l-1][i] + dp[l][i]) % mod;
    }
  }

   
  // custom accumulation :)
  if(nums.back() == 0){
    cout << accumulate(dp.back().begin(), dp.back().end(), 0, [](ll a, ll b)->ll{
      return (a+b)% mod;
    });
  }else{
    cout << dp.back()[nums.back() - 1];
  }


}
