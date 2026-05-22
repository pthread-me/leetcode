#include <algorithm>
#include <format>
#include <functional>
#include <iterator>
#include <numeric>
#include <print>
#include <ranges>
#include <span>
#include <string>
#include <utils.hpp>
#include <bits/stdc++.h>
#include <vector>

struct Word{
  string word;
  ll occ;
};

struct Words{
  vector<Word> line;
  ll remaing;
};

template<>
struct std::formatter<Word>: std::formatter<string>{
  auto format(Word const& word, std::format_context& ctx) const {
    string val = word.word; 
    string occ = to_string(word.occ);
    string res = "(" + val + ", " + occ + ")";

    return std::formatter<std::string>::format(res, ctx);
  }
};


class Solution {
public:

  vector<string> fullJustify(vector<string>& words, int maxWidth) {
    auto result = vector<string>();
    auto lines = vector<Words>();

    auto line = Words(vector<Word>(), maxWidth);

    for (string word: words){
      if (word.size() + 1 > line.remaing){
        auto clone = Words(line);
        lines.push_back(clone);
        line = Words(vector<Word>(), maxWidth);
      }     
      
      ll added = 0;
      if (line.line.size() > 0){
        line.line.push_back(Word(" ", 1));
        added += 1;
      }
      line.line.push_back(Word(word, 1));
      added += word.size();

      line.remaing -= (added);
    }



    println("BEFORE");
    for (auto line: lines){
      for (auto token: line.line){
        print("{}", token);
      }
      print("\nRemaining: {}\n", line.remaing);
    }

    for (auto& line: lines){
      for(ll i = 1; line.remaing > 0; line.remaing --){
        line.line[i].occ ++;
        i = (i+2<line.line.size())? i+2 : 1;
      }
    }
  
    println("\n\nAFTER");
    for (auto line: lines){
      for (auto token: line.line){
        print("{}", token);
      }
      print("\nRemaining: {}\n", line.remaing);
    }

    rs::transform(lines.begin(), lines.end()-1, back_inserter(result), [](Words line) -> string{
        string res = "";
        for (Word w: line.line){
          for (ll i=0; i<w.occ; i++){
            res += w.word;
          }
        }
        return res;
      });

    return result;
  }

};


int main(){
  auto s = Solution();
  auto words = vector<string>{"Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"};
  auto result = s.fullJustify(words, 20);
  println("{}", result);
}
