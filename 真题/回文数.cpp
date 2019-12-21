#include <cstdio>
#include <cctype>
#include <algorithm>
int a[105], n = 0, len = 0;
bool check()
{
	for (int i = 1; i <= len; i++)
		if (a[i] ^ a[len - i + 1])
			return false;
	return true;
}
int main()
{
	scanf("%d", &n);
	char ch = getchar();
	while ((!isdigit(ch)) && (!isalpha(ch)))
		ch = getchar();
	while (isdigit(ch) || isalpha(ch))
	{
		if (isdigit(ch))
			a[++len] = ch - '0';
		else
			a[++len] = ch - 'A' + 10;
		ch = getchar();
	}
	std::reverse(a + 1, a + len + 1);
	if (check())
	{
		printf("0");
		return 0;
	}
	for (int i = 1; i <= 30; i++)
	{
		for (int j = 1; j <= ((len + 1) / 2); j++)
		{
			a[j] += a[len - j + 1];
			a[len - j + 1] = a[j];
		}
		for (int j = 1; j <= len; j++)
			a[j + 1] += a[j] / n, a[j] %= n;
		if (a[len + 1])
			len++;
		if (check())
		{
			printf("STEP=%d", i);
			return 0;
		}
	}
	printf("Impossible!");
	return 0;
}