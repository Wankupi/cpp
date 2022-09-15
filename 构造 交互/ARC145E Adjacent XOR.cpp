#include <cstdio>
#include <algorithm>
using namespace std;
using ll = unsigned long long;
int n = 0;
ll a[1003], b[1003];

int base[64];
ll val[64];
bool insert(ll x, int index) {
	for (int j = 60; ~j; --j)
		if (((x >> j) & 1)) {
			if (base[j])
				x ^= val[j];
			else { base[j] = index; val[j] = x; return true; }
		}
	return false;
}

int opt[70003], cnt = 0;

void set(int p) {
	opt[++cnt] = p;
	for (int i = 2; i <= p; ++i) b[i] ^= b[i - 1];
}

bool solve() {
	cnt = 0;
	for (int i = 1; i <= n; ++i)
		insert(b[i], i);

	for (int i = n; i >= 1; --i) {
		if (a[i] == b[i]) continue;
		while (true) {
			ll s = a[i];
			for (int j = 1; j <= i; ++j) s ^= b[j];
			int mx = 0;
			for (int j = 60; ~j; --j)
				if ((s >> j) & 1) {
					if (base[j]) {
						mx = max(mx, base[j]);
						s ^= val[j];
					}
					else return false;
				}
			if (mx == 0) break;
			set(mx + 1);
			if (cnt > 70000) return false;
		}
		set(i);
		if (cnt > 70000) return false;
	}
	return true;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
	for (int i = 1; i <= n; ++i) scanf("%lld", b + i);

	if (solve()) {
		printf("Yes\n%d\n", cnt);
		for (int i = cnt; i >= 1; --i) printf("%d%c", opt[i], " \n"[i == 1]);
	}
	else {
		printf("No\n");
	}

	return 0;
}