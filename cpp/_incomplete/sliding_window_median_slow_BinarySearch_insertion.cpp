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


int main(){
  ll n, k;
  cin >> n >> k;

  vl res{}; res.reserve(n);
  vl nums{};
  for(auto _: srv::iota(0, n)){
    ll c; cin>>c;
    nums.push_back(c); 
  }

  vl mem{};
  for(ll i=0; i<k; ++i){
    mem.push_back(nums[i]);
  }

  auto median = [&mem, &k]()->ll{
    if(k%2 == 0){
      return min(mem[k/2 - 1], mem[k/2]);
    }
      return mem[k/2];
  };

  auto bs = [&mem](ll val) -> ll {
    ll i=0;
    ll j=mem.size();
    
    while(i<j){
      ll m = i+(j-i)/2;
      if(mem[m]>val){
        j = m;
      }else if(mem[m]<val){
        i = m+1;
      }else{
        return m;
      }
    }
    return i;
  };

  auto rearrange = [&mem, &k, &bs](ll rem, ll inst) -> void {
    ll rem_pos = bs(rem);
    mem.erase(next(mem.begin(), rem_pos));
    //println("removing: {} at: {}", rem, rem_pos);

    ll inst_pos = bs(inst);
    if(inst_pos >= k){
      mem.push_back(inst);
    }else{
      mem.insert(next(mem.begin(), inst_pos), inst);
    }
    //println("inserting: {} at: {}", inst, inst_pos);
  };


  sort(mem.begin(), mem.end());
  //println("mem: {}", mem);
  res.push_back(median());
  for(ll i=k; i<n; ++i){
    if(nums[i-k] != nums[i])[[likely]]{
      rearrange(nums[i-k], nums[i]); 
    }
    //println("mem: {}", mem);
    res.push_back(median());
  }

 print_vec(res);
}
