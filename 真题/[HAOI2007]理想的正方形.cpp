#include <cstdio>
int read() {
	int x = 0, c = getchar();
	while (c < '0' || c > '9')
		c = getchar();
	while ('0' <= c && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x;
}
int a = 0, b = 0, n = 0;

int m[2003][2003];
int mx[2003][2003], mi[2003][2003];
int q[2003], v[2003], l = 0, r = 0;
inline void push(int id, int val, bool(cmp)(int, int)) {
	while (l <= r && cmp(val, v[r]))
		--r;
	++r;
	q[r] = id;
	v[r] = val;
}
inline int front(int least) {
	while (l <= r && q[l] < least)
		++l;
	return v[l];
}
inline bool less(int x, int y) { return x < y; }
inline bool more(int x, int y) { return y < x; }
int main() {
	a = read();
	b = read();
	n = read();
	for (int i = 1; i <= a; ++i)
		for (int j = 1; j <= b; ++j)
			m[i][j] = read();
	for (int i = 1; i <= a; ++i) {
		l = 1;
		r = 0;
		for (int j = 1; j <= b; ++j) {
			push(j, m[i][j], more);
			mx[i][j] = front(j - n + 1);
		}
	}
	for (int i = 1; i <= a; ++i) {
		l = 1;
		r = 0;
		for (int j = 1; j <= b; ++j) {
			push(j, m[i][j], less);
			mi[i][j] = front(j - n + 1);
		}
	}
	for (int j = 1; j <= b; ++j) {
		l = 1;
		r = 0;
		for (int i = 1; i <= a; ++i) {
			push(i, mx[i][j], more);
			mx[i][j] = front(i - n + 1);
		}
	}
	for (int j = 1; j <= b; ++j) {
		l = 1;
		r = 0;
		for (int i = 1; i <= a; ++i) {
			push(i, mi[i][j], less);
			mi[i][j] = front(i - n + 1);
		}
	}
	int ans = 0x7fffffff;
	for (int i = n; i <= a; ++i)
		for (int j = n; j <= b; ++j)
			if (mx[i][j] - mi[i][j] < ans)
				ans = mx[i][j] - mi[i][j];
	printf("%d", ans);
	return 0;
}