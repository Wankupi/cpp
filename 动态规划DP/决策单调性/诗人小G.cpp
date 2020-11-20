#include <iostream>
#include <string>
#include <cmath>
using namespace std;
inline long double mpow(long double x, int b) {
	long double r = 1;
	while (b) {
		if (b & 1) r *= x;
		x *= x;
		b >>= 1;
	}
	return r;
}
int n = 0, L = 0, P = 0;
string a[100003];
int s[100003];
long double f[100003];
int pre[100003];
int q[100003], ql = 1, qr = 0;

inline long double calc(int i, int x) {
	return f[i] + mpow(abs(s[x] - s[i] + x - i - 1 - L), P);
}
inline int getTrans(int a, int b) {
	if (calc(a, n) < calc(b, n)) return n + 1;
	int L = b, R = n;
	while (L <= R) {
		int mid = (L + R) >> 1;
		if (calc(a, mid) >= calc(b, mid))
			R = mid - 1;
		else
			L = mid + 1;
	}
	return R + 1;
}
int main() {
	ios::sync_with_stdio(false);
	int T = 0;
	cin >> T;
	while (T--) {
		cin >> n >> L >> P;
		for (int i = 1; i <= n; ++i) {
			cin >> a[i];
			s[i] = s[i - 1] + a[i].length();
		}
		q[ql = qr = 1] = 0;
		for (int i = 1; i <= n; ++i) {
			while (ql < qr && getTrans(q[ql], q[ql + 1]) <= i) ++ql;
			pre[i] = q[ql];
			f[i] = calc(q[ql], i);
			while (ql < qr && getTrans(q[qr - 1], q[qr]) >= getTrans(q[qr], i))
				--qr;
			q[++qr] = i;
		}
		if (f[n] > 1e18)
			cout << "Too hard to arrange\n";
		else {
			// printf("%lld\n", (long long)f[n]);
			cout << (long long)f[n] << endl;
			static int st[100003];
			int top = 0;
			for (int x = n; x; x = pre[x]) st[++top] = x;
			st[++top] = 0;
			while (top > 1) {
				for (int i = st[top] + 1; i < st[top - 1]; ++i)
					cout << a[i] << ' ';
				cout << a[st[top - 1]] << endl;
				--top;
			}
		}
		cout << "--------------------\n";
	}
	return 0;
}