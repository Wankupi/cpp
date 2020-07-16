#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
int n = 0, m = 0;
ll seed = 0, vmax = 0;
ll rnd() {
	ll ret = seed;
	seed = (seed * 7 + 13) % 1000000007;
	return ret;
}
ll pow(ll x, ll a, ll mod) {
	x %= mod;
	ll ret = 1;
	while (a) {
		if (a & 1) ret = ret * x % mod;
		x = x * x % mod;
		a >>= 1;
	}
	return ret;
}
struct Node {
	Node(int _l, int _r = -1, ll _V = 0) : l(_l), r(_r), v(_V) {}
	int l, r;
	mutable ll v;
};
inline bool operator<(const Node &lhs, const Node &rhs) { return lhs.l == rhs.l ? lhs.r < rhs.r : lhs.l < rhs.l; }
inline bool cmp(const Node &lhs, const Node &rhs) { return lhs.v < rhs.v; }
set<Node> tr;
using Ptr = set<Node>::iterator;
Ptr spilt(int cur) {
	Ptr p = tr.lower_bound(Node(cur));
	if (p != tr.end() && p->l == cur) return p;
	--p;
	Node L(p->l, cur - 1, p->v), R(cur, p->r, p->v);
	tr.erase(p);
	tr.insert(L);
	return tr.insert(R).first;
}
void add(int l, int r, ll x) {
	Ptr rp = spilt(r + 1), lp = spilt(l);
	while(lp != rp) {
		lp->v += x;
		++lp;
	}
}
void SET(int l, int r, ll x) {
	Ptr rp = spilt(r + 1), lp = spilt(l);
	tr.erase(lp, rp);
	tr.insert(Node(l, r, x));
}
ll Rank(int l, int r, ll x) {
	Ptr rp = spilt(r + 1), lp = spilt(l);
	vector<Node> vec;
	while (lp != rp) vec.push_back(*lp++);
	sort(vec.begin(), vec.end(), cmp);
	for (auto i : vec) {
		if (i.r - i.l + 1 < x) x -= i.r - i.l + 1;
		else return i.v;
	}
	return 0; // to ensure it can return an value.
}
ll Fang(int l, int r, ll x, ll mod) {
	Ptr rp = spilt(r + 1), lp = spilt(l);
	ll ret = 0;
	while (lp != rp) {
		ret = (ret + (lp->r - lp->l + 1) * pow(lp->v, x, mod)) % mod;
		++lp;
	}
	return ret;
}
int main() {
	scanf("%d%d%lld%lld", &n, &m, &seed, &vmax);
	int l = 1, r = 1;
	ll x = 0, y = 0;
	ll last = (rnd() % vmax) + 1;
	for (int i = 2; i <= n; ++i) {
		ll now = (rnd() % vmax) + 1;
		if (now == last)
			continue;
		else {
			tr.insert(Node(l, i - 1, last));
			l = i;
			last = now;
		}
	}
	tr.insert(Node(l, n, last));
	//tr.insert(Node(n + 1, n + 1, 0));
	for (int i = 1; i <= m; ++i) {
		int opt = (rnd() % 4) + 1;
		l = (rnd() % n) + 1;
		r = (rnd() % n) + 1;
		if (l > r) swap(l, r);
		if (opt == 3) x = (rnd() % (r - l + 1)) + 1;
		else x = (rnd() % vmax) + 1;
		if (opt == 4) y = (rnd() % vmax) + 1;

		if (opt == 1) add(l, r, x);
		else if (opt == 2) SET(l, r, x);
		else if (opt == 3) printf("%lld\n", Rank(l, r, x));
		else printf("%lld\n", Fang(l, r, x, y));
	}
	return 0;
}