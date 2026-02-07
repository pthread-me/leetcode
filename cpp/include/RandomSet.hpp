#include <random>
#include <unordered_set>
#include <vector>


class  RandomSet{
  private:
    std::default_random_engine engine;
    std::uniform_int_distribution<int> dist;

    std::unordered_set<int> set;
    std::vector<size_t> keys;
		std::hash<int> hasher;

  public:
    RandomSet();
    bool insert(int val);
    bool remove(int val);
    int getRandom(int val);

};
