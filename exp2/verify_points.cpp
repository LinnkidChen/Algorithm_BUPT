#include <algorithm>
#include <climits>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
struct point {
  int x;
  int y;
  bool operator<(const point &pt) const { return (y < pt.y); }
};
using namespace std;
double cal_dis(point a, point b) {
  return 1.0 * sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
int main() {
  vector<point> set;
  ifstream fin;
  ofstream fout;
  fin.open("point.in");

  if (!fin.is_open()) {
    cout << "fail to open file." << endl;
    exit(0);
  }
  point temp;
  int n;
  double dis;
  fin >> n;
  for (int i = 0; i < n; i++) {
    fin >> temp.x >> temp.y;
    set.push_back(temp);
  }
  double min_dis, relt;
  min_dis = cal_dis(set[0], set[1]);
  sort(set.begin(), set.end()); // pre-sort based on y in asending order
  for (auto it1 = set.begin(); it1 != set.end(); it1++) {
    for (auto it2 = it1 + 1; it2 != set.end(); it2++) {
      relt = cal_dis(*it1, *it2);
      if (relt < min_dis)
        min_dis = relt;
    }
  }
  cout << fixed << setprecision(6) << min_dis << endl;
  return 0;
}