// dij
// 使用可持久化线段树存储点权
// 查询某点开始的连续段--> （最长前缀
// 区间赋值
// 线段树比大小
//		数位hash 判相等
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
typedef unsigned long long ull;
ull const mod = 1000000007;
int const maxn = 100003, maxW = 100100, maxP = maxW << 5;
inline int read() {
	int x = 0, c = getchar(), f = 1;
	while (c < '0' || c>'9') { if (c == '-') f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}
int n = 0, m = 0, W = 0;
int S = 0, T = 0;
int head[maxn], nxt[maxn << 1], to[maxn << 1], val[maxn << 1], cLine = 0;
inline void insert(int u, int e, int v) { nxt[++cLine] = head[u]; head[u] = cLine; to[cLine] = e; val[cLine] = v; }
ull hW[maxW], mi[maxW];
inline ull rnd() { return ((ull)rand() << 48) ^ ((ull)rand() << 32) ^ ((ull)rand() << 16) ^ (ull)rand(); }

struct Node {
	bool v;
	int lmx;
	ull hash;
	int lc, rc;
};
Node tr[maxP];
int yvan[maxP];
int cP = 0, limit = 0;

void Create(int &p, int L, int R) {
	p = ++cP;
	yvan[p] = p;
	if (L == R) return;
	int mid = (L + R) >> 1;
	Create(tr[p].lc, L, mid);
	Create(tr[p].rc, mid + 1, R);
}

int queryLen(int p, int L, int R, int l) {
	if (L == R || l <= L)
		return tr[p].lmx;
	int mid = (L + R) >> 1;
	if (l <= mid) {
		int k = queryLen(tr[p].lc, L, mid, l);
		if (k == mid - l + 1) return k + tr[tr[p].rc].lmx;
		else return k;
	}
	else return queryLen(tr[p].rc, mid + 1, R, l);
}

void set0(int &p, int L, int R, int l, int r) {
	if (l <= L && R <= r) {
		p = yvan[p]; // 挂到最初的树上
		return;
	}
	if (p <= limit) {
		tr[++cP] = tr[p];
		yvan[cP] = yvan[p];
		p = cP;
	}
	int mid = (L + R) >> 1;
	if (l <= mid) set0(tr[p].lc, L, mid, l, r);
	if (r > mid) set0(tr[p].rc, mid + 1, R, l, r);
	tr[p].hash = tr[tr[p].lc].hash ^ tr[tr[p].rc].hash;
	tr[p].lmx = tr[tr[p].lc].lmx;
	if (tr[p].lmx == mid - L + 1) tr[p].lmx += tr[tr[p].rc].lmx;
}

void set1(int &p, int L, int R, int x) {
	if (p <= limit) {
		tr[++cP] = tr[p];
		p = cP;
	}
	if (L == R) {
		tr[p].v = true;
		tr[p].hash = hW[L];
		tr[p].lmx = 1;
		return;
	}
	int mid = (L + R) >> 1;
	if (x <= mid) set1(tr[p].lc, L, mid, x);
	else set1(tr[p].rc, mid + 1, R, x);
	tr[p].hash = tr[tr[p].lc].hash ^ tr[tr[p].rc].hash;
	tr[p].lmx = tr[tr[p].lc].lmx;
	if (tr[p].lmx == mid - L + 1) tr[p].lmx += tr[tr[p].rc].lmx;
}

int cmp(int p1, int p2, int L, int R) {
	if (tr[p1].hash == tr[p2].hash) return 0;
	if (L == R) return int(tr[p2].v) - int(tr[p1].v);
	int mid = (L + R) >> 1;
	int k = cmp(tr[p1].rc, tr[p2].rc, mid + 1, R);
	if (k == 0) return cmp(tr[p1].lc, tr[p2].lc, L, mid);
	else return k;
}

int disRt[maxn], from[maxn], goby[maxn];
bool confirmed[maxn];
int getVal(int x, int v) {
	int nrt = disRt[x];
	limit = cP;
	int len = queryLen(nrt, 0, W, v);
	if (len >= 1)
		set0(nrt, 0, W, v, v + len - 1);
	set1(nrt, 0, W, v + len);
	return nrt;
}
struct Distance {
	Distance(int Iden, int root) :id(Iden), diRt(root) {}
	int id;
	int diRt;
};
inline bool operator<(Distance const &lhs, Distance const &rhs) { return cmp(lhs.diRt, rhs.diRt, 0, W) < 0; }
void dij() {
	Create(disRt[S], 0, W);
	std::priority_queue<Distance> q;
	q.push(Distance(S, disRt[S]));
	while (!q.empty()) {
		int x = q.top().id;
		q.pop();
		if (confirmed[x]) continue;
		confirmed[x] = true;
		for (int i = head[x]; i; i = nxt[i])
			if (!confirmed[to[i]]) {
				int nrt = getVal(x, val[i]);
				if (disRt[to[i]] == 0 || cmp(nrt, disRt[to[i]], 0, W) > 0) {
					disRt[to[i]] = nrt;
					q.push(Distance(to[i], disRt[to[i]]));
					from[to[i]] = x;
					goby[to[i]] = val[i];
				}
				else cP = limit;
			}
	}
}
ull minVal = 0;
int st[maxn];
void find_way() {
	int x = T;
	while (x) {
		st[++st[0]] = x;
		if (x != S) minVal = (minVal + mi[goby[x]]) % mod;
		x = from[x];
	}
}

int main() {
	n = read(); m = read();
	int x = 0, y = 0, z = 0;
	for (int i = 1; i <= m; ++i) {
		x = read(); y = read(); z = read();
		insert(x, y, z);
		insert(y, x, z);
		if (z > W) W = z;
	}
	S = read(); T = read();
	W += 32;
	for (int i = 0; i <= W; ++i) {
		hW[i] = rnd();
		mi[i] = (i >= 1 ? mi[i - 1] * 2 % mod : 1);
	}

	dij();

	if (confirmed[T]) {
		find_way();
		printf("%llu\n%d\n", minVal, st[0]);
		for (int i = st[0]; i >= 1; --i) printf("%d ", st[i]);
	}
	else puts("-1");
	return 0;
}