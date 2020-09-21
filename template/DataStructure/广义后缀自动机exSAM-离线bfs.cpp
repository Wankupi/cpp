// 离线 bfs
#include <cstdio>
#include <queue>
int const maxn = 1000003;
struct SAM {
	static const int maxP = maxn << 1;
	struct Node {
		int son[26];
		int fa, len;
		int &operator[](int x) { return son[x]; }
	};
	Node tr[maxP];
	int cnt = 1;
	int expand(int last, int c) {
		int p = last, np = ++cnt;
		tr[np].len = tr[p].len + 1;
		for (; p && tr[p][c] == 0; p = tr[p].fa) tr[p][c] = np;
		if (p == 0) tr[np].fa = 1;
		else {
			int q = tr[p][c];
			if (tr[q].len == tr[p].len + 1) tr[np].fa = q;
			else {
				int nq = ++cnt;
				tr[nq] = tr[q];
				tr[nq].len = tr[p].len + 1;
				tr[q].fa = tr[np].fa = nq;
				for (; p && tr[p][c] == q; p = tr[p].fa) tr[p][c] = nq;
			}
		}
		return np;
	}
};
struct Trie {
	int tr[maxn][26], cnt = 1;
	int pos[maxn];
	void insert(char *s) {
		int p = 1;
		while (*s) {
			int c = *s++ - 'a';
			if (!tr[p][c]) tr[p][c] = ++cnt;
			p = tr[p][c];
		}
	}
	void buildSAM(SAM &sam) {
		std::queue<int> q;
		pos[1] = 1;
		q.push(1);
		while (!q.empty()) {
			int x = q.front();
			q.pop();
			for (int i = 0; i < 26; ++i)
				if (tr[x][i]) {
					pos[tr[x][i]] = sam.expand(pos[x], i);
					q.push(tr[x][i]);
				}
		}
	}
};

Trie trie;
SAM sam;
char str[maxn];
int main() {
	int n = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", str);
		trie.insert(str);
	}
	trie.buildSAM(sam);
	long long ans = 0;
	for (int i = 1; i <= sam.cnt; ++i)
		ans += sam.tr[i].len - sam.tr[sam.tr[i].fa].len;
	printf("%lld\n", ans);
	return 0;
}