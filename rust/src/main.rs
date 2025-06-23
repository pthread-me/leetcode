use std::collections::HashMap;

struct Trie{
  is_end: bool,
  rep: u64,
  children: HashMap<char, Trie>,
}


impl Trie{
  fn new() -> Trie{
    Trie{
      is_end : false,
      rep: 0,
      children : HashMap::new()
    }
  }
 
  fn insert_char(&mut self, c: char) -> &mut Trie{
    if !self.children.contains_key(&c){
      self.children.insert(c, Trie{is_end:false, rep:0, children:HashMap::new()});
    }
    self.children.get_mut(&c).unwrap()
  }


  fn insert(&mut self, s: &mut str){
     let mut cur = self;
     for (i, c) in s.char_indices(){
       if cur.children.keys().any(|k| k>&c){
        return 
       }
       cur = cur.insert_char(c);
       if s.len()-1 == i{
         cur.is_end = true;
       }
     }
  }
}

struct Solution();
impl Solution {
    pub fn last_substring(s: String) -> String {
      if s.len() == 0{
        return String::from("")
      } 

      let mut root = Trie::new();
      let mut suffix = s.clone();
    
      while suffix.len() > 0{
        root.insert(&mut suffix);
        suffix = suffix.split_off(1);
      }

      let mut cur = &root;
      let mut res = String::new();

      while cur.children.keys().len() > 0{
        let (child_key, child_val) = cur.children.iter().max_by(|a,b| a.0.cmp(&b.0)).unwrap();
        res.push(child_key.to_owned());
        cur = child_val;
      }
      return res
      
    }
}
fn main(){
  let res = Solution::last_substring(String::from("leetcode"));
  println!("{res}");
}
