#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;

struct treeNode {
  treeNode *left;
  treeNode *right;
  float weight;
  treeNode(float weight_ = 0, treeNode *left_ = NULL, treeNode *right_ = NULL) {
    left = left_;
    right = right_;
    weight = weight_;
  }
  bool isLeaf() { return (!left && !right); }
  bool operator>(treeNode const &obj) const { return weight > obj.weight; }
};
treeNode *build_hfm_tree(vector<int> &input); // return head_ptr
int main() {
  ifstream fin;
  ofstream fout;

  fin.open("huffman.in");
  fout.open("huffman.out");

  vector<int> input;
  int n;
  float temp;

  fin >> n;
  for (int i = 0; i < n; i++) {
    fin >> temp;
    input.push_back(temp);
  }
  treeNode *head;
  head = build_hfm_tree(input);
}
treeNode *build_hfm_tree(vector<float> &ipt) {
  treeNode *left, *right, *temp_tn;
  map<float, treeNode *> tree_map;
  float temp_f;
  priority_queue<float, vector<float>, greater<float>> queue; // min heap

  for (auto &i : ipt) {
    queue.push(i);
    tree_map[i] = new treeNode(i);
  }
  while (queue.size() > 1) {
    left = tree_map[queue.top()];
    queue.pop();
    right = tree_map[queue.top()];
    queue.pop();

    temp_f = right->weight + left->weight;
    temp_tn = new treeNode(temp_f, left, right);

    queue.push(temp_f);
  }
  return temp_tn;
}
