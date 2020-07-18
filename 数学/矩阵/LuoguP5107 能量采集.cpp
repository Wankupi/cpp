#include <cstdio>
#include <cstring>
typedef long long ll;
const ll mod = 998244353, B = 100;
inline int read() {
	int x = 0, c = getchar();
	while (c < '0' || c>'9') c = getchar();
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x;
}
int n = 0, m = 0, q = 0;
struct Matrix {
	Matrix() { memset(a, 0, sizeof a); }
	Matrix(int) {
		memset(a, 0, sizeof a);
		for (int i = 0; i < m; ++i)
			a[i][i] = 1;
	}
	ll a[50][50];
};
Matrix ret;
inline Matrix operator*(const Matrix &A, const Matrix &B) {
	memset(ret.a, 0, sizeof ret.a);
	for (int k = 0; k < n; ++k)
		for (int i = 0; i < n; ++i)
			if (A.a[i][k])
				for (int j = 0; j < n; ++j)
					(ret.a[i][j] += A.a[i][k] * B.a[k][j]) %= mod;
	return ret;
}
inline ll pow(ll x, int b) {
	ll res = 1;
	while (b) {
		if (b & 1) res = res * x % mod;
		x = x * x % mod;
		b >>= 1;
	}
	return res;
}
int d[51];
ll mi[10];
Matrix base, F;
Matrix g[7][B + 3]; // g[i][j] = F^(j * B^i)
Matrix ans;
inline void Mi(int t) {
	ans = base;
	for (int j = 5; j >= 0; --j)
		if (t >= mi[j]) {
			ans = ans * g[j][t / mi[j]];
			t %= mi[j];
		}
}
void GetInput() {
	n = read(); m = read(); q = read();
	for (int i = 0; i < n; ++i) base.a[0][i] = read();
	int x = 0, y = 0;
	for (int i = 0; i < m; ++i) {
		x = read() - 1; y = read() - 1;
		F.a[x][y] += 1;
		++d[x];
	}
	for (int i = 0; i < n; ++i) F.a[i][i] = 1;
	for (int i = 0; i < n; ++i) {
		ll inv = pow(d[i] + 1ll, mod - 2);
		for (int j = 0; j < n; ++j)
			F.a[i][j] = F.a[i][j] * inv % mod;
	}
}
void init() {
	//g[0][0] = Matrix(1); // use this will be RE
	g[0][1] = F;
	for (int j = 1; j <= B; ++j) g[0][j] = g[0][j - 1] * F;
	for (int i = 1; i <= 5; ++i) {
		//g[i][0] = Matrix(1);
		g[i][1] = g[i - 1][B];
		for (int j = 2; j <= B; ++j)
			g[i][j] = g[i][j - 1] * g[i][1];
	}
	mi[0] = 1;
	for (int i = 1; i <= 5; ++i) mi[i] = mi[i - 1] * B;
}
int main() {
	GetInput();
	init();
	int x = 0;
	for (int i = 0; i < q; ++i) {
		x = read();
		Mi(x);
		ll sum = 0;
		for (int j = 0; j < n; ++j) sum ^= ans.a[0][j];
		printf("%lld\n", sum % mod);
	}
	return 0;
}