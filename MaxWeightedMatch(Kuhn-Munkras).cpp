/*
 *Kuhn-Munkras算法，求解二分图最大带权匹配。复杂度O(N^3)。
 *若要求最小权匹配,则先对边权取相反数，最后结果再取一次相反数即可。
 *思想有点儿类似于dinic，维护可行顶标，每次只在相等子图中扩展
 *nx,ny分别是左右两边的点数，需保证nx<=ny；
 *w[][]为权函数，lx[],ly[]为可行顶标，mx[],my[]保存匹配边，slack[]维护松弛量
 *visx[],visy[]分别表示X,Y中的顶点是否被访问过(是否在匈牙利树中)
 */
int w[MAXX][MAXY],lx[MAXX],ly[MAXY],mx[MAXX],my[MAXY],slack[MAXY],nx,ny;
bool visx[MAXX],visy[MAXY];

bool DFS_KM(int x){
    visx[x] = true;
    for (int y=0;y<ny;++y){
        if (visy[y])            continue;
        int t = lx[x] + ly[y] - w[x][y];
        if (t == 0){       //沿相等子图中的边搜索增广路,若为浮点类型要注意精度
            visy[y] = true;
            if (my[y]==-1 || DFS_KM(my[y])){
                my[y] = x;
                mx[x] = y;
                return true;
            }
        }
        else
            slack[y] =  slack[y]>t ? t : slack[y];     //更新松弛量slack
    }
    return false;
}

int KM(){
    int i,j;
    memset (mx,-1,sizeof(mx));
    memset (my,-1,sizeof(my));
    memset (ly,0,sizeof(ly));
    for (i=0; i<nx; ++i)            //lx初始化为与它关联边中最大的
        for (lx[i]=w[i][0],j=1; j<ny; ++j)
            lx[i] = w[i][j] > lx[i] ? w[i][j] : lx[i];

    for (int x=0; x<nx; ++x){
        memset(slack, 0x7F, sizeof(slack));
        while (1){
            memset (visx,0,sizeof(visx));
            memset (visy,0,sizeof(visy));
            if (DFS_KM(x))                break;

            int d = INF;
            for (i=0; i<ny; ++i)
                if (!visy[i] && d > slack[i])
                    d = slack[i];

            for (i=0; i<nx; ++i)         //修改顶标和松弛量
                lx[i] -= visx[i] ? d : 0;
            for (i=0;i<ny;++i){
                ly[i] += visy[i] ? d : 0;
                slack[i] -= visy[i] ? 0 : d;
            }
        }
    }

    int res = 0;    //可将下面的循环改成if (my[i]!=-1) res += w[my[i]][i]以节省mx[]所占空间
    for (i=0; i<nx; ++i)
        res += w[i][mx[i]];
    return res;
}
