//二分图多重匹配，拓展匈牙利算法，复杂度O(MNx),Nx为左集合X的阶

/*nx,ny分别是X,Y集合中的顶点总数, nlimit[v]表示Y中顶点V的多重匹配数的上限
 *mx[u]表示与X中顶点u匹配的Y中顶点，若仅需求出匹配数而不用求出匹配，可去掉此数组
 *nmy[v]表示已经与Y中的顶点V匹配上的X中顶点的数目，这些X中的点保存在列表my[v][]中
 *map[][]用于存图，visit[]为Y中节点的访问标记，辅助寻找增广路 */
int mx[MAXX],my[MAXY][MAXM],nmy[MAXY],nlimit[MAXY],nx,ny;
bool map[MAXX][MAXY],visit[MAXY];

int findPath(int u)
{
    for (int v=0;v<ny;++v)
        if (map[u][v] && !visit[v])
        {
            visit[v] = true;
            if (nmy[v]<nlimit[v])
            {
                my[v][nmy[v]++] = u;
                mx[u] = v;
                return 1;
            }
            else
            {
                for (int j=0;j<nmy[v];++j)
                    if (findPath(my[v][j]))
                    {
                        my[v][j] = u;
                        mx[u] = v;
                        return 1;
                    }
            }
        }
    return 0;
}

int multiMaxMatch()
{
    memset(mx, -1, sizeof(mx));
    memset(my, -1, sizeof(my));
    memset(nmy, 0, sizeof(nmy));
    int i,ans = 0;
    for (i=0;i<nx;++i)
    {
        memset(visit, 0, sizeof(visit));
        ans += findPath(i);
        //若仅需知道是否存在完备匹配，可将这一句改为：if (!findPath(i)) return false;
    }
    return ans;
}
