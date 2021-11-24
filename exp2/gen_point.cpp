#include <ctime>
#include <fstream>
#include <iostream>
using namespace std;
#define N 80
#define Range 2000
int main() {
  ofstream fout;
  srand(time(NULL));
  fout.open("point.in");
  fout << N << endl;
  for (int i = 0; i < N; i++) {
    fout << rand() % (2 * Range) - Range << " " << rand() % (2 * Range) - Range
         << endl;
  }
}