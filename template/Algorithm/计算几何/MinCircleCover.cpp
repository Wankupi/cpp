struct Circle {
	Point o;
	double r;
	bool contain(Point const &p) const { return (p - o).len() <= r; }
};
Circle make_circle(Point const &a, Point const &b) {
	return Circle{{(a.x + b.x) / 2, (a.y + b.y) / 2}, (b - a).len() / 2};
}
Circle make_circle(Point const &a, Point const &b, Point const &c) {
	Point o = intersection((a + b) / 2, (b - a).rotate90(), (a + c) / 2, (c - a).rotate90());
	return {o, (a - o).len()};
}
Circle MinCircleCover(std::vector<Point> const &a) {
	int n = a.size();
	Circle cir{a[0], 0};
	for (int i = 1; i < n; ++i) {
		if (cir.contain(a[i])) continue;
		cir = {a[i], 0};
		for (int j = 0; j < i; ++j) {
			if (cir.contain(a[j])) continue;
			cir = make_circle(a[j], a[i]);
			for (int k = 0; k < j; ++k) {
				if (cir.contain(a[k])) continue;
				cir = make_circle(a[i], a[j], a[k]);
			}
		}
	}
	return cir;
}
// advise: shuffle randomly before use.
