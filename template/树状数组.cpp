const int maxN = 100001;
int n = maxN;
int sum[maxN];//前缀和
int tree[maxN];
inline int lowbit(int i) { return i & -i; }

// 在区间修改、单点查询时，会不太一样
inline void create() {
	for (int i = 1; i <= n;++i)
		tree[i] = sum[i] - sum[i - lowbit(i)];
}
inline void add(int p, int v) {
	while (p <= n){
		tree[p] += v;
		p += lowbit(p);
	}
}
inline void query(int p) {
	int ret = 0;
	while (p){
		ret += tree[p];
		p -= lowbit(p);
	}
}

/*
1. 单点修改 区间查询
	1) add(p,v)
	2) query(b)-query(a-1)
2. 区间修改 单点查询
	化原序列为差分序列
	每次修改，在头+，在尾后-，维护差分数组的前缀和
	1) add(a,v) add(b+1,-v);
	2) query(p)
3. 区间修改 区间查询
	使用数学转化. 暂不详述
*/