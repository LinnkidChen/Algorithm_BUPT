/* calculate closest (Euclidean distance) pair of points of all points in 2-dims
space
author:github.com/LinnkidChen
mail:linnkid.chen@gmail.com
*/

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
double clst_pair(vector<point> &set, int n);
int find_mid(vector<point> const &set); // return the mid value of x
double cal_dis(point a, point b);
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
  double dis;
  fin >> n;
  for (int i = 0; i < n; i++) {
    fin >> temp.x;
    fin >> temp.y;
    set.push_back(temp);
  }
  sort(set.begin(), set.end()); // pre-sort based on y in asending order
  dis = clst_pair(set, n);
  cout << "Min distance is " << setiosflags(ios::fixed) << setprecision(2)
       << dis << endl;
  fout << "Min distance is " << setiosflags(ios::fixed) << setprecision(2)
       << dis << endl;
  return 0;
}

double clst_pair(vector<point> &set, int n) {
  if (n < 2)
    return __DBL_MAX__;
  double returnval;
  if (n == 2) {
    returnval = cal_dis(set[0], set[1]);
    return returnval;
  }
  int mid_x = find_mid(set);
  vector<point> set1, set2;
  auto it = set.begin();
  for (; it != set.end(); it++) {
    if (it->x <= mid_x)
      set1.push_back(*it);
    else
      set2.push_back(*it);
  }
  double d1, d2;

  d1 = clst_pair(set1, set1.size());
  d2 = clst_pair(set2, set2.size());
  if (d1 > d2)
    d1 = d2;

  vector<point> p;
  auto it1 = set1.begin();
  auto it2 = set2.begin();
  while (!(it1 == set1.end() && it2 == set2.end())) {
    if (it1 == set1.end()) {
      p.push_back(*it2);
      it2++;
    } else if (it2 == set2.end()) {
      p.push_back(*it1);
      it1++;
    } else if (it1->y >= it2->y) {
      p.push_back(*it1);
      it1++;
    } else {
      p.push_back(*it2);
      it2++;
    }
  } // acending order of y in P
  double min_dis = -1;
  int count;
  double temp;
  for (it = p.begin(); it != p.end() - 1; it++) {
    count = 0;
    it1 = it + 1;
    while (count < 8 && it1 != p.end()) {
      if (it1->y - it->y > d1)
        break;
      temp = cal_dis(*it1, *it);
      if (temp < d1) {
        if (min_dis == -1 || temp < min_dis) {
          min_dis = temp;
        }
      }
      it1++;
      count++;
    }
  }
  if (min_dis != -1)
    returnval = min_dis;
  else
    returnval = d1;

  return returnval;
}

int find_mid(vector<point> const &set) {
  vector<int> x;
  auto it = set.begin();
  for (int t = 0; t < set.size(); t++) {
    x.push_back(it->x);
    it++;
  }
  sort(x.begin(), x.end());
  return x[(x.size() / 2) - 1];
}
double cal_dis(point a, point b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y + 0.0));
}