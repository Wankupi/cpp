#include <cstdio>
inline int max(int a, int b) { return a < b ? b : a; }
const int maxn = 100001;
int n = 0, m = 0;
int a[20][maxn];
int mi[20], log[maxn];
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
	 	scanf("%d", &a[0][i]);
	mi[0] = 1;
	for (int t = 1; t <= 17; ++t)
	{
		mi[t] = mi[t - 1] * 2;
		if (mi[t] <= n)
			log[mi[t]] = t;
		else break;
	}
	for (int i = 3; i <= n; ++i)
		if (!log[i])
			log[i] = log[i - 1];
	for (int j = 1; j <= 17; ++j)
		for (int i = 1; i + mi[j] - 1 <= n; ++i)
			a[j][i] = max(a[j - 1][i],
				a[j - 1][i + mi[j - 1]]);
	int l = 0, r = 0, t = 0;
	for (int i = 1; i <= m; ++i)
	{
		scanf("%d%d", &l, &r);
		t = log[r - l + 1];
		printf("%d\n", max(a[t][l], a[t][r - mi[t] + 1]));
	}
	return 0;
}