#include <cstddef>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

struct item {
  int val;
  int weight;
};
int **a;
using namespace std;
int cal_weight(int j, vector<item> &items) {
  for (int itm = items.size() - 2; itm >= 0; itm--) {
    for (int cap = j; cap >= 0; cap--) {

      if (items[itm].weight > cap) {
        a[itm][cap] = a[itm + 1][cap];
      } else {
        a[itm][cap] = max(a[itm + 1][cap],
                          a[itm + 1][cap - items[itm].weight] + items[itm].val);
      }
      // cout << a[itm][cap] << " ";
    }
    // cout << endl;
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
  a = new int *[n];
  for (int i = 0; i < n; i++) {
    a[i] = new int[v];
    for (int q = 0; q < v; q++) {
      a[i][q] = 0;
    }
  }
  cal_weight(v, items);
  cout << a[0][v] << endl;

  return 0;
}