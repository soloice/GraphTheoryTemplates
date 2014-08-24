/*
 *Kuhn-Munkras�㷨��������ͼ����Ȩƥ�䡣���Ӷ�O(N^3)��
 *��Ҫ����СȨƥ��,���ȶԱ�Ȩȡ�෴�����������ȡһ���෴�����ɡ�
 *˼���е��������dinic��ά�����ж��꣬ÿ��ֻ�������ͼ����չ
 *nx,ny�ֱ����������ߵĵ������豣֤nx<=ny��
 *w[][]ΪȨ������lx[],ly[]Ϊ���ж��꣬mx[],my[]����ƥ��ߣ�slack[]ά���ɳ���
 *visx[],visy[]�ֱ��ʾX,Y�еĶ����Ƿ񱻷��ʹ�(�Ƿ�������������)
 */
int w[MAXX][MAXY],lx[MAXX],ly[MAXY],mx[MAXX],my[MAXY],slack[MAXY],nx,ny;
bool visx[MAXX],visy[MAXY];

bool DFS_KM(int x){
    visx[x] = true;
    for (int y=0;y<ny;++y){
        if (visy[y])            continue;
        int t = lx[x] + ly[y] - w[x][y];
        if (t == 0){       //�������ͼ�еı���������·,��Ϊ��������Ҫע�⾫��
            visy[y] = true;
            if (my[y]==-1 || DFS_KM(my[y])){
                my[y] = x;
                mx[x] = y;
                return true;
            }
        }
        else
            slack[y] =  slack[y]>t ? t : slack[y];     //�����ɳ���slack
    }
    return false;
}

int KM(){
    int i,j;
    memset (mx,-1,sizeof(mx));
    memset (my,-1,sizeof(my));
    memset (ly,0,sizeof(ly));
    for (i=0; i<nx; ++i)            //lx��ʼ��Ϊ����������������
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

            for (i=0; i<nx; ++i)         //�޸Ķ�����ɳ���
                lx[i] -= visx[i] ? d : 0;
            for (i=0;i<ny;++i){
                ly[i] += visy[i] ? d : 0;
                slack[i] -= visy[i] ? 0 : d;
            }
        }
    }

    int res = 0;    //�ɽ������ѭ���ĳ�if (my[i]!=-1) res += w[my[i]][i]�Խ�ʡmx[]��ռ�ռ�
    for (i=0; i<nx; ++i)
        res += w[i][mx[i]];
    return res;
}
