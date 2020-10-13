#include <cstdio>
#include <vector>
using namespace std;
using ll = long long;
const ll mod = 100003;
int n = 0, k = 0;
bool sign[100001];
vector<int> yz[mod];
ll inv[mod], fact = 1;
ll f[mod];
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i) scanf("%d", sign + i);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; i * j <= n; ++j)
			yz[i * j].push_back(i);
	inv[0] = inv[1] = 1;
	for (int i = 2; i <= n; ++i) {
		fact = fact * i % mod;
		inv[i] = (-(mod / i) * inv[mod % i] % mod + mod) % mod;
	}
	int least = 0;
	for (int i = n; i >= 1; --i)
		if (sign[i]) {
			++least;
			for (int j : yz[i]) sign[j] ^= 1;
		}
	if (least <= k) {
		printf("%lld", least * fact % mod);
		return 0;
	}
	f[n] = 1;
	for (int i = n - 1; i > k; --i) {
		f[i] = ((n + (n - i) * f[i + 1] % mod) * inv[i]) % mod;
	}
	f[k] = k;
	ll sum = 0;
	for (int i = k; i <= least; ++i) sum = (sum + f[i]) % mod;
	printf("%lld", sum * fact % mod);
	return 0;
}