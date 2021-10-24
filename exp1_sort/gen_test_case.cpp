/*
generationg test cases for sorting algorithms
*/

#include <fstream>
#include <iostream>
using namespace std;
#define len 8
#define range 20
int main() {
  ofstream f_out;
  f_out.open("quicksort.in", fstream::out);
  if (f_out.is_open()) {
    f_out << len << endl;
    for (int i = 0; i < len; i++) {
      f_out << rand() % range - range / 2 << " ";
    }
  } else
    cout << "Fail to open file" << endl;
}