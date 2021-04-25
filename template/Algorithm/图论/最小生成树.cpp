#include <algorithm>
const int maxn=100001,maxm=500001;

int m = 0, n = 0;
struct B{
	int u, e, v;
};
bool Cmp(const B&lhs,const B&rhs){
	return lhs.v < rhs.v;
}
B lines[maxm];

int fa[maxn];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
inline void merge(int x, int y) { fa[find(x)] = find(y); }

void insert(int u, int e, int v);//加边

void kru(){
	std::sort(lines+1,lines+m+1);
	for (int i = 1; i <= n;++i)
		fa[i] = i;
	int tot = 0, sum = 0;
	for (int i = 1; i <= m;++i) {
		if (find(lines[i].u) != find(lines[i].e)){
			insert(lines[i].u, lines[i].e, lines[i].v);
			insert(lines[i].e, lines[i].u, lines[i].v);
			sum += lines[i].v;
			merge(lines[i].u, lines[i].e);
			if(++tot==n-1)
				break;
		}
	}
}
