/*

给定一个长度为 n 的整数数列 {a} 和 q 次操作：

修改操作：形如 1 x y, 表示将 $a_x$ 的值修改为 $y$；

询问操作：形如 2 x y，表示询问 $\sum_{i=1}^n(a_i + x) and y$ 的值。


分位处理
利用模2^(j+1)保留后j位的值，权值数据结构，维护区间和。
*/
#include <cstdio>
int n = 0, q = 0;
int a[100003];
int ar19[(1 << 20) + 7], ar18[(1 << 19) + 7], ar17[(1 << 18) + 7], ar16[(1 << 17) + 7], ar15[(1 << 16) + 7],
ar14[(1 << 15) + 7], ar13[(1 << 14) + 7], ar12[(1 << 13) + 7], ar11[(1 << 12) + 7], ar10[(1 << 11) + 7],
ar9[(1 << 10) + 7], ar8[(1 << 9) + 7], ar7[(1 << 8) + 7], ar6[(1 << 7) + 7], ar5[(1 << 6) + 7],
ar4[(1 << 5) + 7], ar3[(1 << 4) + 7], ar2[(1 << 3) + 7], ar1[(1 << 2) + 7], ar0[(1 << 1) + 7];
int *ar[20]; // ar[j]定义为保留j位时的权值树状数组
inline int lowbit(int x) { return x & -x; }
inline void add(int *tr, int N, int p, int v) {
	++p; ++N; // 偏移
	while (p <= N) {
		tr[p] += v;
		p += lowbit(p); // 为 0 时死循环
	}
}
inline int query(int *tr, int p) {
	++p; // 偏移
	int sum = 0;
	while (p) {
		sum += tr[p];
		p -= lowbit(p);
	}
	return sum;
}
inline void modiNumber(int x, int v) {
	for (int j = 0; j < 20; ++j)
		add(ar[j], (1 << (j + 1)) - 1, x % (1 << (j + 1)), v);
}
void init() {
	ar[0] = ar0; ar[1] = ar1; ar[2] = ar2; ar[3] = ar3; ar[4] = ar4; ar[5] = ar5; ar[6] = ar6; ar[7] = ar7; ar[8] = ar8; ar[9] = ar9;
	ar[10] = ar10; ar[11] = ar11; ar[12] = ar12; ar[13] = ar13; ar[14] = ar14; ar[15] = ar15; ar[16] = ar16; ar[17] = ar17; ar[18] = ar18; ar[19] = ar19;
	for (int i = 1; i <= n; ++i)
		modiNumber(a[i], +1);
}
int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	init();
	int opt = 0, x = 0, y = 0;
	for (int i = 1; i <= q; ++i) {
		scanf("%d%d%d", &opt, &x, &y);
		if (opt == 1) {
			modiNumber(a[x], -1);
			a[x] = y;
			modiNumber(a[x], +1);
		}
		else {
			long long sum = 0;
			for (int j = 0; j < 20; ++j)
				if (y & (1 << j)) {
					int mod = (1 << (j + 1));
					int l = (1 << j), r = mod - 1; // 闭区间
					l = (l - (x % mod) + mod) % mod;
					r = (r - (x % mod) + mod) % mod;
					if (l <= r)
						sum += ((long long)query(ar[j], r) - (l > 0 ? query(ar[j], l - 1) : 0)) << j;
					else
						sum += ((long long)query(ar[j], mod - 1) - query(ar[j], l - 1) + query(ar[j], r)) << j;
				}
			printf("%lld\n", sum);
		}
	}
	return 0;
}