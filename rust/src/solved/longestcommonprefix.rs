use std::collections::HashMap;

struct Trie{
  is_end: bool,
  children: HashMap<char, Trie>,
}


impl Trie{
  fn new() -> Trie{
    Trie{
      is_end : false,
      children : HashMap::new()
    }
  }
 
  fn insert_char(&mut self, c: char) -> &mut Trie{
    if !self.children.contains_key(&c){
      self.children.insert(c, Trie{is_end:false, children:HashMap::new()});
    }
    self.children.get_mut(&c).unwrap()
  }


  fn insert(&mut self, s: &mut str){
     let mut cur = self;
     for (i, c) in s.char_indices(){
       cur = cur.insert_char(c);
       if s.len()-1 == i{
         cur.is_end = true;
       }
     }
  }
}

struct Solution();
impl Solution {
    pub fn longest_common_prefix(strs: Vec<String>) -> String {
      if strs.iter().any(|s| s.is_empty()){
        return String::from("")
      }

      let mut root = Trie::new();
      let strs: Vec<String> = strs.clone();
      
      for mut s in strs{
        root.insert(&mut s);
      }
      
      let mut cur = &root;
      let mut res: String = String::new();
      while cur.children.len() ==1 && cur.is_end == false {
        let child = cur.children.keys().last().unwrap();
        res.push(child.to_owned());
        cur = cur.children.get(child).unwrap();
      }

      res
    }
}
fn main(){
  let strs = Vec::from([String::from("a"), String::from("ab")]);
  let res = Solution::longest_common_prefix(strs);
  println!("{res}");
}
