#include <cstdio>
#include <algorithm>
#include <cmath>

typedef long double ld;
int const maxn = 50003;
ld const eps = 1e-8;
struct Vector {
	Vector() {}
	Vector(ld _x, ld _y) :x(_x), y(_y) {}
	ld len() const { return sqrt(x * x + y * y); }
	Vector rotateL90() const { return Vector(-y, x); }
	ld x, y;
};
Vector operator*(Vector const &A, ld a) { return Vector(A.x * a, A.y * a); }
Vector operator*(ld a, Vector const &A) { return Vector(A.x * a, A.y * a); }
Vector operator+(Vector const &A, Vector const &B) { return Vector(A.x + B.x, A.y + B.y); }
Vector operator-(Vector const &A, Vector const &B) { return Vector(A.x - B.x, A.y - B.y); }
ld operator*(Vector const &A, Vector const &B) { return A.x * B.y - A.y * B.x; }
ld dot(Vector const &A, Vector const &B) { return A.x * B.x + A.y * B.y; }

typedef Vector Point;

inline bool cmpAngle(Vector const &A, Vector const &B) {
	ld v = A * B;
	return v > eps || (v > -eps && v < eps && A.len() < B.len());
}
inline bool cmpY(Vector const &A, Vector const &B) {
	return A.y < B.y || (fabs(A.y - B.y) < eps && A.x < B.x);
}

int st[maxn];
void Convex(Vector *a, int &n) {
	Vector bas = a[1];
	for (int i = 2; i <= n; ++i) if (a[i].y < bas.y || (a[i].y == bas.y && a[i].x < bas.x)) bas = a[i];
	for (int i = 1; i <= n; ++i) a[i] = a[i] - bas;
	std::sort(a + 1, a + n + 1, cmpAngle);
	int top = 1;
	st[top = 1] = 1;
	for (int i = 2; i <= n; ++i) {
		while (top >= 2 && (a[i] - a[st[top - 1]]) * (a[st[top]] - a[st[top - 1]]) >= 0)
			--top;
		st[++top] = i;
	}
	for (int i = 1; i <= top; ++i) a[i] = bas + a[st[i]];
	n = top;
}

int n = 0;
Point a[maxn << 1], d[maxn << 1];
ld mxS = 1e20;
Point res[7];

void solve() {
	for (int p1 = 1, p2 = 2, p3 = 2, p4 = 2; p1 <= n; ++p1) {
		while (dot(d[p1], d[p2 + 1]) >= 0) ++p2;
		if (p3 < p2) p3 = p2;
		while (d[p1] * d[p3 + 1] >= 0) ++p3;
		if (p4 < p3) p4 = p3;
		while (dot(d[p1], d[p4 + 1]) <= 0) ++p4;
		
		ld A = d[p1] * (a[p3] - a[p1 - 1]) / d[p1].len();
		ld B = dot(d[p1], (a[p2] - a[p4])) / d[p1].len();
		if (A * B < mxS) {
			mxS = A * B;
			res[1] = a[p1] + dot((a[p2] - a[p1]), d[p1]) / d[p1].len() / d[p1].len() * d[p1];
			Vector po = d[p1].rotateL90();
			res[2] = res[1] + A / po.len() * po;
			po = po.rotateL90();
			res[3] = res[2] + B / po.len() * po;
			po = po.rotateL90();
			res[4] = res[3] + A / po.len() * po;
		}
	}
	int a = 4;
	Convex(res, a);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%Lf%LF", &a[i].x, &a[i].y);
	Convex(a, n);
	a[0] = a[n];
	for (int i = 1; i <= n; ++i) {
		d[i] = a[i] - a[i - 1];
		a[n + i] = a[i];
		d[n + i] = d[i];
	}
	d[0] = d[n];
	solve();
	printf("%.5Lf\n",  mxS);
	for (int i = 1; i <= 4; ++i)
		printf("%.5Lf %.5Lf\n", fabs(res[i].x) < eps ? 0 : res[i].x, fabs(res[i].y) < eps ? 0 : res[i].y);
	return 0;
}
