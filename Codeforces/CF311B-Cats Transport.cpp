#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
int n = 0, m = 0, p = 0;
ll t[100001], s[100001];
ll f[101][100001];
int per = 0;
ll x[100001];
int l = 0, r = 0;
inline ll y(int a) { return f[per - 1][a] + s[a]; }
inline ll min(ll a, ll b) { return a < b ? a : b; }
namespace INIT {
	int read() {
		int x = 0, c = getchar();
		while (c < '0' || c > '9') c = getchar();
		while (c >= '0' && c <= '9') { x = (x << 1) + (x << 3) + c - '0'; c = getchar(); }
		return x;
	}
	ll d[100001];
	void init() {
		n = read(); m = read(); p = read();
		for (int i = 2; i <= n; ++i)
			d[i] = read() + d[i - 1];
		int h = 0;
		for (int i = 1; i <= m; ++i) {
			h = read(); t[i] = read() - d[h];
		}
		sort(t + 1, t + m + 1);
		for (int i = 1; i <= m; ++i)
			s[i] = s[i - 1] + t[i];
	}
}
inline int front(ll k) {
	while (l < r && (y(x[l + 1]) - y(x[l]) < k * (x[l + 1] - x[l]))) ++l;
	return x[l];
}
inline void push(int a) {
	while (l < r && (y(a) - y(x[r])) * (x[r] - x[r - 1]) <= (y(x[r]) - y(x[r - 1])) * (a - x[r])) --r;
	x[++r] = a;
}
int main() {
	INIT::init();
	for (int i = 1; i <= m; ++i) f[0][i] = 0x3ffffffffffff;
	for (per = 1; per <= p; ++per) {
		l = r = 1; x[1] = 0;
		for (int j = 1; j <= m; ++j) {
			int k = front(t[j]);
			f[per][j] = min(f[per - 1][j], f[per - 1][k] + (j - k) * t[j] - s[j] + s[k]);
			push(j);
		}
	}
	cout << f[p][m] << endl;
	return 0;
}