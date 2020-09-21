#include <cstdio>
#include <unordered_map>
using namespace std;
using ll = long long;
const int N = 5000000;
int prime[N], cnt = 0;
ll phi[N + 10], mu[N + 10];
void Euler() {
	phi[1] = 1; mu[1] = 1;
	for (int i = 2; i <= N; ++i) {
		if (!phi[i]) {
			prime[cnt++] = i;
			phi[i] = i - 1;
			mu[i] = -1;
		}
		for (int j = 0; j != cnt && prime[j] * i <= N; ++j) {
			if (i % prime[j]) {
				phi[prime[j] * i] = phi[i] * phi[prime[j]];
				mu[prime[j] * i] = mu[i] * mu[prime[j]];
			} else {
				phi[prime[j] * i] = phi[i] * prime[j];
				mu[prime[j] * i] = 0;
			}
		}
	}
	for (int i = 1; i <= N; ++i) {
		phi[i] += phi[i - 1];
		mu[i] += mu[i - 1];
	}
}
unordered_map<int, ll> fp, fm;
ll getPhiSum(int n) {
	if (n <= N) return phi[n];
	if (fp[n]) return fp[n];
	ll res = (long long)n * (n + 1) / 2;
	for (int l = 2, r = 0; l <= n; l = r + 1) {
		r = n / (n / l);
		res -= (r - l + 1) * getPhiSum(n / l);
	}
	return fp[n] = res;
}
ll getMuSum(int n) {
	if (n <= N) return mu[n];
	if (fm[n]) return fm[n];
	ll res = 1;
	for (int l = 2, r = 0; l <= n; l = r + 1) {
		r = n / (n / l);
		res -= (r - l + 1) * getMuSum(n / l);
	}
	return fm[n] = res;
}
int main() {
	Euler();
	int T = 0;
	scanf("%d", &T);
	int n = 0;
	for (int t = 1; t <= T; ++t) {
		scanf("%d", &n);
		printf("%lld %lld\n", getPhiSum(n), getMuSum(n));
	}
	return 0;
}