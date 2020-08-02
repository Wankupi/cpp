#include <cstdio>
#include <bitset>
#include <queue>
int n = 0;
int tr[620][26], cp = 0;
int st[620], fail[620];
void insert(char *s, int id) {
	int p = 0;
	while (*s) {
		int c = *s++ - 'A';
		if (tr[p][c] == 0)
			tr[p][c] = ++cp;
		p = tr[p][c];
	}
	st[p] |= (1 << (id - 1));
}

void GetFail() {
	std::queue<int> q;
	for (int i = 0; i < 26; ++i)
		if (tr[0][i]) q.push(tr[0][i]);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		st[x] |= st[fail[x]];
		for (int i = 0; i < 26; ++i)
			if (tr[x][i]) {
				fail[tr[x][i]] = tr[fail[x]][i];
				q.push(tr[x][i]);
			} else
				tr[x][i] = tr[fail[x]][i];
	}
}
struct State {
	int p, s, pre, c;
};
State d[3000000];
int l = 0, r = 0;
std::bitset<1 << 12> vis[620];
int ans = 0;
void solve() {
	l = r = 0;
	while (l <= r) {
		State x = d[l];
		for (int i = 0; i < 26; ++i)
			if (vis[tr[x.p][i]][x.s | st[tr[x.p][i]]] == false) {
				++r;
				d[r].c = i;
				d[r].pre = l;
				d[r].p = tr[x.p][i];
				d[r].s = x.s | st[tr[x.p][i]];
				vis[d[r].p][d[r].s] = true;
				if (d[r].s == (1 << n) - 1) {
					ans = r;
					return;
				}
			}
		++l;
	}
}
char str[700];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", str);
		insert(str, i);
	}
	GetFail();
	solve();
	int cur = 0, p = ans;
	while (p) {
		str[++cur] = char(d[p].c + 'A');
		p = d[p].pre;
	}
	while (cur)
		putchar(str[cur--]);
	return 0;
}