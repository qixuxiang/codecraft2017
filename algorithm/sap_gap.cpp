#include <cstdio>
#include <queue>
#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100010;
int n, m;
struct Edge{
      int cap, to;
      int next;
}edge[N * 4];

int head[N], cnt, ans, des, src;
int gap[N], curedge[N], d[N], pre[N], que[N];

void bfs(){
  memset(d, -1, sizeof(d));
  memset(gap, 0, sizeof(gap));
  gap[0] = 1;
  int front = 0, rear = 0;
  d[des] = 0;
  que[rear++] = des;
  while(front != rear){
      int deq = que[front++];
      front = front % N;
      for (int it = head[deq]; it != -1; it = edge[it].next){
          int e = edge[it].to;
          if (edge[it].cap != 0 || d[e] != -1)
              continue;
          que[rear++] = e;
          rear = rear % N;
          ++gap[d[e] = d[deq] + 1];
      }
  }
}

struct ISAP{
  // gap:统计高度数量数组；d:距离标号数组;
  // curedges:当前弧数组;pre:前驱数组
  void initi(){
      fill(d + 1, d + n + 1, 0);
      fill(pre + 1, pre + n + 1, -1);
      fill(head + 1, head + n + 1, -1);
      ans = 0; //初始化最大流为0
      cnt = 0;
  }
  void addedge(int a, int b, int c){    //有向图加边。
      edge[cnt].to = b, edge[cnt].cap = c;
      edge[cnt].next = head[a], head[a] = cnt++;
      edge[cnt].to = a, edge[cnt].cap = 0;
      edge[cnt].next = head[b], head[b] = cnt++;
  }
  int max_flow(int start, int end){
      int i, u, tmp, neck;
      bfs();
      for(i = 1;i <= n;i++)
          curedge[i] = head[i];    //初始化当前弧为第一条邻接边
      u = start;
      while(d[start] < n){        //当d[start] >= n,网络中肯定出现了gap
          if(u == end){            //增广成功，寻找瓶颈边
              int min_flow = INT_MAX;
              for(i = start;i != end;i = edge[curedge[i]].to){
                  if(min_flow > edge[curedge[i]].cap){
                      neck = i;
                      min_flow = edge[curedge[i]].cap;
                  }
              }

              for(i = start;i != end;i = edge[curedge[i]].to){//更新正反向弧流量
                  tmp = curedge[i];
                  edge[tmp].cap -= min_flow;
                  edge[tmp ^ 1].cap += min_flow;
              }
              ans += min_flow;
              u = neck;        //下次增广从瓶颈边开始
          }
          for(i = curedge[u];i != -1;i = edge[i].next)
              if(edge[i].cap&&d[u] == d[edge[i].to] + 1)        //寻找可行弧
                  break;
          if(i != -1){
              curedge[u] = i;
              pre[edge[i].to] = u;
              u = edge[i].to;
          } else {
              if(--gap[d[u]] == 0)
                  break;
              curedge[u] = head[u];
              for(tmp = n, i = head[u];i != -1;i = edge[i].next)
                  if(edge[i].cap)
                      tmp = std::min(tmp, d[edge[i].to]);
              d[u] = tmp + 1;
              ++gap[d[u]];
              if(u != start)
                  u = pre[u];    //重标号并且从当前点前驱重新增广
          }
      }
      return ans;
  }
}g;

int main(){
  int T;
  cin >> T;
  while(T--){
      int i, a, b, c, sd = INT_MAX, dd = INT_MIN, x, y;
      cin>>n>>m;
      //scanf("%d%d", &n, &m);
      g.initi();
      for(i = 1;i <= n;i++){
          //scanf("%d%d", &x, &y);
          cin>>x>>y;
          if(sd > x){
              src = i;
              sd = x;
          }
          if(dd < x){
              des = i;
              dd = x;
          }
      }
      for(i = 0;i < m;i++){
          //scanf("%d%d%d", &a, &b, &c);
          cin>>a>>b>>c;
          g.addedge(a, b, c);
          g.addedge(b, a, c);
      }
      cout<<"maxflw is :"<<g.max_flow(src, des)<<endl;
      //printf("%d\n", g.max_flow(src, des));
  }
  return 0;
}
