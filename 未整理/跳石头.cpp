#include <cstdio>
int L = 0, N = 0, M = 0;
int a[50001];
bool check(int x)
{
	int use = 0, last = 0;
	for (int i = 1; i <= N; ++i)
		if (a[i] - a[last] >= x)
			last = i;
		else
			++use;
	return use <= M;
}
int main()
{
	scanf("%d%d%d", &L, &N, &M);
	for (int i = 1; i <= N; ++i)
		scanf("%d", a + i);
	int l = 0, r = L, mid = 0;
	while (l <= r)
	{
		mid = (l + r) >> 1;
		if (check(mid))
			l = mid + 1;
		else
			r = mid - 1;
	}
	printf("%d", l - 1);
	return 0;
}