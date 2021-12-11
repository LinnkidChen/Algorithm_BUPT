#include <stdio.h>
#define INFINITY 2147483647
#define MAXVTXNUM 20 //最大顶点个数

typedef struct {
  char vexs[MAXVTXNUM];           //存储图中顶点的数据
  int arcs[MAXVTXNUM][MAXVTXNUM]; //有权图，记录顶点关系和权值
  int vtxnum, arcnum;
} Graph;

Graph G;
int Matrix[MAXVTXNUM][MAXVTXNUM]; //辅助数组
int visited[MAXVTXNUM];           // dfs的标志访问数组
int VisitedNum
    [MAXVTXNUM]; //代表dfs中某个顶点被访问到的次数，如果大于1那么就是有环
int flag[MAXVTXNUM][MAXVTXNUM];

void CreateGraph(Graph *G); //建立图G
void InitMatrix(void);      //初始化辅助数组
void PrintGraph(Graph *G);  //打印图的邻接矩阵
void Prim(Graph *G); // Prim算法求最小生成树,时间复杂度为O(n^3)
void Kruskal(Graph *G); // Kruskal算法求最小生成树，时间复杂度为O(n^3)
void DeleteArc(Graph *G); //去边法求最小生成树，时间复杂度为O(n^3)
int isLoop(int row, int col, Graph *G, int value); //判断邻接矩阵是否产生回路
void DFSTraverse(Graph *G, int row);               //深度优先搜索
void dfs(Graph *G, int i, int upper);              //深度优先搜索
int FirstAdj(Graph *G, int i, int upper); //求相对于顶点i的第一个邻接点
int NextAdj(Graph *G, int i, int j); //求顶点i在其邻接点j后的下一个邻接点
int isConnected(int row, int col, Graph *G); //判断图是否是连通图

void CreateGraph(Graph *G) {
  //采用邻接矩阵构造无向有权图G
  printf("输入图的顶点数和边数,中间用空格分隔\n");
  scanf("%d%d", &(G->vtxnum), (&G->arcnum));

  int i, j;
  printf("按顺序输入图顶点的信息(以字符串形式输入):\n");
  scanf("%s", (G->vexs));

  printf("按刚刚输入顶点信息的顺序继续输入顶点的关系和权值:\n");
  for (i = 0; i < G->vtxnum; i++)
    for (j = 0; j < G->vtxnum; j++)
      scanf("%d", &(G->arcs[i][j]));
  printf("构造完毕\n");
}

void InitMatrix() //辅助数组的初始化函数
{
  int i, j;
  for (i = 0; i < MAXVTXNUM; i++)
    for (j = 0; j < MAXVTXNUM; j++)
      Matrix[i][j] = 0;
}

void Prim(Graph *G) {
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
  PrintGraph(G);
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
  PrintGraph(G);
}

void DeleteArc(Graph *G) {
  int i, j, col, row;
  int cnt;
  int chosen[MAXVTXNUM][MAXVTXNUM]; //该边如果被选择过，就不再被选择
  for (i = 0; i < G->vtxnum; i++) {
    for (j = 0; j < G->vtxnum; j++) {
      Matrix[i][j] = G->arcs[i][j];
      chosen[i][j] = 0;
    }
  }
  //一轮大循环筛选出一条最大权值的边,然后标记它让它不再被选择
  for (cnt = 0; cnt < G->arcnum; cnt++) {
    int max = -INFINITY;
    for (i = 0; i < G->vtxnum; i++) {
      for (j = 0; j < G->vtxnum; j++) {
        if (G->arcs[i][j] != 0 && G->arcs[i][j] > max && Matrix[i][j] &&
            !chosen[i][j]) {
          row = i;
          col = j;
          max = G->arcs[i][j];
        }
      }
    }
    if (!isConnected(row, col, G)) {
      Matrix[row][col] = Matrix[col][row] =
          max; //删除的边让图不连通，故要保留这条边,但之后不再遍历这条边
    } else {
      Matrix[row][col] = Matrix[col][row] = -1;
    }
    chosen[row][col] = chosen[col][row] = 1; //被选择标记
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
  PrintGraph(G);
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

int isConnected(
    int row, int col,
    Graph *
        G) { //判断Matrix对应的邻接矩阵去掉row和col对应的边后是否还连通，如果不连通，返回0
  int i, j;
  for (i = 0; i < G->vtxnum; i++) {
    for (j = 0; j < G->vtxnum; j++)
      flag[i][j] = Matrix[i][j];
    VisitedNum[i] = 0; //初始化顶点访问次数数组
                       //,如果一轮中每个顶点都能遍历到一次，那么构成回路
  }
  flag[row][col] = flag[col][row] = 0;
  DFSTraverse(
      G, 0); //只要任意选择一个起始顶点，如果DFS不能遍历每个点，那么就是非连通图
  for (i = 0; i < G->vtxnum; i++)
    if (VisitedNum[i] == 0)
      break;
  if (i == G->vtxnum)
    return 1;
  else
    return 0;
}

void DFSTraverse(Graph *G, int row) {
  int i, j;
  for (i = 0; i < G->vtxnum; i++)
    visited[i] = 0; //初始化visited数组
  dfs(G, row, -1);
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

int FirstAdj(Graph *G, int i, int upper) {
  int j;
  for (j = 0; j < G->vtxnum; j++)
    if (flag[i][j] > 0 && j != upper)
      return j;
  return -1;
}

int NextAdj(Graph *G, int i, int j) {
  int k;
  for (k = j + 1; k < G->vtxnum; k++)
    if (k != i && flag[i][k] > 0)
      return k;
  return -1;
}

void PrintGraph(Graph *G) {
  int i, j;
  for (i = 0; i < G->vtxnum; i++) {
    for (j = 0; j < G->vtxnum; j++)
      printf("%d ", G->arcs[i][j]);
    printf("\n");
  }
}

int main() {
  Graph G;
  CreateGraph(&G);
  InitMatrix();
  int method; //采用的方法,1表示Prim算法，2表示Kruskal算法，3表示去边法
  printf(
      "请输入想使用的算法对应的序号：\n1、Prim\n2、Kruskal\n3、去边法\n"); //分成函数
  scanf("%d", &method);
  if (method == 1)
    Prim(&G);
  else if (method == 2)
    Kruskal(&G);
  else if (method == 3)
    DeleteArc(&G);
  return 0;
}
