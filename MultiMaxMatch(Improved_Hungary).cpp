//����ͼ����ƥ�䣬��չ�������㷨�����Ӷ�O(MNx),NxΪ�󼯺�X�Ľ�

/*nx,ny�ֱ���X,Y�����еĶ�������, nlimit[v]��ʾY�ж���V�Ķ���ƥ����������
 *mx[u]��ʾ��X�ж���uƥ���Y�ж��㣬���������ƥ�������������ƥ�䣬��ȥ��������
 *nmy[v]��ʾ�Ѿ���Y�еĶ���Vƥ���ϵ�X�ж������Ŀ����ЩX�еĵ㱣�����б�my[v][]��
 *map[][]���ڴ�ͼ��visit[]ΪY�нڵ�ķ��ʱ�ǣ�����Ѱ������· */
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
        //������֪���Ƿ�����걸ƥ�䣬�ɽ���һ���Ϊ��if (!findPath(i)) return false;
    }
    return ans;
}
