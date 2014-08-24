//最大流，dinic算法，O(MN^2)
//w[][]为残留网络，level[i]为分层图中点i的层数，n为总点数
int w[MAXN][MAXN],n,level[MAXN],q[MAXN];

bool makeLevel(int src, int sink){
    memset(level, -1, sizeof(level));
    int front=0,rear=0,i,e;
    q[rear++] = src;
    level[src] = 0;
    while(front<rear){

        e = q[front++];
        for (i=0;i<n;++i)
            if (level[i]==-1 && w[e][i]>0){
                level[i] = level[e] + 1;
                q[rear++] = i;
            }
        if (level[sink]!=-1)
            return true;
    }
    return false;
}

int DFS_dinic(int cur, int sink, __int64 maxf){

    if (cur==sink){
        return maxf;
    }

    int i, j, k, used = 0;
    for (i=0;i<n;++i){
        if (level[i]==level[cur]+1 && w[cur][i]>0){
            k = DFS_dinic(i, sink, maxf-used<w[cur][i] ? maxf-used : w[cur][i]);
            w[cur][i] -= k;
            w[i][cur] += k;
            used += k;
            if (used==maxf){
                return maxf;
            }
        }
    }

    return used;
}

int dinic(int src, int sink){
    int ans = 0;
    while (makeLevel(src, sink))
        ans += DFS_dinic(src, sink, INF);
    return ans;
}
