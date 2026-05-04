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

static const ll INF = numeric_limits<ll>::max() - 100'000; // offset possible addition issues
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
  cout <<"\n";
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
auto mymin(T a, T b, Rest...args){
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


/*
 *  We keep 2 stacks in and out where each stack holds the cur value and 
 *  the cummulative OR up to that value in the stack.
 *
 *  for every window, we add a new element and remove one. The top
 *  of the out stack tells us the cumm or up until and including the elem
 *  we want to remove to out_top[-1] is the cumm without the elem we are removing
 *  while the top of the in stack tells us the cumm of up until what we are addind.
 *
 *  Take the seq: 3,0,1,8,2,4,7,6
 *  We start by adding k-1 to the in stack
 *  so:
 *  in = [(3,3),(0,3),(1,3),(8,11)]
 *  out = []
 *
 *  for the first iteration we start by adding the new element to in. so:
 *  in = [(3,3),(0,3),(1,3),(8,11), (2,15)]
 *  out = []
 *  then to remove from out we see that its empty to we need to fill it with 
 *  in, since the in elemenets will start to be removed in iter i+1
 *
 *  so:
 *  in = []
 *  out = [(2,2), (8,10), (1,11), (0,11), (3,11)]
 *  the result is the top of in | out, since in is empty we take it as 0
 *  so 0 | 11 = 11.
 *  after oring the top of out we pop it since its now leaving the window.
 *
 *  in iter i+1:
 *
 *  we start by adding the new elemn to in, so
 *  in = [(4,4)]
 *  out = [(2,2), (8,10), (1,11), (0,11)]
 *
 *  res = 4 | 11 = 15, then remove (0,11)
 *
 *  we continue this until out is empty, then fill it up
 *
 *
 *  for a better explaination look at: 
 *  https://codeforces.com/blog/entry/143960
 *
 */


int main(){
  ll n, k;
  cin >> n >> k;
  ll x, a, b, c;
  cin >> x >> a >> b >> c;
  ll cur = x;
  ll res = 0;

  // seq generator
  auto next_val = [&](ll prev) -> ll {
    return (a*prev + b) % c;
  };

  auto push_to_stack = [](vector<pair<ll,ll>>& stack, ll cur)->void{
    if(stack.empty()){
      stack.push_back(pair(cur, cur));
    }else{
      stack.push_back(pair(cur, stack.back().second | cur));
    }
  };

  vector<pair<ll,ll>> in_stack{};
  vector<pair<ll,ll>> out_stack{};

  for(ll i=0; i<k-1; ++i){
    push_to_stack(in_stack, cur);
    cur = next_val(cur);
  }

  for(ll i=k-1; i<n; ++i){
    push_to_stack(in_stack, cur); 
    if(out_stack.empty()){
      while(!in_stack.empty()){
        ll removed = in_stack.back().first;
        in_stack.pop_back();
        push_to_stack(out_stack, removed);
      }
    }
    
    ll in_stack_top = in_stack.empty() ? 0 : in_stack.back().second;
    ll out_stack_top = out_stack.back().second;

    out_stack.pop_back();
    res ^= (in_stack_top | out_stack_top);
    cur = next_val(cur);
  }

  cout << res;


}
