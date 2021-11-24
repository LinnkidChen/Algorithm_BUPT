#include <cstddef>
#include <fstream>
#include <iostream>
#include <list>
#include <utility>
#include <vector>

class node {
public:
  node(int val_ = 0, int weight_ = 0) {
    val = val_;
    weight = weight_;
  }
  node operator+(node &obj) const {
    return node(val + obj.val, weight + obj.weight);
  }
  bool operator>(const node &obj) const { return val > obj.val; }
  bool operator<(const node &obj) const { return val < obj.val; }
  int val;
  int weight;
};

using namespace std;
list<node> *a;
void clear_point(list<node> &set) {
  auto it = set.begin();
  auto it_ = it;
  it_++;
  while (it_ != set.end()) {
    if (*it > *it_) {
      it_ = set.erase(it_);
    } else

    {
      it++;
      it_++;
    }
  }
}
void cal_weight(int j, vector<node> &items) {
  node temp_node(0, 0);
  a[items.size()].push_back(temp_node);
  list<node> temp_q;
  auto it = items.rbegin();
  temp_q.push_back(temp_node + *it);

  for (int i = items.size() - 1; i >= 0; i--) {
    temp_q.merge(a[i + 1]);
    a[i] = temp_q;
    clear_point(a[i]);

    temp_q.clear();
    it++;
    for (const auto &it_ : a[i]) {
      temp_q.push_back(it_ + *it);
    };
  }
}

int main() {
  int v, n;
  vector<node> items;
  node temp_itm;
  ifstream fin;
  fin.open("bag.in");

  fin >> v >> n;
  for (int i = 0; i < n; i++) {
    fin >> temp_itm.weight >> temp_itm.val;
    items.push_back(temp_itm);
  }

  a = new list<node>[n + 1];

  cal_weight(v, items);
  cout << a[0].rbegin()->val << endl;

  return 0;
}