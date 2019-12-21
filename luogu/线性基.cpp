#include <cstdio>
typedef unsigned long long ull;
int n = 0;
ull base[60];
inline ull max(ull a, ull b) { return a < b ? b : a; }
int main() {
	scanf("%llu", &n);
	ull a = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%llu", &a);
		for (int j = 51; ~j; --j)
			if (a & (1ull << j)) {
				if (base[j])
					a ^= base[j];
				else {
					base[j] = a;
					break;
				}
			}
	}
	ull ans = 0;
	for (int i = 52; ~i;--i)
		if(base[i])
			ans = max(ans, ans ^ base[i]);
	printf("%llu", ans);
	return 0;
}