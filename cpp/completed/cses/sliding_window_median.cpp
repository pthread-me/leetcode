#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

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
 *  In the multiset solution, we keep 2 sets L and R, where every element
 *  l in L is <= every element r in R.
 *  this was we maintain an ordering (if we traverse L then R).
 *
 *  Further by maintaining the size of L to be equal to (k+1)/2 we garuntee
 *  that either k/2 or k/2 + 1 of the elements are in L (based on the parity of k
 *   we dont do (k/2)+1 immediatly since that puts us 1 off if k is even).
 *
 *   By maintaining the relation between L and R we have it that the rightmost 
 *   element in L is the median.
 *
 *   There is another solution using Policy based data structures PBDS, check it 
 *   out :)
 *
 */
auto multiset_sol(vl& nums, ll n, ll k) -> void{
  multiset<ll> L{};
  multiset<ll> R{};
  
  for(ll i=0; i<k; ++i){
    L.insert(nums[i]);
  }
  while(L.size() > (k+1)/2){
    R.insert(*L.rbegin()); 
    L.extract(*L.rbegin());
  }


  cout << *L.rbegin() << " ";
  //println("L: {}\nR: {}\n", L, R);
  for(ll i=k; i<n; ++i){
    ll out = nums[i-k];
    ll in = nums[i];

    if(out <= *L.rbegin()) L.extract(out);
    else R.extract(out);

    if(!L.empty() && in <= *L.rbegin()) L.insert(in);
    else R.insert(in);

    while(L.size() < (k+1)/2){
      L.insert(*R.begin());
      R.extract(*R.begin());
    }
    while(L.size() > (k+1)/2){
      R.insert(*L.rbegin());
      L.extract(*L.rbegin());
    }

    //println("L: {}\nR: {}\n", L, R);
    cout << *L.rbegin() << " ";
  }
}



using namespace __gnu_pbds;
using multiset_index = tree<ll, null_type, less_equal<ll>, rb_tree_tag, tree_order_statistics_node_update>;

auto pdbs_sol(vl& nums, ll n, ll k)-> void {
  multiset_index idx{};

  for(ll i=0; i<k; ++i){
    idx.insert(nums[i]);
  }
  cout << *idx.find_by_order((k-1)/2) << " ";

  for(ll i=k; i<n; ++i){
    ll out = nums[i-k];
    ll in  = nums[i];

    // we get the order aka pos then use it to aquire an iterator to the elem
    // to remove
    auto out_pos = idx.find_by_order(idx.order_of_key(out));

    idx.erase(out_pos);
    idx.insert(in);
    cout << *idx.find_by_order((k-1)/2) << " ";
  }
}


int main(){
  ll n, k;
  cin >> n >> k;

  vl nums{};
  for(auto _: srv::iota(0, n)){
    ll c; cin>>c;
    nums.push_back(c); 
  }
  
//  multiset_sol(nums, n, k);
  pdbs_sol(nums, n, k);
}
