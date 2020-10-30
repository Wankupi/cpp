#include <cstdio>
#include <bitset>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long ll;
int prime[1000000], cPrime = 0;
bitset<10000001> h;
void euler() {
	h[1] = true;
	for (int i = 2; i <= 10000000; ++i) {
		if (!h[i]) prime[cPrime++] = i;
		for (int j = 0; j < cPrime && prime[j] * i <= 10000000; ++j) {
			h[prime[j] * i] = true;
			if (i % prime[j] == 0) break;
		}
	}
}

bitset<460> base[460];
bool exist[460];
int Count = 0;
inline void clear() {
	for (int i = 0; i < 460; ++i) { base[i].reset(); exist[i] = false; }
	Count = 0;
}
bitset<460> make(int x) {
	bitset<460> X;
	for (int i = 0; i < 455 && prime[i] <= x; ++i) {
		int cnt = 0;
		while (x % prime[i] == 0) x /= prime[i], ++cnt;
		if (cnt & 1) X[i] = true;
	}
	return X;
}
void insert(bitset<460> X) {
	for (int i = 455; ~i; --i)
		if (X[i]) {
			if (exist[i]) X ^= base[i];
			else { std::swap(X, base[i]); exist[i] = true; ++Count; break; }
		}
}
struct Number {
	Number(int X) :x(X) {
		for (int i = 0; i < 455 && prime[i] <= X; ++i)
			while (X % prime[i] == 0)
				X /= prime[i];
		p = X;
	}
	int x, p;
};
inline bool operator<(Number const &lhs, Number const &rhs) { return lhs.p == rhs.p ? lhs.x < rhs.x : lhs.p < rhs.p; }


inline ll pow(ll b) {
	ll x = 2, r = 1;
	while (b) {
		if (b & 1) r = r * x % 998244353;
		x = x * x % 998244353;
		b >>= 1;
	}
	return r;
}

void solve1(int L, int R) {
	int sum = R - L + 1;
	for (int i = 0; i < cPrime && prime[i] <= R; ++i)
		if (R / prime[i] != (L - 1) / prime[i])
			--sum;
	printf("%lld\n", pow(sum));
}
void solve2(int L, int R) {
	vector<Number> v;
	v.reserve(R - L + 1);
	clear();
	for (int i = L; i <= R; ++i)
		v.emplace_back(i);
	sort(v.begin(), v.end());
	int lastP = 1;
	bitset<460> last;
	for (auto i : v) {
		if (i.p != lastP && i.p != 1) {
			lastP = i.p; ++Count;
			last = make(i.x);
		}
		else {
			bitset<460> &&g = make(i.x) ^ last;
			insert(g);
		}
	}
	int sum = R - L + 1 - Count;
	printf("%lld\n", pow(sum));
}
int main() {
	euler();
	int T = 0;
	scanf("%d", &T);
	while (T--) {
		int L = 0, R = 0;
		scanf("%d %d", &L, &R);
		if (R - L <= 7000) solve2(L, R);
		else solve1(L, R);
	}
	return 0;
}