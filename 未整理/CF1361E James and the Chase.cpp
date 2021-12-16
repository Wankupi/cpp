#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <algorithm>
#include <set>
using namespace std;

int const maxn = 100003, maxm = 200003;

inline int read() {
	int x = 0, c = getchar();
	while (!isdigit(c)) c = getchar();
	while (isdigit(c)) x = 10 * x + c - '0', c = getchar();
	return x;
}

int n = 0, m = 0;
int head[maxn], nxt[maxm], to[maxm], cnt = 0;
inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }

bool in[maxn]; // true if in stack
int dfn[maxn], cdfn = 0, laDfn = 0;
bool dfs(int x) {
	in[x] = true;
	dfn[x] = ++cdfn;
	bool sign = true;
	for (int i = head[x]; i && sign; i = nxt[i])
		if (dfn[to[i]] > laDfn) {
			if (!in[to[i]]) sign = false;
		}
		else if (!dfs(to[i]))
			sign = false;
	in[x] = false;
	return sign;
}
int rndPermu[maxn];
int check() {
	for (int i = 1; i <= n; ++i) rndPermu[i] = i;
	random_shuffle(rndPermu + 1, rndPermu + n + 1);
	for (int i = 1; i <= n && i <= 100; ++i) {
		int x = rndPermu[i];
		laDfn = cdfn;
		bool a = dfs(x);
		for (int i = 1; i <= n && a; ++i)
			a = (dfn[i] > laDfn);
		if (a) return x;
	}
	return -1;
}

int rt = 0;
int good[maxn];
multiset<int> dfs2(int x) {
	// dfn[x] = ++cdfn;
	in[x] = true;
	set<int> ret;
	for (int i = head[x]; i; i = nxt[i]) {
		if (!in[to[i]]) {
			multiset<int> &&rr = dfs2(to[i]);
			ret.insert(rr.begin(), rr.end());
		}
		else
			ret.insert(to[i]);
	}
	ret.erase(x);
	if (ret.size() >= 2)
		good[x] = -1;
	else if (ret.size() == 1) {
		good[x] = *ret.begin();
	}
	else if (ret.size() == 0)
		good[x] = (x == rt ? 0 : -1);
	in[x] = false;
}

void dfs3(int x) {
	in[x] = true;
	if (good[x] >= 1)
		good[x] = good[good[x]];
	for (int i = head[x]; i; i = nxt[i]) {
		if (in[to[i]]) continue;
		dfs3(to[i]);
	}
}

void solve(int rt) {
	dfs2(rt);
	dfs3(rt);
}


int main() {
	int T = read();
	while (T--) {
		n = read(); m = read();
		for (int i = 1; i <= m; ++i) {
			int x = read(), y = read();
			insert(x, y);
		}
		rt = check();
		if (rt > 0)
			solve(rt);
		else
			printf("-1\n");
		// clear
		cnt = 0;
		for (int i = 1; i <= n; ++i) head[i] = 0;
	}
	return 0;
}