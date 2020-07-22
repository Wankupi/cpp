#include <cmath>
#include <cstdio>
int n = 0, m = 0;
int ans = 0x3f3f3f3f;
int minV[20], minS[20];
int min(int a, int b) { return a < b ? a : b; }
inline long long MaxV(int t, int mH, int mR) {
	long long sum = 0;
	for (int i = 1; i <= t; ++i)
		sum += (mH - i) * (mR - i) * (mR - i);
	return sum;
}
void dfs(int tier, int S, int V, int lastH, int lastR) {
	if (tier == 0) {
		if (V == n) ans = min(ans, S);
		return;
	}
	if (MaxV(tier, lastH, lastR) < n - V || minV[tier] > n - V) return;
	if (S + minS[tier] >= ans /*|| S + 2 * (n - V) / lastR > ans*/) return;
	for (int r = lastR - 1; r >= tier; --r) {
		for (int h = min(lastH - 1, (n - V - minV[tier - 1] + r * r) / (r * r)); h >= tier; --h) {
			if (V + r * r * h > n) continue;
			dfs(tier - 1, 2 * r * h + (tier == m ? r * r : S), V + r * r * h, h, r);
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		minV[i] = minV[i - 1] + i * i * i;
		minS[i] = minS[i - 1] + 2 * i * i;
	}
	minS[m] += m * m;
	dfs(m, 0, 0, n, sqrt(n) + 10);
	printf("%d", ans == 0x3f3f3f3f ? 0 : ans);
	return 0;
}