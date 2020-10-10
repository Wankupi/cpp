#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>
using namespace std;
typedef long long ll;
int const maxn = 300003;
int n = 0, K = 0;

struct Operation { int l, r; };
Operation a[maxn];

struct Square {
	Square(int L, int R = -1,int Iden = 0) : l(L), r(R), id(Iden) {}
	int l, r, id;
};
inline bool operator<(Square const &lhs, Square const &rhs) { return lhs.l == rhs.l ? lhs.r < rhs.r : lhs.l < rhs.l; }
set<Square> s;
using Ptr =  set<Square>::iterator;
Ptr spilt(int cur) {
	Ptr p = s.lower_bound(Square(cur));
	if (p != s.end() && p->l == cur) return p;
	--p;
	Square sqL(p->l, cur, p->id), sqR(cur, p->r, p->id);
	s.erase(p); s.insert(sqL);
	return s.insert(sqR).first;
}
struct Changes {
	Changes(int Position, int Value) : pos(Position), v(Value) {}
	int pos, v;
};
inline bool operator<(Changes const &lhs, Changes const &rhs) { return lhs.pos < rhs.pos; }
vector<Changes> modi[maxn];
void ApplyOperation(int OptId) {
	Operation &o = a[OptId];
	Ptr rp = spilt(o.r), lp = spilt(o.l);
	for (Ptr p = lp; p != rp; ++p)
		modi[OptId].push_back(Changes(p->id, (p->r - p->l)));
	s.erase(lp, rp);
	s.insert(Square(o.l, o.r, OptId));
	sort(modi[OptId].begin(), modi[OptId].end());
}
ll ans = 0;
ll delta[maxn];
bool check(ll len) {
	for (int i = 0; i <= n + 1; ++i) delta[i] = 0;
	ll U = 0, Sum = 0;
	ll CntSq = 0, Tot = 0;
	for (int R = 1, L = 1; R <= n; ++R) {
		U += a[R].r - a[R].l;
		Sum += (ll)(a[R].r - a[R].l) * L;
		delta[R + 1] = -(a[R].r - a[R].l);
		for (auto const &ch : modi[R]) {
			if (ch.pos < L) Sum -= (ll)ch.v * ch.pos;
			else {
				U -= ch.v;
				Sum -= (ll)ch.v * L;
				delta[ch.pos + 1] += ch.v;
			}
		}
		while (U >= len) {
			U += delta[++L];
			Sum += U;
		}
		CntSq += L - 1;
		Tot += Sum - U;
	}
	if (CntSq < K) return false;
	ans = Tot - (CntSq - K) * len; // 最后一次成功时，多计数的那部分的长度一定是len
	return true;
}

int main() {
	scanf("%d %d", &n, &K);
	for (int i = 1; i <= n; ++i) scanf("%d %d", &a[i].l, &a[i].r);
	s.insert(Square(1, 1000000000, 0));
	for (int i = 1; i <= n; ++i) ApplyOperation(i);
	int len = 0;
	for (int j = 30; ~j; --j) if (check(len | (1 << j))) len |= (1 << j);
	printf("%lld", ans);
	return 0;
}