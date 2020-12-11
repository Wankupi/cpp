#include <cstdio>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;
int const maxn = 100003, maxm = 1000003;
int n = 0, m = 0;
int head[maxn], nxt[maxm], to[maxm], cnt = 0;
inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }

int st[maxn], top = 0;
bool inSt[maxn];
int dfn[maxn], low[maxn], cdfn = 0;;
int sym[maxn], cntSCC = 0;
list<int> V[maxn];
void tarjan(int x) {
	dfn[x] = low[x] = ++cdfn;
	st[++top] = x;
	inSt[x] = true;
	for (int i = head[x]; i; i = nxt[i])
		if (!dfn[to[i]]) {
			tarjan(to[i]);
			low[x] = min(low[x], low[to[i]]);
		}
		else if (inSt[to[i]]) low[x] = min(low[x], dfn[to[i]]);
	if (low[x] == dfn[x]) {
		int id = ++cntSCC, y = 0;
		do {
			y = st[top--];
			inSt[y] = false;
			sym[y] = id;
			V[id].push_back(y);
		} while (y != x);
	}
}
vector<int> G[maxn];
int deg[maxn];
int q[maxn], ql = 1, qr = 0;
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		int x = 0, y = 0;
		scanf("%d %d", &x, &y);
		insert(x, y);
	}
	for (int i = 1; i <= n; ++i) if (!dfn[i]) tarjan(i);
	for (int x = 1; x <= n; ++x)
		for (int i = head[x]; i; i = nxt[i])
			if (sym[to[i]] != sym[x]) {
				++deg[sym[to[i]]];
				G[sym[x]].push_back(sym[to[i]]);
			}
	bool first = true;
	int A = 0, x = 0;
	for (int i = 1; i <= cntSCC; ++i) if (deg[i] == 0) {
		if (first) {
			A = i;
			x = *V[i].begin();
			first = false;
			continue;
		}
		q[++qr] = i;
	}
	
	while (ql <= qr) {
		int B = q[ql++];
		while (V[B].size()) {
			int y = *V[B].begin();
			printf("? %d %d\n", x, y); fflush(stdout);
			int ver = 0; scanf("%d", &ver);
			if (ver == 0) { std::swap(A, B); std::swap(x, y); }
			V[B].erase(V[B].begin());
		}
		for (int i = 0; i < G[B].size(); ++i) {
			int t = G[B][i];
			if (--deg[t] == 0)
				q[++qr] = t;
		}
	}
	printf("! %d\n", x);
	return 0;
}
