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
  bool operator>(const node &obj) const { return weight > obj.weight; }
  bool operator<(const node &obj) const { return weight < obj.weight; }
  int weight;
  int val;
};

using namespace std;
list<node> *a;
void clear_point(list<node> &set) {
  list<node>::iterator it = set.begin();
  list<node>::iterator it_ = it;
  it_++;
  while (it_ != set.end()) {
    if (it->weight <= it_->weight && it->val > it_->val) {
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
  list<node> temp_q, temp;
  auto it = items.rbegin();

  temp_q.push_back(temp_node + *it);

  for (int i = items.size() - 1; i >= 0; i--) {
    temp = a[i + 1];
    temp_q.merge(temp);

    clear_point(temp_q);
    a[i] = temp_q;
    temp_q.clear();
    it++;
    for (const auto &it_ : a[i]) {
      temp_node = (it_ + *it);
      if (temp_node.weight <= j)
        temp_q.push_back(temp_node);
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