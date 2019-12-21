#include <cstdio>
const int maxN = 130;
int a[maxN][maxN], sum[maxN][maxN];
int n = 0;
int f[1001];
int max(int a, int b) { return a < b ? b : a; }
int maxJZ()
{
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			sum[i][j] = sum[i][j - 1] + a[i][j];
	int ans = 0;
	for (int len1 = 1; len1 <= n; ++len1)
		for (int len2 = 1; len2 <= len1; ++len2)
		{
			f[0] = 1;
			for (int i = 1; i <= n; ++i)
			{
				f[i] = max(f[i - 1] + sum[i][len1] - sum[i][len2 - 1],
						   sum[i][len1] - sum[i][len2 - 1]);
				ans = max(ans, f[i]);
			}
		}
	return ans;
}

int main(){
	scanf("%d", &n);
	for (int i = 1; i <= n;++i)
		for (int j = 1; j <= n;++j)
			scanf("%d", &a[i][j]);
	printf("%d", maxJZ());
	return 0;
}
