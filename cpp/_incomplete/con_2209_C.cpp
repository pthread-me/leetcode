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
auto read_line() -> vs {
  string line;
  getline(cin, line);

  return trim(line) | srv::split(' ') 
    | srv::transform([](auto&& sub) -> string{
      return std::string(sub.begin(), sub.end());
      }) 
    | sr::to<vs>(); 
}
template<number T>
auto read_line() -> vector<T> {
  string line;
  getline(cin, line);

  return trim(line) | srv::split(' ') 
    | srv::transform([](auto&& sub) -> T{
        auto b = &*sub.begin();
        auto e = &*sub.end();
        T i{};

        auto [ptr, err] = from_chars(b, e, i);
        if(err == errc::result_out_of_range || err == errc::invalid_argument){
          println(cerr, "Error in line to vector<{}> read", typeid(T).name());
          exit(1);
        }
        return i;
      }) 
    | sr::to<vector<T>>(); 
}

template<formattable<char> T>
auto print_vec(vector<T>& v) -> void{
  print("{}", *v.begin());
  for(auto it = next(v.begin()); it!=v.end(); ++it){
    print(" {}", *it);
  }
  println();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

auto sol(ll n) -> void {
  ll mq = n+1;
  auto query = [&mq](ull i, ull j) -> ull {
    if(mq==0) return -1;

    string line;
    println("? {} {}", i, j);
    cout.flush();
    getline(cin, line);
    return stoull(line);
  };


  vl q{};
  for(ull i=1; i<n-2; i+=2){
    auto query_res = query(i, i+1);  
    if(query_res == -1){
      println("out of queries");
      exit(1);
    }
    q.push_back(query_res);
  }
  
  ull a{}, b{};
  ull res{};

  if(accumulate(q.begin(), q.end(), 0) == 0){
    a = 1;
    b = n-1;
    if(query(a, b) + query(a, b+1) == 0) res = a;
    else res = a+1;
  }else{
    b = 1+  2*(*find_if(q.begin(), q.end(), [](auto e){return e==1;}));
    if(sr::contains(q, 0)) a = 1+ 2*(*find_if(q.begin(), q.end(), [](auto e){return e==0;}));
    else a = n-1;

    query(n-1, n); // enforce inequality

    if(query(a, b) == 0) res = a;
    else res = a+1;
  }

  println("! {}", res);
  cout.flush();
}


int main(){

  string line;
  getline(cin, line);
  ull t = stoll(line);

  for(auto _: srv::iota(0ull, t)){
    getline(cin, line);
    ll n = stoll(line);
    sol(2*n);
  }
}
