#include <algorithm>
#include <cstdio>

int const maxn = 100003;
int n = 0, S = 0;
double A[maxn], B[maxn], R[maxn];
double f[maxn];
struct Obj {
	int id;
	double x, y, k;
};
bool cmpK(const Obj &lhs, const Obj &rhs) { return lhs.k < rhs.k; }
Obj o[maxn], pL[maxn], pR[maxn];
Obj st[maxn];
int top = 0;

void cdq(int l, int r) {
	if (l == r) {
		int x = o[l].id;
		f[x] = std::max(f[x], f[x - 1]);
		o[l].x = R[x] * f[x] / (R[x] * A[x] + B[x]);
		o[l].y = f[x] / (R[x] * A[x] + B[x]);
		return;
	}
	int mid = (l + r) >> 1;
	int cL = 0, cR = 0;
	for (int i = l; i <= r; ++i)
		if (o[i].id <= mid)
			pL[++cL] = o[i];
		else
			pR[++cR] = o[i];
	for (int i = 1; i <= cL; ++i)
		o[l + i - 1] = pL[i];
	for (int i = 1; i <= cR; ++i)
		o[l + cL + i - 1] = pR[i];
	cdq(l, mid);
	top = 0;
	for (int i = l; i <= mid; ++i) {
		while (top > 1 && (o[i].x - st[top].x) * (st[top - 1].y - st[top].y) - (o[i].y - st[top].y) * (st[top - 1].x - st[top].x) + 1e-9 > 0)
			--top;
		st[++top] = o[i];
	}
	for (int i = mid + 1; i <= r; ++i) {
		while (top >= 2 && (st[top].y - st[top - 1].y) - o[i].k * (st[top].x - st[top - 1].x) + 1e-9 < 0)
			--top;
		if (top >= 1)
			f[o[i].id] = std::max(f[o[i].id], st[top].x * A[o[i].id] + st[top].y * B[o[i].id]);
	}
	cdq(mid + 1, r);
	top = 0;
	for (cL = l, cR = mid + 1; cL <= mid && cR <= r;)
		if (o[cL].x < o[cR].x)
			st[++top] = o[cL++];
		else
			st[++top] = o[cR++];
	while (cL <= mid)
		st[++top] = o[cL++];
	while (cR <= r)
		st[++top] = o[cR++];
	for (int i = 1; i <= top; ++i)
		o[l + i - 1] = st[i];
}
int main() {
	scanf("%d %d", &n, &S);
	f[0] = S;
	for (int i = 1; i <= n; ++i) {
		scanf("%lf %lf %lf", A + i, B + i, R + i);
		o[i].id = i;
		o[i].k = -A[i] / B[i];
	}
	std::sort(o + 1, o + n + 1, cmpK);
	cdq(1, n);
	printf("%.3lf\n", f[n]);
	return 0;
}