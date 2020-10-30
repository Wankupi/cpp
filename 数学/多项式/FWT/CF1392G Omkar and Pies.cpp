#include <cstdio>
#include <bitset>
#include <cstring>
#include <algorithm>
using namespace std;
int n = 0, m = 0, k = 0;
bitset<20> S, T;
char buff[30]; int per[20];
int f[1 << 20], g[1 << 20];
inline int CountBits(int x) { int r = 0;
	while (x) {
		if (x & 1) ++r;
		x >>= 1;
	}
	return r;
}
int main() {
	scanf("%d %d %d", &n, &m, &k);
	scanf("%s", buff);
	for (int i = 0; i < k; ++i)
		if (buff[i] == '1')
			S[i] = 1;
	scanf("%s", buff);
	for (int i = 0; i < k; ++i)
		if (buff[i] == '1')
			T[i] = 1;
	for (int i = 0; i < k; ++i) per[i] = i;
	memset(f, 0x3f, sizeof f);
	memset(g, -0x3f, sizeof g);
	f[S.to_ulong()] = 0;
	g[T.to_ulong()] = 0;
	int a = 0, b = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d %d", &a, &b);
		--a; --b;
		std::swap(per[a], per[b]);
		a = per[a]; b = per[b];
		bool A = S[a], B = S[b];
		S[a] = B; S[b] = A;
		A = T[a]; B = T[b];
		T[a] = B; T[b] = A;
		f[S.to_ulong()] = std::min(f[S.to_ulong()], i);
		g[T.to_ulong()] = std::max(g[T.to_ulong()], i);
	}
	int K = 1 << k;
	for (int len = 1; len < K; len <<= 1) {
		for (int i = 0; i < K; i += 2 * len) {
			for (int j = 0; j < len; ++j) {
				f[i + j] = std::min(f[i + j], f[i + j + len]);
				g[i + j] = std::max(g[i + j], g[i + j + len]);
			}
		}
	}
	int ans = 0, L = 0, R = n; // R must be n
	for (int i = K - 1; i >= 0; --i)
		if (CountBits(i) > ans && g[i] - f[i] >= m) {
			ans = CountBits(i);
			L = f[i]; R = g[i];
		}
	printf("%d\n%d %d\n", 2 * ans + k - CountBits(S.to_ulong()) - CountBits(T.to_ulong()), L + 1, R);
	return 0;
}