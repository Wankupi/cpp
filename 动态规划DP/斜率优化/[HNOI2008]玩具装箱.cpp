#include <cstdio>
typedef long long ll;
int n = 0, L = 0;
int a[50001];
ll s[50001], f[50001];
inline ll min(ll a, ll b) { return a < b ? a : b; }
inline ll A(const ll &i) { return s[i] + i - 1; }
inline ll B(const ll &j) { return s[j] + j + L; } // 亦是X
inline ll y(int j) { return B(j) * B(j) + f[j]; }
int q[50001], l = 1, r = 0;
void push(int j) {
	while (l < r && ((y(q[r]) - y(q[r - 1])) * (B(j) - B(q[r]))) >=
		((B(q[r]) - B(q[r - 1])) * (y(j) - y(q[r]))))
		--r;
	q[++r] = j;
}
int front(ll k) {
	while (l < r && (y(q[l + 1]) - y(q[l])) <= (B(q[l + 1]) - B(q[l])) * k)
		++l;
	return q[l];
}
int main() {
	scanf("%d%d", &n, &L);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		s[i] = s[i - 1] + a[i];
	}
	f[0] = 0;
	q[l = r = 1] = 0;
	for (int i = 1; i <= n; ++i) {
		int j = front(2 * A(i));
		f[i] = f[j] + (A(i) - B(j)) * (A(i) - B(j));
		push(i);
	}
	printf("%lld", f[n]);
	return 0;
}