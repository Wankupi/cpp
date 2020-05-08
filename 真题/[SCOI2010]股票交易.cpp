#include <cstdio>
#include <cctype>
#include <cstring>
inline int read() {
	int x = 0, c = getchar();
	while (!isdigit(c)) c = getchar();
	while (isdigit(c)) { x = x * 10 + c - '0'; c = getchar(); }
	return x;
}
const int MAXT = 2003;
int T = 0, MaxP = 0, W = 0;
int ap[MAXT], bp[MAXT], as[MAXT], bs[MAXT];
int f[MAXT][MAXT];
int a[MAXT];

class Qu {
public:
	Qu(bool (*_fun)(int, int)) :fun(_fun) {}
	void reset(int _i) { l = 1; r = 0; w = _i; }
	int front(int range) { while (l <= r && fun(range, q[l])) ++l; return q[l]; }
	void push(int j) { while (l <= r && (a[q[r]] + q[r] * w) <= (a[j] + j * w)) --r; q[++r] = j; }
private:
	int q[MAXT] = { 0 };
	int l = 1, r = 0;
	int w = 0;
	bool (*fun)(int, int);
};
inline int max(int a, int b) { return a < b ? b : a; }
inline int min(int a, int b) { return a < b ? a : b; }
inline bool less(int a, int b) { return a < b; }
inline bool greater(int a, int b) { return b < a; }
Qu q1(greater), q2(less);
int main() {
	T = read(); MaxP = read(); W = read();
	for (int i = 1; i <= T; ++i) { ap[i] = read(); bp[i] = read(); as[i] = read(); bs[i] = read(); }
	memset(a, -0x3f, sizeof(a));
	f[0][0] = 0; a[0] = 0;
	int ans = 0;
	for (int i = 1; i <= T; ++i) {
		if (i - W - 1 > 0) {
			for (int j = 0; j <= MaxP; ++j)
				a[j] = max(a[j], f[i - W - 1][j]);
		}
		// 暴力
		//for (int j = 0; j <= MaxP; ++j) {
		//	f[i][j] = a[j];
		//	for (int t = max(0, j - as[i]); t < j; ++t) {
		//		f[i][j] = max(f[i][j], a[t] + t * ap[i] - j * ap[i]);
		//	}
		//	for (int t = j + 1; t <= min(j + bs[i], MaxP); ++t) {
		//		f[i][j] = max(f[i][j], a[t] + t * bp[i] - j * bp[i]);
		//	}
		//	ans = max(ans, f[i][j]);
		//}
		for (int j = 0; j <= MaxP; ++j) f[i][j] = a[j];
		q1.reset(ap[i]); q1.push(0);
		for (int j = 1; j <= MaxP; ++j) {
			int t = q1.front(j - as[i]);
			f[i][j] = max(f[i][j], a[t] + t * ap[i] - j * ap[i]);
			q1.push(j);
		}
		q2.reset(bp[i]); q2.push(MaxP);
		for (int j = MaxP - 1; j >= 0; --j) {
			int t = q2.front(j + bs[i]);
			f[i][j] = max(f[i][j], a[t] + t * bp[i] - j * bp[i]);
			q2.push(j);
		}
		for (int j = 0; j <= MaxP; ++j) ans = max(ans, f[i][j]);
	}
	printf("%d", ans);
	return 0;
}