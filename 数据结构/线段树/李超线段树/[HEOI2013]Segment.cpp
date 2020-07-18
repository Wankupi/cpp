#include <cstdio>
const int N = 39989;
int n = 0;
inline void swap(int &a, int &b) {
	int c = a;
	a = b;
	b = c;
}
inline int max(int a, int b) { return a < b ? b : a; }
struct Line {
	Line(int ID = 0, int X1 = 0, int Y1 = 0, int X2 = 0, int Y2 = 0) {
		id = ID; l = X1; r = X2;
		if (l > r) swap(l, r);
		k = (X1 == X2 ? max(Y1, Y2) : double(Y2 - Y1) / (X2 - X1));
		b = -k * X1 + Y1;
	}
	int id;
	int l, r;
	double k, b;
	double f(int x) const {
		if (l == r) return k;
		return k * x + b;
	}
};
inline void swap(Line &a, Line &b) {
	Line c = a;
	a = b;
	b = c;
}
int LineCnt = 0;
Line tr[N << 2];
inline bool cover(const Line &A, const Line &B, int L, int R) {
	return A.f(L) >= B.f(L) && A.f(R) >= B.f(R);
}
inline double crossX(const Line &A, const Line &B) { // 能调用这个函数的，一定不会是L=R
	return -(A.b - B.b) / (A.k - B.k);
}
void add(int p, int L, int R, Line li) {
	if (li.l <= L && R <= li.r) {
		if (cover(tr[p], li, L, R)) return; // 后加入的必然编号大，直接舍去。
		if (tr[p].id == 0 || cover(li, tr[p], L, R)) {
			tr[p] = li;
			return;
		}
		double Cx = crossX(tr[p], li);
		int mid = (L + R) >> 1;
		if (Cx <= mid) {
			if (li.f(mid) > tr[p].f(mid))
				swap(li, tr[p]);
			add(p << 1, L, mid, li);
		}
		else {
			if (li.f(mid) > tr[p].f(mid)) swap(li, tr[p]);
			add(p << 1 | 1, mid + 1, R, li);
		}
	}
	else {
		int mid = (L + R) >> 1;
		if (li.l <= mid) add(p << 1, L, mid, li);
		if (mid < li.r) add(p << 1 | 1, mid + 1, R, li);
	}
}
struct Result {
	Result(double F_x = 0.0, int ID = 0) { fx = F_x, id = ID; }
	double fx;
	int id;
};
Result query(int p, int L, int R, int x0) {
	Result res(tr[p].f(x0), tr[p].id);
	if (L == R) return res;
	int mid = (L + R) >> 1;
	Result tem;
	if (x0 <= mid)
		tem = query(p << 1, L, mid, x0);
	else
		tem = query(p << 1 | 1, mid + 1, R, x0);
	if (res.id == 0 || tem.fx > res.fx) res = tem;
	return res;
}
int main() {
	scanf("%d", &n);
	int LastAns = 0;
	int opt = 0, x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &opt);
		if (opt == 0) {
			scanf("%d", &x1);
			x1 = (x1 + LastAns - 1) % 39989 + 1;
			LastAns = query(1, 1, N, x1).id;
			printf("%d\n", LastAns);
		}
		else {
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			x1 = (x1 + LastAns - 1) % 39989 + 1;
			x2 = (x2 + LastAns - 1) % 39989 + 1;
			y1 = (y1 + LastAns - 1) % 1000000000 + 1;
			y2 = (y2 + LastAns - 1) % 1000000000 + 1;
			add(1, 1, N, Line(++LineCnt, x1, y1, x2, y2));
		}
	}
	return 0;
}