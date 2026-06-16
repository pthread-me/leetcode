#include <bits/stdc++.h>
 
using namespace std;
using ll =  long long;
using ull =  unsigned long long;
using us = unordered_set<string>;
using um = unordered_map<char, ull>;
using vs = vector<string>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vul = vector<ull>;
using vul = vector<ull>;
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
  return trim(line) | srv::split(' ') 
    | srv::transform([](auto&& sub) -> string{
      return std::string(sub.begin(), sub.end());
      }) 
    | sr::for_each([&res](string s){res.push_back(s);}); 
 
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
 
 
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
 
 
/*
 * Stole the solution from: 
 *  https://phuongdinh1411.github.io/cses-analyses/problem_soulutions/introductory_problems/apple_division_analysis
 *
 *  We basically use a bit mask to go over all possible sets, and adding the values for
 *  the elements in the set. Then doing a min check. AKA brute force.
 *
 *  I had a backtrack alg that worked for all n < 20 but couldnt fix it for n>=20
 *  so whatever. Also good to know about bit enumeration since I always forget thats a thing we can
 *  do with small n
 *
 */
 
auto sol(vl& nums) -> ull{
  ll t = accumulate(nums.begin(), nums.end(), 0ull);

  ll diff = t;
  for(ll mask=0; mask<1<<nums.size(); ++mask){
    ll g1 = 0;
    for(ll i=0; i<nums.size(); ++i){
      if(mask & 1<<i){
        g1 += nums[i];
      }
    }
    ll g2 = t - g1;
    diff = min(diff, abs(g2-g1));
  }
  return diff;
}
 
 
int main(){
 
  string line;
  getline(cin, line);
  ull n = stoll(line);
 
  auto nums = read_line<ll>();
  sort(nums.begin(), nums.end());
  ull t = accumulate(nums.begin(), nums.end(), 0);

  cout << sol(nums) << "\n";
}
