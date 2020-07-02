#include <cstdio>
#include <cmath>
#include <deque>
#include <random>
using namespace std;
const double eps = 1e-8, pi = 3.14159265358979323846;
struct Victor {
	Victor(double _x = 0.0, double _y = 0.0) :x(_x), y(_y) {}
	double len() const { return sqrt(x * x + y * y); }
	Victor& to_one() {
		double l = len();
		if (l <= eps) return *this;
		x /= l; y /= l;
		return *this;
	}
	Victor& operator*=(double k) { x *= k; y *= k; return *this; }
	Victor& operator+=(const Victor &rhs) { x += rhs.x; y += rhs.y; return *this; }
	Victor& rotate(double th) {
		Victor t = *this;
		double si = sin(th), co = cos(th);
		x = co * t.x - si * t.y;
		y = si * t.x + co * t.y;
		return *this;
	}
	Victor& rotate_90() { double t = x; x = y; y = -t; return *this; }
	friend double operator*(const Victor &A, const Victor &B) { return A.x * B.y - B.x * A.y; }
	double x;
	double y;
};
using Point = Victor;
inline Victor operator+(const Victor &a, const Victor &b) { return Victor(a.x + b.x, a.y + b.y); }
inline Victor operator-(const Point &a, const Point &b) { return Victor(a.x - b.x, a.y - b.y); }
inline Victor operator*(double k, const Victor &v) { return Victor(k * v.x, k * v.y); }
struct Line {
	Line(Point _p, Victor _v) : P(_p), v(_v) {}
	Point P;
	Victor v;
};
inline Line make_Line(Point A, Point B) {
	return Line(A, (B - A).to_one());
}
inline bool Left(const Line &l, Point p) {
	return l.v * (p - l.P) > 0;
}

int n = 0;
int x[1001], y[1001], w[1001];

inline Victor Force(Point p, int i) {
	Victor v(x[i] - p.x, y[i] - p.y);
	v.to_one() *= w[i];
	return v;
}
inline Victor getForce(Point p) {
	Victor sum;
	for (int i = 1; i <= n; ++i) sum += Force(p, i);
	return sum;
}
deque<Point> d;
Point getCenter() {
	static default_random_engine e;
	int a = e() % d.size(), b = e() % d.size();
	while (b == a) b = e() % d.size();
	return Point(0.5 * (d[a].x + d[b].x), 0.5 * (d[a].y + d[b].y));
}

Point Jiao(Line L1, Line L2) {
	if (fabs(L1.v * L2.v) < eps) return L1.P;
	Victor u = L1.P - L2.P;
	double t = (L2.v * u) / (L1.v * L2.v);
	return L1.P + t * L1.v;
}

void cut(Line l) {
	deque<Point> nd;
	if (!Left(l, d[0])) {
		if (Left(l, d.back()))
			nd.push_back(Jiao(l, make_Line(d.back(), d[0])));
	}
	else {
		if (!Left(l, d.back()))
			nd.push_back(Jiao(l, make_Line(d.back(), d[0])));
		nd.push_back(d[0]);
	}
	for (int i = 1; i < d.size(); ++i) {
		if (!Left(l, d[i])) {
			if (Left(l, d[i - 1]))
				nd.push_back(Jiao(l, make_Line(d[i - 1], d[i])));
		}
		else {
			if (!Left(l, d[i - 1]))
				nd.push_back(Jiao(l, make_Line(d[i - 1], d[i])));
			nd.push_back(d[i]);
		}
	}
	d = nd;
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d%d%d", x + i, y + i, w + i);
	d.push_back(Point(-10000, 10000));
	d.push_back(Point(-10000, -10000));
	d.push_back(Point(10000, -10000));
	d.push_back(Point(10000, 10000));
	Point p;
	while (true) {
		p = getCenter();
		Victor F = getForce(p);
		if (F.len() < eps) break;
		F.to_one().rotate_90();
		cut(Line(p, F));
	}
	printf("%.3lf %.3lf\n", p.x, p.y);
	return 0;
}