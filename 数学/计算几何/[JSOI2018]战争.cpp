#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

int const maxn = 100003;

struct Vector {
	Vector() {}
	Vector(ll _x, ll _y) :x(_x), y(_y) {}
	friend Vector operator+(Vector const &lhs, Vector const &rhs) { return Vector(lhs.x + rhs.x, lhs.y + rhs.y); }
	friend Vector operator-(Vector const &lhs, Vector const &rhs) { return Vector(lhs.x - rhs.x, lhs.y - rhs.y); }
	friend ll operator*(Vector const &A, Vector const &B) { return A.x * B.y - A.y * B.x; }
	ll len2() const { return x * x + y * y; }
	ll x, y;
};
bool cmp1(Vector const &A, Vector const &B) { return A.y < B.y || (A.y == B.y && A.x < B.x); }
bool cmp2(Vector const &A, Vector const &B) { ll a = A * B; return a > 0 || (a == 0 && A.len2() < B.len2()); }

void Convex(Vector *A, int &n) {
	static int st[maxn];
	int top = 0;
	sort(A + 1, A  + n + 1, cmp1);
	Vector bs = A[1];
	st[top = 1] = 1;
	for (int i = 1; i <= n; ++i) A[i] = A[i] - bs;
	sort(A + 2, A + n + 1, cmp2);
	for (int i = 2; i <= n; st[++top] = i++) {
		while (top >= 2 && (A[i] - A[st[top - 1]]) * (A[st[top]] - A[st[top - 1]]) >= 0)
			--top;
	}
	for (int i = 1; i <= top; ++i) A[i] = A[st[i]] + bs;
	n = top;
	A[n + 1] = A[1];
}

void MinkowskiSum(Vector *A, int n, Vector *B, int m, Vector *R, int &tot) {
	static Vector s1[maxn], s2[maxn];
	for (int i = 1; i < n; ++i) s1[i] = A[i + 1] - A[i];
	s1[n] = A[1] - A[n];
	for (int i = 1; i < m; ++i) s2[i] = B[i + 1] - B[i];
	s2[m] = B[1] - B[m];
	R[tot = 1] = A[1] + B[1];
	int p1 = 1, p2 = 1;
	while (p1 <= n && p2 <= m) { ++tot; R[tot] = R[tot - 1] + (s1[p1] * s2[p2] >= 0 ? s1[p1++] : s2[p2++]); }
	while (p1 <= n) { ++tot; R[tot] = R[tot - 1] + s1[p1++]; }
	while (p2 <= m) { ++tot; R[tot] = R[tot - 1] + s2[p2++]; }
}


Vector R[maxn << 1], C1[maxn], C2[maxn];
int siz = 0;

bool in(Vector x) {
	if (x * R[1] > 0 || R[siz] * x > 0) return false;
	int p = lower_bound(R + 1, R + siz + 1, x, cmp2) - R - 1;
	return (x - R[p]) * (R[p + 1] - R[p]) <= 0;
}

int main() {
	int n = 0, m = 0, q = 0;
	scanf("%d %d %d", &n, &m, &q);
	for (int i = 1; i <= n; ++i) scanf("%lld %lld", &C1[i].x, &C1[i].y);
	for (int i = 1; i <= m; ++i) {
		scanf("%lld %lld", &C2[i].x, &C2[i].y);
		C2[i].x = -C2[i].x; C2[i].y = -C2[i].y;
	}
	Convex(C1, n);
	Convex(C2, m);
	MinkowskiSum(C1, n, C2, m, R, siz);
	Convex(R, siz);
	Vector bs = R[1], delta;
	for (int i = 1; i <= siz; ++i) R[i] = R[i] - bs;
	for (int t = 1; t <= q; ++t) {
		scanf("%lld %lld", &delta.x, &delta.y);
		putchar(in(delta - bs) ? '1' : '0');
		putchar('\n');
	}
	return 0;
}
