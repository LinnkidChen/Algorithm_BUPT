/* select the kth small element in an unsorted sequence

author : github.com/LinnkidChen
mail: linnkid.chen@gmail.com
*/

#include <fstream>
#include <iostream>
#include <vector>
#define GRP_SIZ 5
#define PARTI 75 // determing which algorithm to use
// n<75, use sort
// n>=75 use linear time select alg
using namespace std;
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

  if (n < PARTI) {
    sort(seq.begin(), seq.end());
    cout << seq[k - 1];
  } else {
  }
  return 0;
}