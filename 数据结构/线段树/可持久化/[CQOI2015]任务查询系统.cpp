#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100003;
int read() {
	int x = 0, c = getchar();
	while (c < '0' || c>'9') c = getchar();
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x;
}
struct Event {
	int time;
	int priority;
	int act;
};
bool operator<(const Event&lhs, const Event&rhs) { return lhs.time < rhs.time; }
int m = 0, n = 0;
int lsh[maxn];
Event ev[200003];
struct Node {
	int l, r;
	int cnt;
	long long sum;
};
Node tr[5000000];
int root[maxn], cnt = 0, N = 0;
int limit = 0; // 表示版本
inline int NewNode() { return ++cnt; }
inline int clone(int p) { tr[++cnt] = tr[p]; return cnt; }
void Create(int &p, int L, int R) {
	if (p == 0) p = NewNode();
	if (L == R) return;
	int mid = (L + R) >> 1;
	Create(tr[p].l, L, mid);
	Create(tr[p].r, mid + 1, R);
}
void modify(int &p, int L, int R, int x, int v) {
	if (p <= limit) p = clone(p);
	if (L == R) {
		tr[p].cnt += v;
		tr[p].sum = (long long)(tr[p].cnt) * lsh[L];
		return;
	}
	int mid = (L + R) >> 1;
	if (x <= mid) modify(tr[p].l, L, mid, x, v);
	if (x > mid) modify(tr[p].r, mid + 1, R, x, v);
	tr[p].cnt = tr[tr[p].l].cnt + tr[tr[p].r].cnt;
	tr[p].sum = tr[tr[p].l].sum + tr[tr[p].r].sum;
}
long long query(int p, int L, int R, int k) {
	Node &th = tr[p];
	if (k >= th.cnt) return th.sum;
	if (L == R)
		return (long long)(k)*lsh[L];
	int mid = (L + R) >> 1;
	if (tr[th.l].cnt >= k) return query(th.l, L, mid, k);
	else return query(th.l, L, mid, k) + query(th.r, mid + 1, R, k - tr[th.l].cnt);
}
int main() {
	m = read(); n = read();
	int s = 0, e = 0;
	for (int i = 1; i <= m; ++i) {
		s = read(); e = read(); lsh[i] = read();
		ev[i * 2 - 1] = { s, lsh[i], +1 };
		ev[i * 2] = { e + 1, lsh[i], -1 };
	}
	sort(ev + 1, ev + 2 * m + 1);
	sort(lsh + 1, lsh + m + 1);
	int *End = unique(lsh + 1, lsh + m + 1); // 离散化
	for (int i = 1; i <= 2 * m; ++i)
		ev[i].priority = lower_bound(lsh + 1, End, ev[i].priority) - lsh;
	N = End - lsh - 1;
	Create(root[0], 1, N);
	int cur = 1;
	for (int i = 1; i <= n; ++i) {
		root[i] = root[i - 1];
		limit = cnt;
		while (cur <= 2 * m && ev[cur].time <= i) {
			modify(root[i], 1, N, ev[cur].priority, ev[cur].act);
			++cur;
		}
	}
	long long pre = 1, a = 0, b = 0, c = 0;
	int x = 0, k = 0;
	for (int i = 1; i <= n; ++i) {
		x = read(); a = read(); b = read(); c = read();
		k = int(1 + (a * pre + b) % c);
		pre = query(root[x], 1, N, k);
		printf("%lld\n", pre);
	}
	return 0;
}