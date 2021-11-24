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
void cal_weight(int i, int j, vector<item> &items) {
  if (j >= items[i].weight) {
    if (a[i + 1][j] == 0)
      cal_weight(i + 1, j, items);
    if (a[i + 1][j - items[i].weight] == 0)
      cal_weight(i + 1, j - items[i].weight, items);
  }
}
int dyn_bag(vector<item>) { return 0; }
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
  a = new int *[v];
  for (int i = 0; i < v; i++) {
    a[i] = new int[n];
    for (int q = 0; q < n; q++) {
      a[i][q] = 0;
    }
  }

  return 0;
}