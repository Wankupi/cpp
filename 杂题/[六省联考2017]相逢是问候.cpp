#include <cstdio>
#include <cmath>
typedef long long ll;
namespace OULASHAI {
	bool h[10007];
	int prime[10000], c = 0;
	void ouler() {
		h[1] = true;
		for (int i = 2; i <= 10000; ++i) {
			if (!h[i]) {
				prime[c++] = i;
			}
			for (int j = 0; j != c && prime[j] * i <= 10000; ++j) {
				h[i * prime[j]] = true;
				if (i % prime[j] == 0) break;
			}
		}
	}
	int getPhi(int x) {
		int ret = 1;
		for (int i = 0; i != c && prime[i] * prime[i] <= x; ++i)
			if (x % prime[i] == 0) {
				ret *= prime[i] - 1;
				x /= prime[i];
				while (x % prime[i] == 0) {
					ret *= prime[i];
					x /= prime[i];
				}
			}
		if (x != 1) ret *= x - 1;
		return ret;
	}
}
int n = 0, m = 0, c = 0;
int p[30], cphi = 0;
int a[50003],b[50003], t[50003];
ll s[50003], tree[50003];
inline int lowbit(int x) { return x & -x; }
void add(int pos, ll val) {
	while (pos <= n) {
		tree[pos] += val;
		if (tree[pos] >= p[0]) tree[pos] %= p[0];
		pos += lowbit(pos);
	}
}
ll query(int pos) {
	ll sum = 0;
	while (pos) {
		sum = (sum + tree[pos]) % p[0];
		pos -= lowbit(pos);
	}
	return sum;
}
int fa[50003];
inline int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
int base = 0;
ll pow1[30][20003], pow2[30][20003]; // pow1[i] = c ^ base*i, pow2[i] = c^i
bool moded1[30][20003], moded2[30][20003];
void init() {
	OULASHAI::ouler();
	while (p[cphi] != 1) {
		++cphi;
		p[cphi] = OULASHAI::getPhi(p[cphi - 1]);
	}
	fa[n + 1] = n + 1;
	for (int i = 1; i <= n; ++i) {
		s[i] = (s[i - 1] + a[i]) % p[0];
		fa[i] = i;
		b[i] = a[i];
	}
	base = 2 * sqrt(p[0]);
	for (int i = 0; i <= cphi; ++i) {
		pow2[i][0] = (i != cphi);
		moded2[i][0] = (i == cphi);
		for (int j = 1; j <= base; ++j) {
			pow2[i][j] = pow2[i][j - 1] * c;
			moded2[i][j] = moded2[i][j - 1] | (pow2[i][j] >= p[i]);
			pow2[i][j] %= p[i];
		}
	}
	for (int i = 0; i <= cphi; ++i) {
		pow1[i][0] = (i != cphi);
		moded1[i][0] = (i == cphi);
		for (int j = 1; j <= base; ++j) {
			pow1[i][j] = pow1[i][j - 1] * pow2[i][base];
			moded1[i][j] = moded1[i][j - 1] | moded2[i][base] | (pow1[i][j] >= p[i]);
			pow1[i][j] %= p[i];
		}
	}
}
int dfs(ll x, int time, int mod) {
	if(mod == cphi + 1) return 0;
	if (time == 0) return x < p[mod] ? x : (x % p[mod] + p[mod]);
	int B = dfs(x, time - 1, mod + 1);
	ll ret = pow1[mod][B / base] * pow2[mod][B % base];
	bool moded = moded1[mod][B / base] | moded2[mod][B % base] | (ret >= p[mod]);
	return moded ? ret % p[mod] + p[mod] : ret;
}
void modify(int l, int r) {
	int i = l;
	while (i <= r) {
		if (find(i) != i) {
			i = find(i);
			continue;
		}
		ll newVal = dfs(a[i], ++t[i], 0) % p[0];
		add(i, newVal - b[i]);
		b[i] = newVal;
		if ((t[i] == cphi && a[i] % p[0] != 0) || (a[i] % p[0] == 0 && t[i] == cphi + 1)) fa[i] = find(i + 1);
		++i;
	}
}
inline int query(int l, int r) {
	return ((query(r) - query(l - 1) + s[r] - s[l - 1]) % p[0] + p[0]) % p[0];
}
int main() {
	scanf("%d%d%d%d", &n, &m, p, &c);
	for (int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	init();
	int opt = 0, l = 0, r = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%d", &opt, &l, &r);
		if (opt == 0)
			modify(l, r);
		else
			printf("%d\n",query(l, r));
	}
	return 0;
}