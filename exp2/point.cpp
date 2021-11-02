/* calculate closest (Euclidean distance) pair of points of all points in 2-dims
space
author:github.com/LinnkidChen
mail:linnkid.chen@gmail.com
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
struct point {
  int x;
  int y;
  bool operator<(const point &pt) const { return (y < pt.y); }
};
using namespace std;
double clst_pair(vector<point> &set, int n);
int main() {
  vector<point> set;
  ifstream fin;
  ofstream fout;
  fin.open("point.in");
  fout.open("point.out");
  if (!fin.is_open() || !fout.is_open()) {
    cout << "fail to open file." << endl;
    exit(0);
  }
  point temp;
  int n;
  float dis;
  fin >> n;
  for (int i = 0; i < n; i++) {
    fin >> temp.x >> temp.y;
    set.push_back(temp);
  }
  sort(set.begin(), set.end()); // pre-sort based on y in asending order
  dis = clst_pair(set, n);
  cout << "Min distance is " << dis << endl;
  return 0;
}

double clst_pair(vector<point> &set, int n) {
  if (n < 2)
    return false;
}
