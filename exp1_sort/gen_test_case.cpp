/*
generationg test cases for sorting algorithms
*/

#include <fstream>
#include <iostream>
using namespace std;
#define len 1000
#define range 500
int main() {
  ofstream f_out;
  f_out.open("quicksort.in", fstream::out);
  if (f_out.is_open()) {
    f_out << len << endl;
    for (int i = 1; i <= len; i++) {
      f_out << rand() % range - range / 2 << " ";
      if (i % 10 == 0)
        f_out << endl;
    }
  } else
    cout << "Fail to open file" << endl;
}