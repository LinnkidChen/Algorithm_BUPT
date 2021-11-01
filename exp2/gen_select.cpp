#include <ctime>
#include <fstream>
#include <iostream>
using namespace std;
#define N 200
#define K 7
#define Range 200
int main() {
  ofstream fout;
  srand(time(NULL));
  fout.open("select.in");
  fout << N << " " << K << endl;
  for (int i = 0; i < N; i++) {
    fout << rand() % (2 * Range) - Range << " ";
  }
}