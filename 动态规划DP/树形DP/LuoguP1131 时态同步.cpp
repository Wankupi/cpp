#include <cstdio>
using namespace std;
int head[500001], nxt[1000001], to[1000001], val[1000001], cnt = 0;
inline void insert(int u, int e, int v) {
	nxt[++cnt] = head[u]; head[u] = cnt;
	to[cnt] = e; val[cnt] = v;
}
int need[500001], mD[500001];
inline int max(int a, int b) { return a > b ? a : b; }
void dfs(int x, int fa) {
	int siz = 0; mD[x] = 0;
	for (int i = head[x];i; i = nxt[i])
		if (to[i] != fa) {
			dfs(to[i], x);
			need[x] += need[to[i]];
			mD[to[i]] += val[i];
			if (mD[to[i]] > mD[x]) {
				need[x] += siz * (mD[to[i]] - mD[x]);
				mD[x] = mD[to[i]];
			}
			else
				need[x] += mD[x] - mD[to[i]];
			++siz;
		}
}
int main() {
	int n = 0, s = 0;
	scanf("%d%d", &n, &s);
	int a = 0, b = 0, t = 0;
	for (int i = 1; i != n; ++i) {
		scanf("%d%d%d", &a, &b, &t);
		insert(a, b, t); insert(b, a, t);
	}
	dfs(s, s);
	printf("%d", need[s]);
	return 0;
}