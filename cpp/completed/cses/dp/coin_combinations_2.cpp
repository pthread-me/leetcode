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

/**
 * Observation:
 *  in the example from coin_combination_1 where x = 9 and nums = [2,3,5]
 *  we repeat for x = 5 both 2+3 and 3+2
 *  this is because we try for x=5:
 *    5-2 then 5-3
 *
 *  if instead we limit our choices to only 2,3,5 as long as we choose 2
 *  then if we choose 3 our next iter choices become 3,5 and so on.
 *
 *  we find that the sequences we choose will be oerders(given that nums is ordered)
 *  but more importantly no repetition.
 *
 *  This can be done by looping through nums {looping through x}
 *  aka reverse the looping order from prev q
 *    
*/


const ll mod =1000*1000*1000 + 7; 

auto T(vl& nums, ll x)->ll{
  if(x<0) return 0;
  if(x == 0) return 1;

  ll res = 0;
  for(auto e: nums){
    res += T(nums, x-e) % mod;
  }
  return res;
}

int main(){
	ll n, x;
	cin >> n >> x;
	vl nums{}; nums.reserve(n);
	for(auto _: srv::iota(0, n)){
		ll c; cin >> c;
		nums.push_back(c);
	}
  
  vl dp(x+1, 0);
  dp[0] = 1;
  

  for(auto e: nums){
    for(auto cur: srv::iota(1, x+1)){
      if(cur-e<0) continue;
      dp[cur] = (dp[cur] + dp[cur-e]) % mod;
    }
  }

  cout << dp[x];
}
