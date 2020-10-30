#include <iostream>
#include <map>
#include <cstring>
using namespace std;
typedef long long ll;
int const maxn = 600007, MASK = (1 << 30) - 1;
ll const P = 1e18;
ll inf = 0x3f3f3f3f3f3f3f3f;

struct LINT {
	LINT(ll a = 0) : high(0), low(a) {}
	LINT(ll h, ll l) : high(h), low(l) {}
	ll high, low;
};
LINT operator+(LINT const &x, ll y) { return LINT{x.high + (x.low + y) / P, (x.low + y) % P}; }
void print(LINT x) {
	if (x.high) printf("%lld%018lld\n", x.high, x.low);
	else printf("%lld\n", x.low);
}

int n = 0;
char s[maxn];
int w[maxn], nxt[maxn], anc[maxn];

ll tr[maxn]; // 维护后缀最小值 
inline int lowbit(int x) { return x & -x; }
inline void modify(int p, ll v) {
	while (0 < p) {
		if (tr[p] > v) tr[p] = v;
		p -= lowbit(p);
	}
}
inline ll query(int p) {
	ll mi = inf;
	while (p <= n) {
		if (tr[p] < mi) mi = tr[p];
		p += lowbit(p);
	}
	return mi;
}
map<ll, int> m;
ll Sum = 0;
inline void Add(int v, int t) {
	m[v] += t;
	Sum += (long long)v * t;
}
inline void Del(int v, int t) {
	m[v] -= t;
	Sum -= (long long)v * t;
	if (m[v] == 0) m.erase(v);
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	memset(tr, 0x3f, sizeof tr);
	cin >> n;
	cin >> s[1] >> w[1];
	modify(1, w[1]);
	LINT lastAns(w[1]); ll ans30 = w[1], ans26 = w[1];
	print(lastAns);
	for (int i = 2; i <= n; ++i) {
		cin >> s[i] >> w[i];
		s[i] = (s[i] - 'a' + ans26) % 26 + 'a';
		w[i] = w[i] ^ (ans30 & MASK);

		int j = nxt[i - 1];
		while (j > 0 && s[i] != s[j + 1]) j = nxt[j];
		if (s[i] == s[j + 1]) ++j;
		nxt[i] = j;
		if (s[nxt[i - 1] + 1] == s[i]) anc[i - 1] = anc[nxt[i - 1]];
		else anc[i - 1] = nxt[i - 1];

		j = nxt[i - 1];
		while (j) {
			if (s[j + 1] != s[i]) {
				Del(query(i - j), 1);
				j = nxt[j];
			}
			else j = anc[j];
		}
		modify(i, w[i]);
		if (s[1] == s[i]) Add(w[i], 1);
		map<ll, int>::iterator it;
		while ((it = m.upper_bound(w[i])) != m.end()) {
			int v = it->first, t = it->second;
			Del(v, t);
			Add(w[i], t);
		}
		lastAns = lastAns + Sum + query(1);
		ans30 = (ans30 + Sum + query(1)) & MASK;
		ans26 = (ans26 + Sum + query(1)) % 26;
		print(lastAns);
	}
	return 0;
}