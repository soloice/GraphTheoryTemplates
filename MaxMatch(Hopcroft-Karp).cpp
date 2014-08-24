//����ͼ���ƥ��Hopcroft-Karp�㷨,O( sqrt(V)*E )
int dx[MAXX],dy[MAXY],mx[MAXX],my[MAXY],nx,ny,dis;
bool map[MAXX][MAXY],visit[MAXY];

bool makeLevel()
{
    static int q[MAXX];    //����q�н�����X�еĽڵ�
    int front = 0, rear = 0, dis = INF; //disΪ�ֲ�����������·�ĳ��ȣ���ΪINF˵������gap

    memset(dx, -1, sizeof(dx));
    memset(dy, -1, sizeof(dy));
    for (int i=0;i<nx;++i)       //��X�е�δƥ��ڵ����
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
            if (my[v]!=-1 && dy[v]==dis)    //�Ѿ����˾���dis��û��Ҫ���������ˣ�ֱ������
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
