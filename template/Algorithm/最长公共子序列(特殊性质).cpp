// 两个序列 都是n排列

#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn = 100003;
int n = 0;
int a[maxn], b[maxn];
int q[maxn], c = 0;
int main() {
	scanf("%d", &n);
	int t = 0;
	for (int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &t);
		b[t] = i;
	}
	for (int i = 1; i <= n; ++i)
		a[i] = b[a[i]];
	for (int i = 1; i <= n; ++i) {
		if (a[i] > q[c]) {
			q[++c] = a[i];
		} else {
			*lower_bound(q + 1, q + c + 1, a[i]) = a[i];
		}
	}
	printf("%d", c);
	return 0;
}