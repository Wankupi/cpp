#include <cstdio>
#include <algorithm>
#include <cctype>
int const maxn = 100003;

inline int read() {
	int x = 0, c = getchar();
	while (!isdigit(c)) c = getchar();
	while (isdigit(c)) { x = 10 * x + c - '0'; c = getchar(); }
	return x;
}

int n = 0, m = 0, q = 0;

int X[maxn], Y[maxn];

int head[maxn], nxt[maxn], to[maxn], cnt = 0, now = 0;
int rub[maxn], top = 0;
inline int newId() { ++now; if (top > 0) return rub[top--]; else return ++cnt; }
void insert(int u, int e) {  int k = newId(); nxt[k] = head[u]; head[u] = k; to[k] = e; }

struct Query { int x, y, z;	int L, R; };
Query qu[maxn];

int fa[maxn], siz[maxn];
inline int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
inline void merge(int x, int y) {
	x = find(x); y = find(y);
	if (x == y) return;
	if (siz[x] < siz[y]) std::swap(x, y);
	fa[y] = x;
	siz[x] += siz[y];
}

int main() {
	n = read(); m = read();
	for (int i = 1; i <= m; ++i) { X[i] = read(); Y[i] = read(); }

	q = read();
	for (int i = 1; i <= q; ++i) {
		qu[i].x = read(); qu[i].y = read(); qu[i].z = read();
		qu[i].L = 1; qu[i].R = m;
		insert((m + 1) >> 1, i);
	}
	while (now) {
		for (int i = 1; i <= n; ++i) { fa[i] = i; siz[i] = 1; }
		for (int x = 1; x <= m; ++x) {
			merge(X[x], Y[x]);

			int H = head[x]; head[x] = 0;
			for (int i = H; i; i = nxt[i]) {
				Query &qq = qu[to[i]];

				int _x = find(qq.x), _y = find(qq.y);
				if ((_x != _y && siz[_x] + siz[_y] < qq.z) || (_x == _y && siz[_x] < qq.z))
					qq.L = x + 1;
				else
					qq.R = x;
				if (qq.L != qq.R)
					insert((qq.L + qq.R) >> 1, to[i]);
				rub[++top] = i;
				--now;
			}
		}
	}
	for (int i = 1; i <= q; ++i) printf("%d\n", qu[i].L);
	return 0;
}