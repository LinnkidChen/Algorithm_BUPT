#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
int main() {
  ofstream fout;
  ifstream fin;
  vector<int> seq;
  fout.open("sorted.txt");
  fin.open("select.in");
  int n, k;
  int temp;
  fin >> n >> k;
  for (int i = 0; i < n; i++) {
    fin >> temp;
    seq.push_back(temp);
  }
  sort(seq.begin(), seq.end());
  for (int i = 0; i < n; i++) {
    fout << seq[i] << " ";
  }
  cout << seq[k - 1] << endl;
  return 0;
}