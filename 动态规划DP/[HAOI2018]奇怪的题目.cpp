#include <cstdio>
#include <unordered_map>
using namespace std;
typedef long long ll;
int const maxn = 1000003, maxD = 1347, mod = 1000000007;
inline int pls(int a, int b) { return a + b < mod ? a + b : a + b - mod; }

int n = 0, q = 0, p = 0;
int d[maxD], cD = 0;
unordered_map<int, int> id;

inline int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

inline void getFactors() {
	for (int i = 1; i * i <= p; ++i) if (p % i == 0) d[++cD] = i;
	for (int i = cD; i >= 1; --i) if (p / d[i] != d[i]) d[++cD] = p / d[i];
	for (int i = 1; i <= cD; ++i) id[d[i]] = i;
}
int pow2[maxn];
int cnt[maxD], ans[maxD];
int f[2][maxD];

void prepare() {
	pow2[0] = 1;
	for (int i = 1; i <= n; ++i) pow2[i] = pow2[i - 1] * 2ll % mod;
	int st = 0;
	for (int i = 1; i <= cD; ++i) {
		if (cnt[i] <= 0) continue;
		st ^= 1;
		for (int j = 1; j <= cD; ++j) f[st][j] = f[st ^ 1][j];
		ll w = pow2[cnt[i]] - 1; // must >= 0
		for (int j = 1; j <= cD; ++j) {
			int k = id[gcd(d[i], d[j])];
			f[st][k] = pls(f[st][k], f[st ^ 1][j] * w % mod);
		}
		f[st][i] = pls(f[st][i], w);
	}
	for (int i = 1; i <= cD; ++i) {
		for (int j = 1; j <= i; ++j)
			if (d[i] % d[j] == 0)
				ans[i] = pls(ans[i], f[st][j]);
	}
}

int main() {
	scanf("%d %d %d", &n, &q, &p);
	getFactors();
	int x = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &x);
		x = gcd(x, p);
		++cnt[id[x]];
	}
	prepare();
	for (int i = 1; i <= q; ++i) {
		scanf("%d", &x);
		x = id[gcd(x, p)];
		printf("%d\n", ans[x]);
	}
	return 0;
}