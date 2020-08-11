#include <cstdio>
#include <cstring>
#include <queue>
int tr[1007][14], fail[1007], cnt = 0;
long long w[1007];
inline void insert(char *s, int val) {
	int p = 0;
	while (*s) {
		int c = *s++ - 'a';
		if (!tr[p][c]) tr[p][c] = ++cnt;
		p = tr[p][c];
	}
	w[p] += val;
}
void GetFail() {
	std::queue<int> q;
	for (int i = 0; i < 14; ++i)
		if (tr[0][i]) q.push(tr[0][i]);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		w[x] += w[fail[x]];
		for (int i = 0; i < 14; ++i)
			if (tr[x][i]) {
				fail[tr[x][i]] = tr[fail[x]][i];
				q.push(tr[x][i]);
			}
			else
				tr[x][i] = tr[fail[x]][i];
	}
}
long long f[1 << 14][1007], g[15][1007];
int pos[15][1007], M = 0;
char st[400007];
int top = 0;
void run(int k, int p) {
	int begP = p;
	g[k][begP] = w[p];
	for (int i = 0; i < top; ++i) {
		int c = st[i] - 'a';
		p = tr[p][c];
		g[k][begP] += w[p];
	}
	pos[k][begP] = p;
}
inline int countBit(int x) {
	int re = 0;
	while (x) {
		re += (x & 1);
		x >>= 1;
	}
	return re;
}
inline long long max(long long a, long long b) { return a < b ? b : a; }
char str[400007];
int main() {
	int k = 0, v = 0;
	scanf("%d", &k);
	for (int i = 1; i <= k; ++i) {
		scanf("%s %d", str, &v);
		insert(str, v);
	}
	GetFail();
	scanf("%s", str);
	int len = strlen(str);
	for (int i = 0; i <= len; ++i) {
		if (i == len || str[i] == '?') {
			for (int j = 0; j <= cnt; ++j)
				run(M, j);
			top = 0;
			M++;
		} else
			st[top++] = str[i];
	}
	memset(f, -0x3f, sizeof f);
	f[0][pos[0][0]] = g[0][0];
	long long ans = -0x7fffffffffffffff;
	for (int S = 0; S < (1 << 14); ++S) {
		k = countBit(S) + 1;
		if (k > M) continue;
		if (k == M) {
			for (int i = 0; i <= cnt; ++i)
				ans = max(ans, f[S][i]);
			continue;
		}
		for (int i = 0; i <= cnt; ++i) {
			for (int j = 0; j < 14; ++j) {
				if ((S >> j) & 1) continue;
				int nxt = tr[i][j], To = S | (1 << j);
				int ver = pos[k][nxt];
				f[To][ver] = max(f[To][ver], f[S][i] + g[k][nxt]);
			}
		}
	}
	printf("%lld", ans);
	return 0;
}