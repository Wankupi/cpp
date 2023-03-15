inline bool cmpAngle(Vector const &A, Vector const &B) {
	double v = A * B;
	return v > eps || (v > -eps && v < eps && A.len() < B.len());
}
void Convex(Vector *a, int &n) {
	static int st[maxn];
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
	a[top + 1] = bas;
	n = top;
}
