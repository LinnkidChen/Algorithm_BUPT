#include <ctime>
#include <fstream>
#include <iostream>
using namespace std;
#define N 5
#define Range 20
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