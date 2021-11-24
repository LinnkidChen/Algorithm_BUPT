#include <cstddef>
#include <fstream>
#include <iostream>
#include <list>
#include <utility>
#include <vector>
struct item {
  int val;
  int weight;
};
struct node {
  int val;
  int itm;
};

using namespace std;
list<node> *a;
int cal_weight(int j, vector<item> &items) {
  for (int itm = items.size() - 1; itm >= 0; itm--) {
    for (int cap = j; cap >= 0; cap--) {
      if (itm == items.size() - 1) {
        if (cap >= items[itm].weight) {
          a[itm][cap] = items[itm].val;
        } else
          a[itm][cap] = -1;
      } else {
        if (items[itm].weight > cap) {
          a[itm][cap] = a[itm + 1][cap];
        } else {
          a[itm][cap] =
              max(a[itm + 1][cap],
                  a[itm + 1][cap - items[itm].weight] + items[itm].val);
        }
      }
    }
    cout << endl;
  }
  return 0;
}

int main() {
  int v, n;
  vector<item> items;
  item temp_itm;
  ifstream fin;
  fin.open("bag.in");

  fin >> v >> n;
  for (int i = 0; i < n; i++) {
    fin >> temp_itm.weight >> temp_itm.val;
    items.push_back(temp_itm);
  }

  a = new list<node>[n];

  cal_weight(v, items);
  cout << a[0][v].rbegin()->val << endl;

  return 0;
}