#include <cstdio>
int n =0,s=0;
int t[5001], w[5001], st[5001], sw[5001];
int f[5001];
inline int y(int x){ return f[x]; }
int q[5001], l = 1, r = 1;
inline int front(int k) {
	while (l < r && y(q[l + 1]) - y(q[l]) <= k * (sw[q[l + 1]] - sw[q[l]]))
		++l;
	return q[l];
}
inline void push(int x) {
	while (l < r && (y(x) - y(q[r])) * (sw[q[r]] - sw[q[r - 1]]) <= (sw[x] - sw[q[r]]) * (y(q[r]) - y(q[r - 1])))
		--r;
	q[++r] = x;
}
int main() {
	scanf("%d%d", &n, &s);
	for (int i = 1;i<=n;++i){
		scanf("%d%d", t + i, w + i);
		st[i] = st[i - 1] + t[i];
		sw[i] = sw[i - 1] + w[i];
	}
	for (int i = 1; i <= n;++i) {
		int k = front(s + st[i]);
		f[i] = f[k] - (s + st[i]) * sw[k] + st[i] * sw[i] + s * sw[n];
		push(i);
	}
	printf("%d", f[n]);
	return 0;
}