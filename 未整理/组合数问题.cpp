#include <cstdio>
int k = 0;
int c[2001][2001], sum[2001][2001];
void init()
{
	for (int i = 0; i <= 2000; ++i)
		c[i][0] = 1;
	c[1][1] = 1;
	for (int i = 2; i <= 2000; ++i)
		for (int j = 1; j <= i; ++j)
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % k;
	for (int i = 1; i <= 2000;++i){
		for (int j = 1; j <= i;++j)
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + (c[i][j] == 0);
		sum[i][i + 1] = sum[i][i];
		}
}
int main()
{
	int t = 0;
	scanf("%d%d", &t, &k);
	init();
	int n = 0, m = 0;
	while (t--)
	{
		scanf("%d%d",&n,&m);
		m = (m > n ? n : m);
		printf("%d", sum[n][m]);
	}
	return 0;
}