#include <algorithm>
#include <cstdio>
using namespace std;
const int maxT = 4000300;
int n = 0, m = 0, T = 0;
int A[maxT], S[maxT];
int X[maxT], Y[maxT], pos[maxT], l = 1, r = 0;
inline void push(int x, int y, int id) {
	while (l < r && 1ll * (y - Y[r - 1]) * (X[r] - X[r - 1]) <= 1ll * (Y[r] - Y[r - 1]) * (x - X[r - 1]))
		--r;
	++r;
	X[r] = x;
	Y[r] = y;
	pos[r] = id;
}
inline int front(int k) {
	while (l < r && (Y[l + 1] - Y[l]) <= k * (X[l + 1] - X[l]))
		++l;
	return pos[l];
}
int f[maxT];
int main() {
	scanf("%d%d", &n, &m);
	if (m == 1) {
		printf("0");
		return 0;
	}
	int time = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &time);
		++time; // 偏移 0 --> 1
		if (time > T) T = time;
		++A[time];
		S[time] += time;
	}
	for (int t = 1; t <= T + m; ++t) {
		A[t] += A[t - 1];
		S[t] += S[t - 1];
	}
	l = 1, r = 0;
	push(0, 0, 0);
	for (int t = 1; t <= T + m; ++t) {
		if (t - m > 0) push(A[t - m], f[t - m] + S[t - m], t - m);
		int j = front(t);
		f[t] = f[j] + (A[t] - A[j]) * t - (S[t] - S[j]);
	}
	int ans = 0x3f3f3f3f;
	for (int i = T; i <= T + m; ++i)
		ans = min(ans, f[i]);
	printf("%d", ans);
	return 0;
}