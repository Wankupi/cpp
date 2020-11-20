#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
typedef long long ll;
ll const mod = 1000000007;
int d = 0, n = 0, m = 0;
int tr[30000][10], fail[30000], cnt = 1;
bool ed[30000];
void build(char *s) {
	for (int i = 1; i <= n - m + 1; ++i) {
		int p = 1;
		for (int j = 0; j < m; ++j) {
			int c = s[i + j] - '0';
			if (tr[p][c] == 0) tr[p][c] = ++cnt;
			p = tr[p][c];
		}
		ed[p] = true;
	}
}
void getFail() {
	queue<int> q;
	for (int i = 0; i < 10; ++i) if (tr[1][i]) fail[tr[1][i]] = 1, q.push(tr[1][i]); else tr[1][i] = 1;
	while (q.size()) {
		int x = q.front(); q.pop();
		for (int i = 0; i < 10; ++i)
			if (tr[x][i]) { fail[tr[x][i]] = tr[fail[x]][i]; q.push(tr[x][i]); }
			else tr[x][i] = tr[fail[x]][i];
	}
}

ll p[60][2], f[53][30000][2];
ll calc(char *t) {
	p[d + 1][0] = p[d + 1][1] = 1;
	for (int i = d; i >= 1; --i) {
		p[i][0] = p[i + 1][0] * 10 % mod;
		p[i][1] = ((t[i] - '0') * p[i + 1][0] % mod + p[i + 1][1]) % mod;
	}
	ll ans = 0;
	memset(f, 0, sizeof f);
	f[0][1][1] = 1;
	for (int i = 0; i < d; ++i)
		for (int j = 1; j <= cnt; ++j)
			if (!ed[j]) {
				for (int k = 0; k < 10; ++k) {
					int o = tr[j][k];
					f[i + 1][o][0] = (f[i + 1][o][0] + f[i][j][0]) % mod;
					if (k < t[i + 1] - '0') f[i + 1][o][0] = (f[i + 1][o][0] + f[i][j][1]) % mod;
					else if (k == t[i + 1] - '0') f[i + 1][o][1] = (f[i + 1][o][1] + f[i][j][1]) % mod;
				}
			}
	for (int i = 1; i <= d; ++i)
		for (int j = 1; j <= cnt; ++j)
			if (ed[j])
				ans = (ans + f[i][j][0] * p[i + 1][0] % mod + f[i][j][1] * p[i + 1][1] % mod) % mod;
	return ans;
}

char s[1003], A[1003], B[1003];
int main() {
	scanf("%s", s + 1); scanf("%s", A + 1); scanf("%s", B + 1);
	n = strlen(s + 1); d = strlen(A + 1);
	m = d / 2;
	build(s);
	getFail();
	ll ans = calc(B);
	int k = d;
	while (A[k] == '0') A[k--] = '9';
	--A[k];
	ans = (ans - calc(A) + mod) % mod;
	printf("%lld", ans);
	return 0;
}