//Program HighestLablePreflowPush;HLPP

// 较快的网络流算法

//最高标号预留与推进算法

//记录d值，然后优先处理d值较高的，直至没有盈余。

// poj1459 Power Network

#include<cstdio>

#include<iostream>

#include<queue>

#include<algorithm>

#define maxn 105

#define max  210

using namespace std;



typedef struct node

{

     int num;

     int a[maxn];

}node;



int n,s,t,maxflow;

int map[maxn][maxn];        //边容量矩阵

int edge[maxn][maxn];       //邻接矩阵

int cur[maxn],d[maxn],e[maxn];

struct node list[2*maxn-1];

int flag;



void pagheuristic();

void insert(int level,int x)//加入标号为level的节点x

{    int num;

     list[level].num++;

     num = list[level].num;

     list[level].a[num] = x;

}

void BFS()//精确计算距离标号dijkstra 建层次表

{

     int p,q;int x[maxn];int i;

     fill(d,d+maxn,max);

     x[1] = t; d[t] = 0; q = 1; p = 0;

     while(p<q)

     {

         p++;

         for(i = 1; i <= edge[x[p]][0]; i++)

              if(d[ edge[x[p]][i] ] == max){

                   q++;

                   x[q] = edge[x[p]][i];

                   d[x[q]] = d[x[p]] + 1;

                   if(x[q] != s) insert(d[x[q]],x[q]);

              }

     }

     d[s] = n;

}

void push(int a,int b)

{

     int x;

     if(map[a][b] > e[a]) x = e[a];

     else x = map[a][b];

     map[a][b] -= x;

     map[b][a] += x;

     e[a] -= x;

     e[b] += x;

}

void relabel(int a)

{

     int i,min = max;

     for(i = 1; i <= edge[a][0]; i++)

         if(map[a][edge[a][i]] > 0 && d[edge[a][i]] < min)

              min = d[edge[a][i]];

     d[a] = min + 1;

     if(flag++ % n == 0) pagheuristic(); //此处加优化

}

bool check(int a)//discharge

{    bool chk = false;

     while(e[a] > 0)

     {

         if(cur[a] > edge[a][0]){

              relabel(a); chk = true; cur[a] = 1;

         }

         else if(map[a][ edge[a][cur[a]] ] > 0 && d[a] == d[ edge[a][cur[a]] ] + 1)

              push(a,edge[a][cur[a]]);//j = edge[a][cur[a]] -> b是a第j 个邻接点

         else cur[a]++;

     }

     return chk;

}

void update(int level)//将所有标号在level上的点抛上九天,会不会就是pagheuristic

{

     int j,k;

     for(j = level+1; j <= n; j++){

         for(k = 1; k <= list[j].num; k++){

              list[n+1].a[list[n+1].num + k] = list[j].a[k];

              d[list[j].a[k]] = n+1;

         }

         list[n+1].num += list[j].num;

         list[j].num = 0;

     }

}

void HLPP()

{

     int i,b,level;

     fill(e,e+maxn,0);

     for(i = 1; i <= edge[s][0]; i++){//将所有s出发的弧充满

         b = edge[s][i];

         e[b] = map[s][b];

         e[s] -= map[s][b];

         map[b][s] = e[b];

         map[s][b] = 0;

     }

     level = n;flag = 0;

     while(level)

     {

         level--;

         for(i = list[level].num; i >= 1; i--){

              int a = list[level].a[i]; int num = list[level].num;

              if(check(a)){                                                //如果有被重标记

                   if(level > 0 &&  list[level].num == 1) update(level);//免除把余流送回S的操作,该层只剩下一个点将要断层才可update，因为在层次图中如果断层，则断层上的顶点有留流，它必流回S，这时不用再计算，把它上放到n+1 层上去

                   insert(d[a],a);

                   list[level].a[i] = list[level].a[num];                  //有标记过则排除该点，把后面没标记的移到前面来

                   list[level].num--;

                   level = d[a];                                           //level 回升

                   break;                                                       //从新的最高level重新开始

              }

         }

     }

}

int main()

{    void input(int node,int np,int nc,int m);

     void init();

     int node,np,nc,m;

     while(scanf("%d%d%d%d",&node,&np,&nc,&m)==4)

     {

         input(node,np,nc,m);

         init();

         BFS();

         HLPP();

         maxflow = e[t];

         printf("%d/n",maxflow);

     }

     return 0;

}

void init()

{

     int i,j;

     memset(edge,0,sizeof edge);

     for(i = 0; i < n; i++)

         for(j = i+1; j <= n; j++)

              if(map[i][j]||map[j][i]){//建立邻接矩阵

                   edge[i][0]++;

                   edge[j][0]++;

                   edge[i][edge[i][0]] = j;

                   edge[j][edge[j][0]] = i;

              }

     fill(cur,cur+maxn,1);

     for(i = 0; i <= n+1; i++) list[i].num = 0;

}

void input(int node,int np,int nc,int m)//complete map,mark s t n

{    int a,b,cap;int i;

     n = node+1;

     s = 0; t = node+1; maxflow = 0;

     fill(map[0],map[maxn],0);

     for (i = 0 ; i < m  ;i++)

     {

         while(getchar()!='(');

         scanf("%d,%d)%d",&a,&b,&cap);

         map[a+1][b+1] = cap;

     }

     for (i = 0 ; i < np ; i++)

     {

         while(getchar()!='(');

         scanf("%d)%d",&b,&cap);

         map[s][b+1] = cap;

     }

     for (i = 0 ; i < nc ; i++)

     {

         while(getchar()!='(');

         scanf("%d)%d",&b,&cap);

         map[b+1][t] = cap;

     }

}

//距离标号法与重标记与前移算法容易退化，所以加一个优化pagheuristic——若存在某一个k(k<n)，

//没有距离标号为k的点，则可以将标号为k--n的所有点移到标号为n+1，以此来提高效率。

//这个优化在relable时可以使用，为了节省时间，可以选在每k*n次检查一次。

void pagheuristic()

{

     int count[maxn*2];

     int i,j;

     fill(count,count+2*maxn,0);

     for(i = 1; i <= n; i++) count[d[i]]++;

     j = 1;

     while(j < n && count[j] != 0) j++;

     if(j == n) return;

     for(i = 1; i <= n; i++)

         if(i != s && d[i] > j && d[i] <= n)

              d[i] = n+1;

}
