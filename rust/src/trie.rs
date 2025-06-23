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


