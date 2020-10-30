#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
typedef long long ll;
ll n = 0, m = 0, L = 0, R = 0;
vector<int> D[200003];
int main() {
	scanf("%lld %lld\n%lld %lld", &n, &m, &L, &R);
	for (int i = 1; i <= std::max(n, m); ++i)
		for (int j = i; j <= std::max(n, m); j += i)
			D[j].push_back(i);
	int ql = m + 1, qr = m;
	set<pair<int, int>> s;
	for (int x = 1; x <= n; ++x) {
		ll l = (L + x - 1) / x, r = std::min(R / x, m);
		if (l > r) {
			puts("-1");
			continue;
		}
		while (ql > l) {
			--ql;
			for (int d : D[ql]) s.insert(make_pair(d, ql));
		}
		while (qr > r) {
			for (int d : D[qr]) s.erase(make_pair(d, qr));
			--qr;
		}
		bool sign = false;
		for (int a : D[x]) {
			auto p = s.upper_bound(make_pair(a, 1000000000));
			if (p == s.end()) break;
			ll b = p->first, y = p->second;
			if (x / a * b <= n) {
				printf("%lld %lld %lld %lld\n", (long long)(x), y, x / a * b, y / b * a);
				sign = true;
				break;
			}
		}
		if (!sign)
			puts("-1");
	}
	return 0;
}