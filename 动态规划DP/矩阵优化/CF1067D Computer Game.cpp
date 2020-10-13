#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
double const eps = 1e-8;
int n = 0;
double V = 0;
ll T = 0;
struct Line {
	double k, b;
	double f(double x) { return k * x + b; }
};
inline bool operator<(Line const &lhs, Line const &rhs) { return fabs(lhs.k - rhs.k) < eps ? lhs.b > rhs.b : lhs.k < rhs.k; }
double Cross(Line const &A, Line const &B) { return (B.b - A.b) / (A.k - B.k); }
Line li[100003], st[100003];
int top = 0;
struct Point {
	double x, y;
};

struct Matrix {
	Matrix() { memset(a, 0, sizeof a); }
	double a[3][3];
	double *operator[](int x) { return a[x]; }
	const double *operator[](int x) const { return a[x]; }
};
Matrix operator*(Matrix const &A, Matrix const &B) {
	Matrix r;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			for (int k = 0; k < 3; ++k)
				r[i][j] += A[i][k] * B[k][j];
	return r;
}
Matrix make_Matrix(double p, double pa) {
	Matrix r;
	r[0][0] = 1 - p;
	r[0][1] = 0;
	r[0][2] = 0;
	r[1][0] = p * V;
	r[1][1] = 1;
	r[1][2] = 0;
	r[2][0] = pa;
	r[2][1] = 1;
	r[2][2] = 1;
	return r;
}
Matrix D[40];
int main() {
	scanf("%d %lld", &n, &T);
	for (int i = 1; i <= n; ++i) {
		ll a = 0, b = 0; double p = 0;
		scanf("%lld %lld %lf", &a, &b, &p);
		V = std::max(V, b * p);
		li[i].k = p;
		li[i].b = p * a;
	}
	std::sort(li + 1, li + n + 1);
	for (int i = 1; i <= n; ++i) {
		if (fabs(li[i].k - st[top].k) < eps) continue;
		while (top >= 2 && Cross(li[i], st[top - 1]) < Cross(st[top], st[top - 1]) + eps)
			--top;
		st[++top] = li[i];
	}
	Matrix F;
	F[0][2] = 1;
	ll t = 0;
	for (int i = 1; i <= top; ++i) {
		double X = t * V - F[0][0];
		while (i < top && Cross(st[i], st[i + 1]) <= X + eps)
			++i;
		double R = i < top ? Cross(st[i], st[i + 1]) : 0.0;
		D[0] = make_Matrix(st[i].k, st[i].b);
		for (int j = 1; j <= 34; ++j)
			D[j] = D[j - 1] * D[j - 1];
		for (int j = 34; ~j; --j) {
			if (t + (1ll << j) >= T) continue;
			Matrix res = F * D[j];
			if (i < top && (t + (1ll << j)) * V - res[0][0] >= R) continue;
			F = res;
			t += (1ll << j);
		}
		F = F * D[0];
		++t;
		if (t == T) break;
	}
	printf("%.10lf\n", F[0][0]);
	return 0;
}