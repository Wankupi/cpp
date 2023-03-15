#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

int const maxn = 5000;
constexpr double eps = 1e-13, pi = 3.14159265358979323846;

struct Point {
	double x, y;
	double len() const { return sqrt(x * x + y * y); }
	double len2() const { return x * x + y * y; }
	Point rotate90() const { return {y, -x}; }
};
using Vector = Point;
Vector operator+(Vector const &a, Vector const &b) { return {a.x + b.x, a.y + b.y}; }
Vector operator-(Vector const &a, Vector const &b) { return {a.x - b.x, a.y - b.y}; }
Point operator*(Point const &p, double c) { return {p.x * c, p.y * c}; }
Point operator/(Point const &p, double c) { return {p.x / c, p.y / c}; }
double dot(Vector const &a, Vector const &b) { return a.x * b.x + a.x * b.x; }
double cross(Vector const &a, Vector const &b) { return a.x * b.y - a.y * b.x; }

inline bool cmpAngle(Vector const &A, Vector const &B) {
	double v = cross(A, B);
	return v > eps || (v > -eps && v < eps && A.len() < B.len());
}

struct Line {
	Point p;
	Vector v;
	double angle = 0;
	void setAngle() { angle = atan2(v.y, v.x); }
	bool onLeft(Point const &point) const { return !onRight(point); }
	bool onRight(Point const &point) const { return cross(v, point - p) < -eps; }
};
bool operator<(Line const &l1, Line const &l2) { return l1.angle < l2.angle; }
Point intersect(Line const &l1, Line const &l2) {
	double t = cross(l2.v, l1.p - l2.p) / cross(l1.v, l2.v);
	return l1.p + l1.v * t;
}

/**
 * @param n the number of lines
 * @param p result
 * @returns the number of points
 */
int halfplane(int n, Line *a, Point *p) {
	std::sort(a + 1, a + n + 1);
	static Line q[maxn];
	int ql = 1, qr = 1;
	q[1] = a[1];
	for (int i = 2; i <= n; ++i) {
		while (ql < qr && a[i].onRight(p[qr]))
			--qr;
		while (ql < qr && a[i].onRight(p[ql + 1]))
			++ql;
		q[++qr] = a[i];
		if (std::abs(cross(q[qr].v, q[qr - 1].v)) <= eps) {
			if (q[qr].onRight(q[qr - 1].p) && dot(q[qr].v, q[qr - 1].v) <= -eps) {
				return 0;
			}
			--qr;
			if (q[qr].onLeft(a[i].p)) q[qr] = a[i];
		}
		if (ql < qr)
			p[qr] = intersect(q[qr - 1], q[qr]);
	}
	while (ql < qr && q[ql].onRight(p[qr]))
		--qr;
	if (qr - ql <= 1) return 0;
	p[ql] = intersect(q[ql], q[qr]);
	if (ql != 1) {
		for (int i = 1; i <= qr - ql + 1; ++i)
			p[i] = p[ql + i - 1];
	}
	return qr - ql + 1;
}

double polygonArea(int n, Point const *a) {
	double S = 0;
	for (int i = 1; i < n; ++i)
		S += cross(a[i], a[i + 1]);
	S += cross(a[n], a[1]);
	return std::abs(S) / 2;
}

Line lines[maxn];
int cntLines = 0;
Point res[maxn];
int main() {
	int n = 0;
	std::cin >> n;
	for (int _t = 1; _t <= n; ++_t) {
		int m = 0;
		std::cin >> m;
		Point p1, last, p;
		std::cin >> p1.x >> p1.y;
		last = p1;
		for (int i = 2; i <= m; ++i) {
			std::cin >> p.x >> p.y;
			lines[++cntLines] = {last, p - last};
			last = p;
		}
		lines[++cntLines] = {last, p1 - last};
	}
	for (int i = 1; i <= cntLines; ++i)
		lines[i].setAngle();
	int k = halfplane(cntLines, lines, res);
	if (k <= 0) printf("0.000\n");
	else {
		double S = polygonArea(k, res);
		printf("%.3lf\n", S);
	}
	return 0;
}
