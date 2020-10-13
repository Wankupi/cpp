#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;
ll min(ll a, ll b) { return a < b ? a : b; }
ll max(ll a, ll b) { return a < b ? b : a; }
int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a < b ? b : a; }
struct Data {
	int a, b;
};
inline bool operator<(const Data &lhs, const Data &rhs) {
	return min(lhs.a, rhs.b) == min(lhs.b, rhs.a) ? lhs.a < rhs.a : min(lhs.a, rhs.b) < min(lhs.b, rhs.a);
}
Data d[20005];
ll s[20005], c[20005];
int main() {
	int T = 0, n = 0;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i)
			scanf("%d%d", &d[i].a, &d[i].b);
		sort(d + 1, d + n + 1);
		s[0] = 0;
		s[1] = d[1].a;
		c[1] = d[1].a + d[1].b;
		for (int i = 2; i <= n; ++i) {
			s[i] = s[i - 1] + d[i].a;
			c[i] = max(c[i - 1], s[i]) + d[i].b;
		}
		printf("%lld\n", c[n]);
	}

	return 0;
}