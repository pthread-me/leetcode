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

using namespace __gnu_pbds;
using multiset_index = tree<ll, null_type, less_equal<ll>, rb_tree_tag, tree_order_statistics_node_update>;


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

/**
 *  Whats important here is that tl,tr,tm are the ranges in nums. vectors
 *  are the segments v.
 *
 *  When moving between left and right we use the following obs:
 *    1) for a vector of length n (so n leafs) we need n-1 internal nodes
 *      to construct a tree on it, so out total is 2n-1 segments/cells in seg.
 *    2) We use an euler tour tranversal (preorder) so left subtree is at v+1.
 *      right subtree is after all the child nodes of left, since we initially
 *      divide the segment at v into [tl, tm] and [tm+1,tr] we have it that
 *      left has 2*(tm-tl) child nodes + 1 for the left segment itself.
 *      So right is at index v+2(tm-tl+1)
 *    3) Update is trivial
 *    4) for query the only thing to keep in mind is what tl,tm,tr stand for.
 *      never cofuse them with v (thats what I used to get stuck at). Then we have
 *      4 cases
 *        a) the curr segment is exactly [l,r] -> just return
 *        b,c) [l,r] is fulling in eith left of right subtrees of curr segment
 *
 *        d) [l,r] is partially in both:
 *            The trick here is that once we go to the left segment we want the entire
 *            value from l to the last element to the right of that seg which is tm.
 *            same for right segment with tm+1 being the full length to the left of r.
 */


auto C(vl& seg, vl& nums, ll v, ll tl, ll tr) -> void {
  if(tl == tr){
    seg[v] = nums[tl];
    return;
  } 
  ll tm = tl + (tr-tl)/2;
  C(seg, nums, v+1, tl, tm);
  C(seg, nums, v+2*(tm-tl+1), tm+1, tr);
  seg[v] = seg[v+1] + seg[v+2*(tm-tl+1)];
}
auto U(vl& seg, ll v, ll tl, ll tr, ll pos, ll val){
  if(tl == tr){
    seg[v] = val;
    return;
  } 
  ll tm = tl + (tr-tl)/2;
  if(pos <= tm){
    U(seg, v+1, tl, tm, pos, val);
  }else{
    U(seg, 2*(tm-tl), tm+1, tr, pos, val);
  }
  seg[v] = seg[v+1] + seg[v+2*(tm-tl)];
}

auto Q(vl& seg, ll v, ll tl, ll tr, ll l, ll r) -> ll {
  if(tl == l && tr == r){
    return seg[v];
  }
  ll tm = tl + (tr-tl)/2;
  if(r<=tm){
    return Q(seg, v+1, tl, tm, l, r);  
  }else if (l>= tm+1){
    return Q(seg, v+2*(tm-tl+1), tm+1, tr, l, r);
  }else{
    return Q(seg, v+1, tl, tm, l, tm) + Q(seg, v+(2*(tm-tl+1)), tm+1, tr, tm+1, r);
  }
}

auto construct_tree(vl& nums) -> vl{
  ll n = nums.size();
  ll m = (2*n)-1;
  
  vl seg(m, 0);
  C(seg, nums, 0, 0, n-1);
  return seg;
}
auto update_tree(vl& seg, vl& nums, ll pos, ll val) -> void{
  assert(pos<seg.size());
  U(seg, 0, 0, nums.size()-1, pos, val);
}

auto sum_query(vl& seg, vl& nums, ll l, ll r){
  return Q(seg, 0, 0, nums.size()-1, l, r);
}


int main(){
  vl nums{18,2,9,-9,1,199,6,12,88,561,0};
  vl seg = construct_tree(nums);
  println("{}", seg);

  update_tree(seg,nums, 0, 0);
  println("{}", seg);

  ll l = 3;
  ll r = 8;
  println("{} + {} = {}",l, r, sum_query(seg, nums, l, r));
}











