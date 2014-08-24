//�������㷨��DFSʵ��,O(MN)
//nx��ny�ֱ�Ϊ���Ҽ���X,Y�Ľڵ���,mx[i],my[j]�ֱ��ʾ���X_i,Y_j����Եĵ�ı��
int nx,ny,mx[MAXN],my[MAXM];
bool map[MAXN][MAXM],visit[MAXM];

int DFS_hungary(int u)
{
    for (int v=0;v<ny;++v)   //������u������ÿһ����<u,v>
        if (map[u][v] && !visit[v]) //���ڵ�vδ���ʹ�������u - v - my[v]��������·
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
    for (int i=0;i<nx;++i)  //��X���ϵ�ÿ�������������·
        if (mx[i]==-1)
        {
            memset(visit, 0, sizeof(visit));
            res += DFS_hungary(i);
        }
    return res;
}
