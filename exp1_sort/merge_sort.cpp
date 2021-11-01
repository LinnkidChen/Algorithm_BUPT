/*
    Merge_sort
    using file "mergesort.in" as input
    the length of unsorted sequence N
    then enter the sequece {an}

    the output would be sorted into asending sequence
    output would be directed to file "mergesort.out"
    author: https://github.com/LinnkidChen
    mail: linnkid.chen@gmail.com
    2021-10-23 21:58:29
*/

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

#define MAXN 1000010
#define range 200000
using namespace std;

void Merge_sort(vector<int> &seq);
void Merge(vector<int> &seq, int begin, int i, int end);
int main() {
  clock_t timer;
  int N;
  int input;
  ifstream f_in;
  f_in.open("mergesort.in", ifstream::in);
  if (!f_in.is_open()) {
    cout << "fail to open file" << endl;
    exit(0);
  }

  ofstream f_out;
  f_out.open("mergesort.out", ofstream::out);
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

  Merge_sort(seq);
  timer = clock() - timer;
  double time_used = timer * 1000.0 / CLOCKS_PER_SEC;
  cout << "Time used " << time_used << " miliseconds\n";

  for (int i = 0; i < N; i++) {
    f_out << seq[i] << " ";
    if ((i + 1) % 10 == 0)
      f_out << endl;
  }
}

// void Merge_sort(vector<int> &seq, int begin, int end) {
//   if (begin < end) { // at least 2 elements in array
//     int i = (begin + end) / 2;
//     Merge_sort(seq, begin, i);
//     Merge_sort(seq, i + 1, end);
//     // seq[begin:i] and seq[i+1: end ] is sorted
//     vector<int> temp;
//     int left, right;
//     left = begin;
//     right = i + 1;
//     while (left <= i && right <= end) { // both array do not reach to end
//       if (seq[left] <= seq[right]) {
//         temp.push_back(seq[left]);
//         left++;
//       } else {
//         temp.push_back(seq[right]);
//         right++;
//       }
//     }
//     while (left <= i) {
//       temp.push_back(seq[left]);
//       left++;
//     }
//     while (right <= end) {
//       temp.push_back(seq[right]);
//       right++;
//     }

//     vector<int>::iterator it;
//     it = temp.begin();
//     for (int i = begin; i <= end; i++) {
//       seq[i] = *it;
//       it++;
//     }
//   }
//   //   for (int i = 0; i < seq.size(); i++) {
//   //     cout << seq[i] << " ";
//   //   }
//   //   cout << endl;
// }

void Merge_sort(vector<int> &seq) {
  int cur_size = 1;
  while (cur_size < 2 * seq.size()) {
    for (; cur_size < seq.size(); cur_size *= 2) {
      for (int left = 0; left < seq.size(); left += 2 * cur_size) {
        int mid = left + cur_size;
        int right = mid + cur_size - 1;
        if (right >= seq.size())
          right = seq.size() - 1;
        Merge(seq, left, mid, right);
      }
    }
    cur_size *= 2;
  }
}
void Merge(vector<int> &seq, int begin, int i, int end) {
  vector<int> temp;
  int left, right;
  left = begin;
  right = i;
  while (left < i && right <= end) { // both array do not reach to end
    if (seq[left] <= seq[right]) {
      temp.push_back(seq[left]);
      left++;
    } else {
      temp.push_back(seq[right]);
      right++;
    }
  }
  while (left < i) {
    temp.push_back(seq[left]);
    left++;
  }
  while (right <= end) {
    temp.push_back(seq[right]);
    right++;
  }

  vector<int>::iterator it;
  it = temp.begin();
  for (int i = begin; i <= end; i++) {
    seq[i] = *it;
    it++;
  }
}
