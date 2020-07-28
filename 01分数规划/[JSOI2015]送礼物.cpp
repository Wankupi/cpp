#include <cstdio>
inline double max(double a, double b) { return a < b ? b : a; }
int n = 0, k = 0, L = 0, R = 0;
int a[50003];
double dl[50003];
int id[50003], l = 1, r = 0;
inline void push(int pos, double val) { //最大值
	while (l <= r && dl[r] <= val)
		--r;
	++r;
	dl[r] = val;
	id[r] = pos;
}
inline void push2(int pos, double val) { //最小值
	while (l <= r && dl[r] >= val)
		--r;
	++r;
	dl[r] = val;
	id[r] = pos;
}
inline void pop(int limit) {
	while (l <= r && id[l] <= limit)
		++l;
}
bool check(double V) {
	// Max{i,j} - jV - Min{i,j} + vi - kv >= 0 ?
	double ans = -1e5;
	// a[i] 为最大值
	l = 1;
	r = 0;
	for (int i = L; i <= n; ++i) {
		push(i - L + 1, -a[i - L + 1] + (i - L + 1) * V);
		pop(i - R);
		if (l <= r) ans = max(ans, dl[l] + a[i] - i * V);
	}
	// a[i] 为最小值
	l = 1;
	r = 0;
	for (int i = L; i <= n; ++i) {
		push(i - L + 1, +a[i - L + 1] + (i - L + 1) * V);
		pop(i - R);
		if (l <= r) ans = max(ans, dl[l] - a[i] - i * V);
	}
	return ans >= V * k;
}
double inRangeAnswer() {
	double ans = -1e5;
	l = 1; r = 0;
	for (int i = 1; i <= n; ++i) {
		push(i, a[i]);
		pop(i - L);
		ans = max(ans, (dl[l] - a[i]) / (L - 1 + k));
	}
	l = 1; r = 0;
	for (int i = 1; i <= n; ++i) {
		push2(i, a[i]);
		pop(i - L);
		ans = max(ans, (a[i] - dl[l]) / (L - 1 + k));
	}
	return ans;
}
int main() {
	int T = 0;
	scanf("%d", &T);
	for (int t = 1; t <= T; ++t) {
		scanf("%d%d%d%d", &n, &k, &L, &R);
		for (int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		double l = 0.0, r = 1000.0, mid = 0.0;
		while (r - l > 0.000001) {
			mid = 0.5 * (l + r);
			if (check(mid))
				l = mid;
			else
				r = mid;
		}
		printf("%.4lf\n", max(l,inRangeAnswer()));
	}
	return 0;
}