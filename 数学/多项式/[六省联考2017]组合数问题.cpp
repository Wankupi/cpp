#include <cstdio>
#include <vector>
using namespace std;

int p = 0, k = 0;

vector<int> operator*(vector<int> const &lhs, vector<int> const &rhs) {
	vector<int> r(k);
	for (int i = 0; i < k; ++i)
		for (int j = 0; j < k; ++j)
			r[(i + j) % k] = (r[(i + j) % k] + (long long)(lhs[i]) * rhs[j]) % p;
	return r;
}

inline void pow(vector<int> &x, long long b, vector<int> &r) {
	r[0] = 1;
	while (b) {
		if (b & 1) r = r * x;
		x = x * x;
		b >>= 1;
	}
}

int main() {
	int n = 0, r = 0;
	scanf("%d %d %d %d", &n, &p, &k, &r);
	vector<int> ans(k), x(k);
	if (k == 1)
		x[0] = 2;
	else x[0] = x[1] = 1;
	pow(x, (long long)(k) * n, ans);
	printf("%d", ans[r]);
	return 0;
}