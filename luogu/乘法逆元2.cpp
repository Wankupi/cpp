#include <cstdio>
inline void read(int &x)
{
	int c = getchar(); x = 0;
	while (c < '0' || c > '9')
		c = getchar();
	while (c >= '0' && c <= '9') {
		x = (x << 1) + (x << 3) + c - '0';
		c = getchar();
	}
}

int n = 0, k = 0, p = 0;
// struct Result {
// 	Result(int _d, int _x, int _y) { d = _d; x = _x; y = _y; }
// 	int d, x, y;
// };

// Result exgcd(int a, int b) {
// 	if (b == 0) return Result(a, 1, 0);
// 	Result r = exgcd(b, a % b);
// 	return Result(r.d, r.y, r.x - (a / b) * r.y);
// }
int fastRow(int x,int a) {
	int ans = 1;
	while(a) {
		if(a & 1)
			ans = (long long)ans * x % p;
		x = (long long)x * x % p;
		a >>= 1;
	}
	return ans;
}

int a[5000001], inv[5000001], muti[5000001];
int main() {
	read(n); read(p); read(k);
	muti[0] = 1;
	for (int i = 1; i <= n; ++i) {
		read(a[i]);
		muti[i] = ((long long)muti[i - 1] * (long long)a[i]) % p;
	}
	//inv[n] = (exgcd(muti[n], p).x % p + p) % p;
	inv[n] = fastRow(muti[n], p - 2);
	for (int i = n - 1; i; --i)
		inv[i] = (long long)inv[i + 1] * (long long)a[i + 1] % p;//现在是前缀逆元
	for (int i = 1; i <= n; ++i)
		inv[i] = (long long)inv[i] * (long long)muti[i - 1] % p;//转化为单点逆元
	long long km = 1, ans = 0;
	for (int i = 1; i <= n; ++i) {
		km = km * k % p;
		ans = (ans + (long long)inv[i] * (long long)km % p) % p;
	}
	printf("%lld", ans);
	return 0;
}