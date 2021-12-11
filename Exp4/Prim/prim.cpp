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

void Prim(struct Graph *G); // Prim算法求最小生成树,时间复杂度为O(n^3)

void Prim(struct Graph *G) {
  // Prim算法求最小生成树,初始顶点默认选取第一个
  int i, j;
  int chosen[MAXVTXNUM] = {0}; //如果该顶点被划分过，则记为1
  int cnt;
  int vertex1 = 0; //储存最小权值的边对应的一顶点
  int vertex2 = 0;
  chosen[0] = 1; //默认初始顶点选取第一个
  for (cnt = 0; cnt < G->vtxnum - 1; cnt++) {
    int min = INFINITY;
    for (i = 0; i < G->vtxnum; i++) {
      if (chosen[i]) {
        for (j = 0; j < G->vtxnum; j++) {
          if (G->arcs[i][j] != 0 && !chosen[j] &&
              G->arcs[i][j] <
                  min) { //筛选最小权值的边,但不能选取到自己和已经选过的
            min = G->arcs[i][j];
            vertex1 = i;
            vertex2 = j;
          }
        }
      }
    }
    chosen[vertex2] = 1;
    Matrix[vertex1][vertex2] = Matrix[vertex2][vertex1] = min;
  }
  //改变G的邻接矩阵，得到最小生成树
  for (i = 0; i < G->vtxnum; i++) {
    for (j = 0; j < G->vtxnum; j++) {
      G->arcs[i][j] = Matrix[i][j];
    }
  }
}

int main() {
  ifstream fin;
  ofstream fout;
  fin.open("prim.in");
  fout.open("prim.out");
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
  Prim(&G);
  int sum = 0;
  for (int i = 0; i < V; i++) {
    for (int q = 0; q < V; q++) {
      sum += G.arcs[i][q];
    }
  }
  sum /= 2;
  fout << sum;
}