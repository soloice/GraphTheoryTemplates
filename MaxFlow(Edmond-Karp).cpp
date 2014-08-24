//最大流FF方法中的Edmond Karp算法，每次通过BFS找最短增广路，O(NM^2)
//w[][]为残留网络，pre[]用于保存src-sink路径上每个点的前驱，n为总点数
int w[MAXN][MAXN],pre[MAXN],n;
int queue[MAXQ];
bool visit[MAXN];

bool BFS_EK(int src, int sink){

    memset(visit, 0, sizeof(visit));

    int front = 0, rear = 0, j, cur;
    queue[rear++] = src;
    visit[src] = true;
    pre[src] = -1;

    while (front<rear){
        cur = queue[front++];
        for (j=1;j<=n;++j){
            if (w[cur][j]>0 && !visit[j]){
                queue[rear++] = j;
                visit[j] = true;
                pre[j] = cur;
            }
        }
        if (visit[sink])            return true;
    }

    return false;
}

/*
 * Maximun Flow, Edmond-Karp Algorithm
 */

__int64 maxflow_EK(int src, int sink){
    __int64 ans = 0, k;
    int i;
    while (BFS_EK(src, sink)){
        i = sink;
        k = INF;
        while (pre[i]!=-1){
            k = k<w[pre[i]][i] ? k : w[pre[i]][i];
            i = pre[i];
        }

        ans += k;

        i = sink;
        while (pre[i]!=-1){
            w[pre[i]][i] -= k;
            w[i][pre[i]] += k;
            i = pre[i];
        }
    }
    return ans;
}
