#include <cstdio>
#include <cstring>
int n = 0, m = 0, mod = 0;
char s[25];
int nxt[25];
struct Matrix {
	Matrix() { memset(a, 0, sizeof a); }
	Matrix(int) {
		memset(a, 0, sizeof a);
		for (int i = 0; i < m; ++i)
			a[i][i] = 1;
	}
	int a[23][23];
};
inline Matrix operator*(const Matrix &A, const Matrix &B) {
	Matrix ret;
	for (int k = 0; k < m; ++k) {
		for (int i = 0; i < m; ++i)
			if (A.a[i][k])
				for (int j = 0; j < m; ++j)
					(ret.a[i][j] += A.a[i][k] * B.a[k][j]) %= mod;
	}
	return ret;
}
Matrix pow(Matrix x, int t) {
	Matrix ret(1);
	while (t) {
		if (t & 1)
			ret = ret * x;
		x = x * x;
		t >>= 1;
	}
	return ret;
}
int main() {
	scanf("%d%d%d%s", &n, &m, &mod, s + 1);
	nxt[1] = 0;
	for (int i = 2; i <= m; ++i) {
		nxt[i] = nxt[i - 1];
		while (nxt[i] && s[nxt[i] + 1] != s[i])
			nxt[i] = nxt[nxt[i]];
		if (s[nxt[i] + 1] == s[i]) ++nxt[i];
	}
	Matrix f, g;
	f.a[0][0] = 1;
	g.a[0][1] = 1;
	g.a[0][0] = 9;
	for (int i = 1; i < m; ++i) {
		for (int c = '0'; c <= '9'; ++c) {
			int j = i;
			while (j && s[j + 1] != c)
				j = nxt[j];
			if (s[j + 1] == c) ++j;
			if (j != m) ++g.a[i][j];
		}
	}
	Matrix ans = f * pow(g, n);
	int sum = 0;
	for (int i = 0; i < m; ++i)
		sum = (sum + ans.a[0][i]) % mod;
	printf("%d", sum);
	return 0;
}