#include <fstream>
#include <iostream>

#define INFINITY 2147483647
#define MAXVTXNUM 20 //最大顶点个数
using namespace std;
struct Graph {
  int arcs[MAXVTXNUM][MAXVTXNUM] = {0}; //有权图，记录顶点关系和权值
  int vtxnum, arcnum;
};

int Matrix[MAXVTXNUM][MAXVTXNUM]; //辅助数组
int visited[MAXVTXNUM];           // dfs的标志访问数组
int VisitedNum
    [MAXVTXNUM]; //代表dfs中某个顶点被访问到的次数，如果大于1那么就是有环
int flag[MAXVTXNUM][MAXVTXNUM];
int NextAdj(Graph *G, int i, int j) {
  int k;
  for (k = j + 1; k < G->vtxnum; k++)
    if (k != i && flag[i][k] > 0)
      return k;
  return -1;
}
int FirstAdj(Graph *G, int i, int upper) {
  int j;
  for (j = 0; j < G->vtxnum; j++)
    if (flag[i][j] > 0 && j != upper)
      return j;
  return -1;
}
void dfs(
    Graph *G, int i,
    int upper) // upper表示该顶点的上层顶点，即由upper得到i，此时不能从i再遍历到upper
{
  //从第i个顶点出发递归深度优先遍历flag数组代表的邻接矩阵
  int temp = upper;
  VisitedNum[i]++;
  int v;
  for (v = FirstAdj(G, i, upper); v >= 0; v = NextAdj(G, i, v)) {
    if (VisitedNum[v] < 2) {
      upper = i;
      dfs(G, v, upper);
      upper = temp;
    }
  }
}
void DFSTraverse(Graph *G, int row) {
  int i, j;
  for (i = 0; i < G->vtxnum; i++)
    visited[i] = 0; //初始化visited数组
  dfs(G, row, -1);
}

int isLoop(
    int row, int col, Graph *G,
    int value) { //判断Matrix邻接矩阵加上边(row,col)权值为value代表的图是否成环
  int i, j;
  for (i = 0; i < G->vtxnum; i++) {
    for (j = 0; j < G->vtxnum; j++)
      flag[i][j] = Matrix[i][j];
    VisitedNum[i] = 0; //初始化顶点访问次数数组
  }
  flag[row][col] = flag[col][row] =
      value; //使用辅助矩阵，预先选取这条边，看是否组成回路
  DFSTraverse(G, row);
  if (VisitedNum[row] == 2)
    return 1;
  return 0;
}
void Kruskal(Graph *G) {
  int i, j, col, row;
  int cnt;
  //一轮大循环筛选出一条最小权值的边
  for (cnt = 0; cnt < G->arcnum; cnt++) {
    int min = INFINITY;
    for (i = 0; i < G->vtxnum; i++) {
      for (j = 0; j < G->vtxnum; j++) {
        if (G->arcs[i][j] != 0 && G->arcs[i][j] < min && !Matrix[i][j]) {
          row = i;
          col = j;
          min = G->arcs[i][j];
        }
      }
    }
    //判断是否成环
    if (!isLoop(row, col, G, min)) {
      Matrix[row][col] = Matrix[col][row] = min;
    } else {
      Matrix[row][col] = Matrix[col][row] =
          -1; //选取的边构成回路，那么不能再重复选取这条边
    }
  }
  //改变G的邻接矩阵，得到最小生成树
  for (i = 0; i < G->vtxnum; i++) {
    for (j = 0; j < G->vtxnum; j++) {
      if (Matrix[i][j] != -1) {
        G->arcs[i][j] = Matrix[i][j];
      } else {
        G->arcs[i][j] = 0;
      }
    }
  }
}
int main() {
  ifstream fin;
  ofstream fout;
  fin.open("kruskal.in");
  fout.open("kruskal.out");
  struct Graph G;
  int V, E;
  int lft, rgt, wgt;
  fin >> V >> E;
  G.vtxnum = V;
  G.arcnum = E;
  for (int i = 0; i < E; i++) {
    fin >> lft >> rgt >> wgt;
    lft--;
    rgt--;
    G.arcs[lft][rgt] = wgt;
    G.arcs[rgt][lft] = wgt;
  }
  Kruskal(&G);
  int sum = 0;
  for (int i = 0; i < V; i++) {
    for (int q = 0; q < V; q++) {
      sum += G.arcs[i][q];
    }
  }
  sum /= 2;
  fout << sum;
}