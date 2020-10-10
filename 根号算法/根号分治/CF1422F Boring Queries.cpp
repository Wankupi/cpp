#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;
int const maxn = 100003, mod = 1000000007;
int const prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
					 31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
					 73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
					 127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
					 179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
					 233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
					 283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
					 353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
					 419, 421, 431, 433, 439, 443};
int n = 0;
int a[maxn], last[maxn];
short t[86][17][maxn], lg2[maxn];
map<int, int> pos;

struct Node {
	int muti;
	int lc, rc;
};
Node tr[maxn * 19];
int cntTr = 0;
void Add(int &p, int L, int R, int x, int v) {
	tr[++cntTr] = tr[p];
	p = cntTr;
	if (L == R) {
		if (tr[p].muti == 0) tr[p].muti = v;
		else tr[p].muti = (long long)tr[p].muti * v % mod;
		return;
	}
	int mid = (L + R) >> 1;
	if (x <= mid) Add(tr[p].lc, L, mid, x, v);
	else Add(tr[p].rc, mid + 1, R, x, v);
	tr[p].muti = (long long)(tr[p].lc ? tr[tr[p].lc].muti : 1) * (tr[p].rc ? tr[tr[p].rc].muti : 1) % mod;
}
int query(int p, int L, int R, int x) { // 查询前缀积
	if (p == 0) return 1;
	if (R <= x) return tr[p].muti != 0 ? tr[p].muti : 1;
	int mid = (L + R) >> 1;
	if (x <= mid) return query(tr[p].lc, L, mid, x);
	else return (long long)query(tr[p].lc, L, mid, x) * query(tr[p].rc, mid + 1, R, x) % mod;
}
int root[maxn];
void init() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		for (int j = 0; j < 86; ++j) {
			while (a[i] % prime[j] == 0) {
				++t[j][0][i];
				a[i] /= prime[j];
			}
		}
		root[i] = root[i - 1];
		if (a[i] != 1) {
			last[i] = pos[a[i]];
			pos[a[i]] = i;
			Add(root[i], 0, n, last[i], a[i]);
		}
	}
	for (int j = 0; j < 86; ++j)
		for (int k = 1; k <= 16; ++k)
			for (int i = 1; i <= n - (1 << k) + 1; ++i)
				t[j][k][i] = std::max(t[j][k - 1][i], t[j][k - 1][i + (1 << (k - 1))]);
	lg2[0] = -1;
	for (int i = 1; i <= n; ++i) lg2[i] = lg2[i / 2] + 1;
}
inline int m_pow(int x, int b) {
	int r = 1;
	while (b) {
		if (b & 1) r = (long long)r * x % mod;
		x = (long long)x * x % mod;
		b >>= 1;
	}
	return r;
}
short GetMax(int j, int l, int r) {
	int k = lg2[r - l + 1];
	return std::max(t[j][k][l], t[j][k][r - (1 << k) + 1]);
}
int main() {
	init();
	int q = 0;
	scanf("%d", &q);
	int lastAns = 0, l = 0, r = 0;
	for (int i = 1; i <= q; ++i) {
		scanf("%d %d", &l, &r);
		l = (lastAns + l) % n + 1;
		r = (lastAns + r) % n + 1;
		if (l > r) std::swap(l, r);
		int ans = 1;
		for (int j = 0; j < 86; ++j)
			ans = (long long)ans * m_pow(prime[j], GetMax(j, l, r)) % mod;
		ans = (long long)ans * query(root[r], 0, n, l - 1) % mod;
		ans = (long long)ans * m_pow(query(root[l - 1], 0, n, l - 1), mod - 2) % mod;
		lastAns = ans;
		printf("%d\n", ans);
	}
	return 0;
}