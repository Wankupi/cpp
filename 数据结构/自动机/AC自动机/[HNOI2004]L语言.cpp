#include <cstdio>
#include <queue>
using std::queue;
const int maxn = 2000;
int n = 0, m = 0;
int tr[maxn][26], cnt = 0;
int fail[maxn], len[maxn], sym[maxn];
bool End[maxn];
void insert(char *s) {
	int p = 0;
	while (*s) {
		int c = *s++ - 'a';
		if (!tr[p][c]) tr[p][c] = ++cnt;
		len[tr[p][c]] = len[p] + 1;
		p = tr[p][c];
	}
	End[p] = true;
}
void GetFail() {
	queue<int> q;
	for (int i = 0; i < 26; ++i)
		if (tr[0][i]) {
			// fail[tr[0][i]] = 0;
			q.push(tr[0][i]);
		}
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		sym[x] = sym[fail[x]] + End[x] * (1 << len[x]);
		for (int i = 0; i < 26; ++i) {
			if (tr[x][i]) {
				fail[tr[x][i]] = tr[fail[x]][i];
				q.push(tr[x][i]);
			} else
				tr[x][i] = tr[fail[x]][i];
		}
	}
}
int solve(char *s) {
	int p = 0;
	int ans = 0;
	unsigned int st = 1;
	for (int i = 1; s[i]; ++i) {
		int c = s[i] - 'a';
		p = tr[p][c];
		if (sym[p] & (st <<= 1)) {
			st |= 1;
			ans = i;
		}
	}
	return ans;
}
char str[2000005];
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", str);
		insert(str);
	}
	GetFail();
	for (int i = 1; i <= m; ++i) {
		scanf("%s", str + 1);
		printf("%d\n", solve(str));
	}
	return 0;
}