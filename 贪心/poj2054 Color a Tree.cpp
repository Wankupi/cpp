#include <cstdio>
#include <cstring>
#include <set>
using namespace std;
const int maxn = 1003;
int n = 0, rt = 0;
int c[maxn];
int head[maxn], nxt[maxn << 1], to[maxn << 1], cnt = 0;
inline void insert(int u, int e) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = e;
}
int F[maxn];
void dfs(int x,int f) { F[x] = f; for (int i = head[x]; i; i = nxt[i]) if (to[i] != f) dfs(to[i], x); }
long long w[maxn], siz[maxn];
struct Per {
	Per(int Iden) { id = Iden; }
	int id;
};
inline bool operator<(const Per &lhs, const Per &rhs) {
	return w[lhs.id] * siz[rhs.id] == w[rhs.id] * siz[lhs.id] ? lhs.id > rhs.id : w[lhs.id] * siz[rhs.id] > w[rhs.id] * siz[lhs.id];
}
int fa[maxn];
inline int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

multiset<Per>::iterator it[maxn];
int main() {
	while(true) {
		scanf("%d %d", &n, &rt);
		if (n == 0) break;
		for (int i = 1; i <= n; ++i) scanf("%d", c + i);
		int x = 0, y = 0;
		for (int i = 1; i < n; ++i) {
			scanf("%d %d", &x, &y);
			insert(x, y);
			insert(y, x);
		}
		dfs(rt, 0);
		multiset<Per> s;
		while (!s.empty()) s.erase(s.begin());
		for (int i = 1; i <= n; ++i) {
			fa[i] = i; 
			siz[i] = 1;
			w[i] = c[i];
			it[i] = s.insert(Per(i));
		}
		siz[0] = 1;
		long long ans = 0;
		while(!s.empty()) {
			int x = s.begin()->id;
			s.erase(s.begin());
			int f = fa[x] = find(F[x]);
			if(f) s.erase(it[f]);
			ans += w[x] * siz[f];
			w[f] += w[x];
			siz[f] += siz[x];
			if(f) it[f] = s.insert(Per(f));
		}
		printf("%lld\n", ans);
		memset(head, 0, sizeof head);
		memset(w, 0, sizeof w);
		cnt = 0;
	}
	return 0;
}
