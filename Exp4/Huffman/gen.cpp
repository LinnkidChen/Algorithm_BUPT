#include <fstream>
#include <iostream>

using namespace std;
int main(int argc, char **argv) {
  ofstream fout;
  int N;
  fout.open("huffman.in");
  srand(time(0));
  int sum = 1000;
  int cur;
  if (argc > 1)
    sscanf(argv[1], "%d", &N);
  fout << N << endl;
  for (int i = 0; i < N - 1; i++) {
    cur = rand() % sum;
    sum -= cur;
    fout << cur * 0.001 << " ";
  }
  fout << sum * 0.001 << endl;
}