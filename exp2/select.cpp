/* select the kth small element in an unsorted sequence

author : github.com/LinnkidChen
mail: linnkid.chen@gmail.com
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#define GRP_SIZ 5
// determing which algorithm to use
// n<75, use sort
// n>=75 use linear time select alg
using namespace std;
int partition(vector<int> &seq, int lft, int rgt, int x);
int select(vector<int> &seq, int k, int lft, int rgt);
void sort_mid(vector<int> &seq, int lft, int rgt);
int main() {
  ifstream fin;

  fin.open("select.in");
  if (!fin.is_open()) {
    cout << "fail to open file" << endl;
    exit(0);
  }

  int n, k;
  int temp;
  vector<int> seq;
  fin >> n >> k;
  for (int i = 0; i < n; i++) {
    fin >> temp;
    seq.push_back(temp);
  }

  temp = select(seq, k, 0, n - 1);
  cout << temp;

  return 0;
}
int select(vector<int> &seq, int k, int lft, int rgt) {
  if (rgt - lft < 75) {
    sort(seq.begin() + lft, seq.begin() + rgt);
    return seq[lft + k - 1];
  }
  int temp;
  for (int i = 0; i <= (rgt - lft - 4) / 5; i++) {
    sort(seq.begin() + lft + 5 * i, seq.begin() + lft + 5 * i + 4);
    temp = seq[lft + 5 * i + 2];
    seq[lft + 5 * i + 2] = seq[lft + i];
    seq[lft + i] = temp;
  }
  temp = select(seq, (rgt - lft - 4) / 10, lft, lft + (rgt - lft - 4) / 5);
  int i = partition(seq, lft, rgt, temp);
  int j = i - lft + 1;
  if (k <= j)
    return select(seq, k, lft, i);
  else
    return select(seq, k - j, i + 1, rgt);
}
int partition(vector<int> &seq, int lft, int rgt, int x) {
  int i, j;
  i = lft;
  j = rgt;
  while (i < j) {
    if (seq[i] > x) {
      while (i < j && seq[j] > x)
        j--;
      if (i != j) {
        int q = seq[i];
        seq[i] = seq[j];
        seq[j] = q;
        j--;
      }
    }
    i++;
  }
  return i - 1;
}
