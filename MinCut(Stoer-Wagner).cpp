/*
 *����������ͼ��ȫ����С�Stoer-Wagner�㷨, O(N^3)
 *nΪͼ���ܵ�����w[i][j]Ϊ����V_i��V_j��Ȩ��
 *map[]���ڽ�����ӳ�䣬ʹ��ÿ�������ߺ���ͼ�еĶ���Ϊmap[0..n-1]
 *visit[i]��ʾ�ڵ�map[i]�Ƿ񱻷��ʹ�
 *dist[i]Ϊ����map[i]�����ֶ��㼯A��Ȩֵ��w(A,map[i]),
 *�����Ϊ����map[i]�����ε�����ȡԴ��map[0]����Զ����
 *�����Ϊ���ѭ��������һ���޸Ĺ���dijkstra�㷨
 */

int w[SIZE][SIZE]={0},n;
int map[SIZE],dist[SIZE];
bool visit[SIZE];

int stoer_Wagner(){

    int maxdist,now,i,j,k,pre,ans = INF;
    for (i=0;i<n;++i)       map[i] = i;
    while (n>1){
        memset(visit, 0, sizeof(visit));
        visit[k=0] = true;        //��map[0]���뼯��visit[]
        for (j=1;j<n;++j)
            dist[j] = w[map[0]][map[j]];

        for (i=1;i<n-1;++i){      //ѭ��N-2��
            maxdist = -1;
            for (j=1;j<n;++j)       //�Ӽ���V - visit[]����ѡdistֵ����Ԫ�أ�����¼�±�k
                if (!visit[j] && dist[j]>maxdist)
                    maxdist = dist[k=j];

            visit[k] = true;

            for (j=1;j<n;++j)
                if (!visit[j])
                    dist[j] += w[map[k]][map[j]];
        }

        for (j=1;visit[j];++j); //�ҵ����һ��δ�����뼯��visit�ĵ�map[j]
        ans = ans < dist[j] ? ans : dist[j];  //dist[j]Ϊ map[k] - map[j] ��С��

        //Contract(map[k], map[j])
        for (i=0;i<n;++i)  //��map[k]������map[k]��map[j]�ϲ���ĵ�
            w[map[k]][map[i]] = w[map[i]][map[k]] += w[map[i]][map[j]];

        map[j] = map[--n];  //��j��ӳ����map[n-1],ʹ���´ε���ʱ�㷨��map[0..n-1]�⼸������ִ��
    }

    return ans;
}
