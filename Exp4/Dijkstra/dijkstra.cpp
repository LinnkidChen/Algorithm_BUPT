
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#define INF INT_MAX - 1
using namespace std;
struct Map_arc {
  // travel time = density*distance/speed
  int node; //当前边指向的顶点地址

  int weight; //用于寻找路径时判断大小的权重
  Map_arc(int weight_, int node_) {
    weight = weight_;
    node = node_;
  }
}; //无向有权图的边
struct Map_node {

  struct Map_node *next_node; //图的下一个顶点
  list<Map_arc> arc;          //图的第一条边

  bool nav_visited; // dijstra搜索时确定是否确定最短路径
  int number;       //节点编号
  int sum_weight;   //记录起始节点到每个节点的当前的weight之和
  Map_node(int i_) {
    number = i_;
    next_node = NULL;
    nav_visited = false;
    sum_weight = INF;
  }
}; //无向有权图的顶点
int dij_find_next_node(vector<Map_node> &loc_node) {
  int min_weight;
  int loc = 0;

  if (!loc_node.empty())
    min_weight = loc_node[0].sum_weight;
  for (int i = 0; i < loc_node.size(); i++) {
    if (loc_node[i].sum_weight < min_weight && !loc_node[i].nav_visited) {
      loc = i;
      min_weight = loc_node[i].sum_weight;
    }
  }
  return loc;
}
int find_min_path(int begin, int end, vector<Map_node> &loc_node) {
  int temp_path[loc_node.size()]; //记录每个起始节点到每个其他节点的路径
  int cur_wei_sum;
  int c_nd;
  c_nd = begin;
  loc_node[c_nd].sum_weight = 0;
  for (int i = 0; i < loc_node.size(); i++) {
    auto c_car = loc_node[c_nd].arc.begin();
    while (c_car != loc_node[c_nd].arc.end()) {
      cur_wei_sum = loc_node[c_nd].sum_weight + c_car->weight;
      if (cur_wei_sum < loc_node[c_car->node].sum_weight) {
        loc_node[c_car->node].sum_weight = cur_wei_sum;
        temp_path[c_car->node] = c_nd;
      }
      c_car++;
    }
    loc_node[c_nd].nav_visited = true;
    c_nd = dij_find_next_node(loc_node);
    if (c_nd == end)
      break;
  }
  return loc_node[end].sum_weight;
}

int main() {
  ifstream fin;
  ofstream fout;
  fin.open("dijkstra.in");
  fout.open("dijkstra.out");
  int lft, rgt, wgt;
  int V, E;
  fin >> V >> E;
  vector<Map_node> loc_node;
  for (int i = 0; i < V; i++) {
    loc_node.push_back(Map_node(i));
  }
  for (int i = 0; i < E; i++) {
    fin >> lft >> rgt >> wgt;
    lft--;
    rgt--;
    loc_node[lft].arc.push_back(Map_arc(wgt, rgt));
    loc_node[rgt].arc.push_back(Map_arc(wgt, lft));
  }
  int cost = find_min_path(0, V - 1, loc_node);
  fout << cost;
}
