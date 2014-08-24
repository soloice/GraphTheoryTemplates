//二分图最大匹配Hopcroft-Karp算法,O( sqrt(V)*E )
int dx[MAXX],dy[MAXY],mx[MAXX],my[MAXY],nx,ny,dis;
bool map[MAXX][MAXY],visit[MAXY];

bool makeLevel()
{
    static int q[MAXX];    //队列q中仅保存X中的节点
    int front = 0, rear = 0, dis = INF; //dis为分层网络中增广路的长度，若为INF说明出现gap

    memset(dx, -1, sizeof(dx));
    memset(dy, -1, sizeof(dy));
    for (int i=0;i<nx;++i)       //将X中的未匹配节点入队
        if (mx[i]==-1)
        {
            q[rear++] = i;
            dx[i] = 0;
        }
    while (front<rear)
    {
        int u = q[front++];
        if (dx[u]>dis)  break;
        for (int v=0;v<ny;++v)
        {
            if (map[u][v] && dy[v]==-1)
            {
                dy[v] = dx[u] + 1;
                if (my[v]==-1)  dis = dy[v];
                else{
                    dx[my[v]] = dy[v] + 1;
                    q[rear++] = my[v];
                }
            }
        }
    }
    return dis!=INF;
}

bool findPath(int u)
{
    for (int v=0;v<ny;++v)
    {
        if (map[u][v] && !visit[v] && dy[v]==dx[u]+1)
        {
            visit[v] = true;
            if (my[v]!=-1 && dy[v]==dis)    //已经到了距离dis，没必要接着搜索了，直接跳过
                continue;
            if ( my[v]==-1 || findPath(my[v]) )
            {
                my[v] = u;
                mx[u] = v;
                return true;
            }
        }
    }
    return false;
}

int hopcroft_Karp()
{
    int res = 0;
    memset(mx, -1, sizeof(mx));
    memset(my, -1, sizeof(my));
    while ( makeLevel() )
    {
        memset(visit, 0, sizeof(visit));
        for (int u=0;u<nx;++u)
            if ( mx[u]==-1 && findPath(u) )
                ++res;
    }
    return res;
}
