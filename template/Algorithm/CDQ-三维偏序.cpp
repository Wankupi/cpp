#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn = 200001;
struct Data {
	int a, b, c,w,ans;
};
inline bool operator==(const Data &lhs, const Data &rhs) {
	return lhs.a == rhs.a && lhs.b == rhs.b && lhs.c == rhs.c;
}
inline bool cmp1(const Data &lhs, const Data &rhs) {
	return lhs.a == rhs.a ? (lhs.b == rhs.b ? lhs.c < rhs.c : lhs.b < rhs.b) : (lhs.a < rhs.a);
}
bool cmp2(const Data &lhs, const Data &rhs) {
	return lhs.b == rhs.b ? lhs.c < rhs.c : lhs.b < rhs.b;
}
Data tem[maxn], dat[maxn];
int n = 0, k = 0, cur = 0;
int tree[maxn];
inline int lowbit(int x) { return x & -x; }
inline void add(int p, int v) {
	while(p<=k) {
		tree[p] += v;
		p += lowbit(p);
	}
}
inline int query(int p) {
	int sum = 0;
	while (p) {
		sum += tree[p];
		p -= lowbit(p);
	}
	return sum;
}
void cdq(int l, int r) {
	if (l == r) return;
	int mid = (l + r) >> 1;
	cdq(l, mid);
	cdq(mid + 1, r);
	sort(dat + l, dat + mid + 1, cmp2);
	sort(dat + mid + 1, dat + r + 1, cmp2);
	int L = l;
	for (int R = mid + 1; R <= r; ++R) {
		while (L <= mid && dat[R].b >= dat[L].b) {
			add(dat[L].c, dat[L].w);
			++L;
		}
		dat[R].ans += query(dat[R].c);
	}
	for (int i = l; i < L; ++i)
		add(dat[i].c, -dat[i].w);
}
int ton[maxn];
int main() {
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; ++i)
		scanf("%d%d%d", &tem[i].a, &tem[i].b, &tem[i].c);
	sort(tem + 1, tem + n + 1, cmp1);
	for (int i = 1; i <= n; ++i)
		if (tem[i] == tem[i - 1])
			++dat[cur].w;
		else {
			dat[++cur] = tem[i];
			dat[cur].w = 1;
		}
	cdq(1, cur);
	for (int i = 1; i <= cur; ++i)
		ton[dat[i].ans + dat[i].w - 1] += dat[i].w;
	for (int i = 0; i != n; ++i)
		printf("%d\n", ton[i]);
	return 0;
}