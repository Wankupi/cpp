#include <cstdio>
#include <queue>
using std::queue;
const int root = 0, mod = 10007, maxn = 6666;
int n = 0, m = 0;
bool End[maxn];
int tr[maxn][26], cnt = root;
int fail[maxn];
char str[103];
void insert(char *s) {
	int p = root;
	while (*s) {
		int c = *s++ - 'A';
		if (tr[p][c] == 0) tr[p][c] = ++cnt;
		p = tr[p][c];
	}
	End[p] = true;
}
void ConnectFail() {
	queue<int> q;
	for (int i = 0; i < 26; ++i)
		if (tr[root][i]) {
			fail[tr[root][i]] = root;
			q.push(tr[root][i]);
		}
		else
			tr[root][i] = root;
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = 0; i < 26; ++i) {
			if (tr[x][i]) {
				fail[tr[x][i]] = tr[fail[x]][i];
				End[tr[x][i]] |= End[tr[fail[x]][i]];
				q.push(tr[x][i]);
			}
			else
				tr[x][i] = tr[fail[x]][i];
		}
	}
}
int pow(int x, int b) {
	int ret = 1;
	while (b) {
		if (b & 1) ret = ret * x % mod;
		x = x * x % mod;
		b >>= 1;
	}
	return ret;
}
int f[103][maxn];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", str);
		insert(str);
	}
	ConnectFail();
	f[0][0] = 1;
	for (int i = 0; i < m; ++i)
		for (int x = 0; x <= cnt; ++x)
			if (!End[x])
				for (int j = 0; j < 26; ++j)
					if (!End[tr[x][j]])
						f[i + 1][tr[x][j]] = (f[i + 1][tr[x][j]] + f[i][x]) % mod;
	int ans = pow(26, m);
	for (int x = 0; x <= cnt; ++x)
		ans = (ans - f[m][x] + mod) % mod;
	printf("%d", ans);
	return 0;
}