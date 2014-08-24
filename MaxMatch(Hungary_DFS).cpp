//匈牙利算法，DFS实现,O(MN)
//nx和ny分别为左右集合X,Y的节点数,mx[i],my[j]分别表示与点X_i,Y_j所配对的点的编号
int nx,ny,mx[MAXN],my[MAXM];
bool map[MAXN][MAXM],visit[MAXM];

int DFS_hungary(int u)
{
    for (int v=0;v<ny;++v)   //遍历从u出发的每一条边<u,v>
        if (map[u][v] && !visit[v]) //若节点v未访问过，沿着u - v - my[v]搜索增广路
        {
            visit[v] = true;
            if (my[v]==-1 || DFS_hungary(my[v]))
            {
                my[v] = u;
                mx[u] = v;
                return 1;
            }
        }
    return 0;
}

int hungary()
{
    int res = 0;
    memset(mx,-1,sizeof(mx));
    memset(my,-1,sizeof(my));
    for (int i=0;i<nx;++i)  //从X集合的每个点出发找增广路
        if (mx[i]==-1)
        {
            memset(visit, 0, sizeof(visit));
            res += DFS_hungary(i);
        }
    return res;
}
