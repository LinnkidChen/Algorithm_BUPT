/*
    Merge_sort
    using file "quicksort.in" as input
    the length of unsorted sequence N
    then enter the sequece {an}

    the output would be sorted into asending sequence
    output would be directed to file "quicksort.out"
    author: https://github.com/LinnkidChen
    mail: linnkid.chen@gmail.com
    2021-10-23 21:58:29
*/

#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

void quick_sort(vector<int> &seq, int begin, int end);
int partition(
    vector<int> &seq, int begin,
    int end); // partition the seq[begin:end] into <=x x >=x , return the
              // position of x(which is the seq[begin]in the origin seq)
int main() {
  int N;
  int input;
  clock_t timer;
  ifstream f_in;
  f_in.open("quicksort.in", ifstream::in);
  if (!f_in.is_open()) {
    cout << "fail to open file" << endl;
    exit(0);
  }

  ofstream f_out;
  f_out.open("quicksort.out", ofstream::out);
  if (!f_out.is_open()) {
    cout << "fail to open file" << endl;
    exit(0);
  }
  vector<int> seq;
  f_in >> N;
  for (int i = 0; i < N; i++) {
    f_in >> input;
    seq.push_back(input);
  }

  timer = clock();

  quick_sort(seq, 0, seq.size() - 1);
  timer = clock() - timer;
  double time_used = timer * 1000.0 / CLOCKS_PER_SEC;
  cout << "Time used " << time_used << " miliseconds\n";

  for (int i = 0; i < N; i++) {
    f_out << seq[i] << " ";
  }
}

void quick_sort(vector<int> &seq, int begin, int end) {
  if (begin < end) {
    int q = partition(seq, begin, end);

    for (int i = 0; i < seq.size(); i++)
      cout << seq[i] << " ";
    cout << endl;

    quick_sort(seq, begin, q - 1);
    quick_sort(seq, q + 1, end);
  }
}

int partition(vector<int> &seq, int begin, int end) {
  int left, right;
  int mid_val;
  int swap_temp;

  left = begin;
  right = begin + 1;
  mid_val = seq[left];
  while (right <= end) {
    if (seq[right] <= mid_val) {
      left++;
      swap_temp = seq[left];
      seq[left] = seq[right];
      seq[right] = swap_temp;
    }
    right++;
  }
  swap_temp = seq[begin];
  seq[begin] = seq[left];
  seq[left] = swap_temp;
  return left;
}