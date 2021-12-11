#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;

struct treeNode {
  float weight;
  treeNode *left;
  treeNode *right;
  int len;
  bool visited;

  treeNode(float weight_ = 0, treeNode *left_ = NULL, treeNode *right_ = NULL) {
    left = left_;
    right = right_;
    weight = weight_;
    len = 0;
    visited = false;
  }
  bool isLeaf() { return (!left && !right); }
  bool operator>(treeNode const &obj) const { return weight > obj.weight; }
};
treeNode *build_hfm_tree(vector<float> &input,
                         vector<treeNode *> &tree_map); // return head_ptr
float cal_cost(treeNode *head, vector<treeNode *> &tree_map);
int main() {
  ifstream fin;
  ofstream fout;

  fin.open("huffman.in");
  fout.open("huffman.out");

  vector<float> input;
  int n;
  float temp, cost;

  fin >> n;
  for (int i = 0; i < n; i++) {
    fin >> temp;
    input.push_back(temp);
  }
  treeNode *head;
  vector<treeNode *> tree_map;
  head = build_hfm_tree(input, tree_map);
  cost = cal_cost(head, tree_map);
  fout << fixed << setprecision(3) << cost;
}
treeNode *find(vector<treeNode *> map, float val) {
  for (auto &i : map) {
    if (i->weight == val && !i->visited) {
      i->visited = true;
      return i;
    }
  }
  return NULL;
}
treeNode *build_hfm_tree(vector<float> &ipt, vector<treeNode *> &tree_map) {
  treeNode *left, *right, *temp_tn;

  float temp_f;
  // clang-format off
  priority_queue<float, vector<float>,
                 greater<float> > queue; // min heap
  // clang-format on

  for (auto &i : ipt) {
    queue.push(i);
    temp_tn = new treeNode(i);
    tree_map.push_back(temp_tn);
  }
  while (queue.size() > 1) {
    temp_f = queue.top();
    left = find(tree_map, queue.top());
    queue.pop();
    temp_f = queue.top();
    right = find(tree_map, queue.top());
    queue.pop();

    temp_f = right->weight + left->weight;
    temp_tn = new treeNode(temp_f, left, right);
    tree_map.push_back(temp_tn);
    queue.push(temp_f);
  }
  return temp_tn;
}

void cal_len(treeNode *cur, int cur_l) {
  cur->len = cur_l;
  if (cur->left)
    cal_len(cur->left, cur_l + 1);
  if (cur->right)
    cal_len(cur->right, cur_l + 1);
}
float cal_cost(treeNode *head, vector<treeNode *> &tree_map) {
  float cost = 0;
  cal_len(head, 0);
  for (auto &i : tree_map) {
    if (i->isLeaf()) {
      cost += i->len * i->weight;
    }
  }
  return cost;
}