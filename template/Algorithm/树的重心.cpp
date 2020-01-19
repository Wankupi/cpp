

inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a < b ? b : a; }

int n = 0;
int head[1001], nxt[2001], to[2001], cnt = 0;
inline void insert(int u, int e)
{
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = e;
}

int heavy = 0, maxpart = 0x7ffffff;
int siz[1001];
void dfs(int x,int f) {
	siz[x] = 1;
	int d = 0;
	for (int i = head[x]; i;i=nxt[i]) {
		if(to[i]!=f){
			dfs(to[i],x);
			siz[x] += to[i];
			d = max(d, siz[to[i]]);
		}
	}
	d = max(n - d, d);
	if(maxpart > d) {
		maxpart = d;
		heavy = x;
	}
}
void read();
int main() {
	read();
	dfs(1, 1);
	return 0;
}