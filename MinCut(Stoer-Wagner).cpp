/*
 *用于求无向图的全局最小割，Stoer-Wagner算法, O(N^3)
 *n为图中总点数，w[i][j]为顶点V_i到V_j的权重
 *map[]用于将点重映射，使得每次收缩边后，新图中的顶点为map[0..n-1]
 *visit[i]表示节点map[i]是否被访问过
 *dist[i]为顶点map[i]到部分顶点集A的权值和w(A,map[i]),
 *可类比为顶点map[i]到本次迭代所取源点map[0]的最远距离
 *可理解为外层循环里套了一个修改过的dijkstra算法
 */

int w[SIZE][SIZE]={0},n;
int map[SIZE],dist[SIZE];
bool visit[SIZE];

int stoer_Wagner(){

    int maxdist,now,i,j,k,pre,ans = INF;
    for (i=0;i<n;++i)       map[i] = i;
    while (n>1){
        memset(visit, 0, sizeof(visit));
        visit[k=0] = true;        //将map[0]加入集合visit[]
        for (j=1;j<n;++j)
            dist[j] = w[map[0]][map[j]];

        for (i=1;i<n-1;++i){      //循环N-2次
            maxdist = -1;
            for (j=1;j<n;++j)       //从集合V - visit[]中挑选dist值最大的元素，并记录下标k
                if (!visit[j] && dist[j]>maxdist)
                    maxdist = dist[k=j];

            visit[k] = true;

            for (j=1;j<n;++j)
                if (!visit[j])
                    dist[j] += w[map[k]][map[j]];
        }

        for (j=1;visit[j];++j); //找到最后一个未被加入集合visit的点map[j]
        ans = ans < dist[j] ? ans : dist[j];  //dist[j]为 map[k] - map[j] 最小割

        //Contract(map[k], map[j])
        for (i=0;i<n;++i)  //用map[k]来代表map[k]和map[j]合并后的点
            w[map[k]][map[i]] = w[map[i]][map[k]] += w[map[i]][map[j]];

        map[j] = map[--n];  //将j重映射至map[n-1],使得下次迭代时算法在map[0..n-1]这几个点上执行
    }

    return ans;
}
