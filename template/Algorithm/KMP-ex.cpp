#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int const maxn = 20000003;
int z[maxn], p[maxn];
void getNxt(char *s, int n) {
	z[1] = n;
	for (int i = 2, l = 0, r = 0; i <= n; ++i) {
		if (i <= r) z[i] = min(z[i - l + 1], r - i + 1);
		while (i + z[i] <= n && s[i + z[i]] == s[z[i] + 1]) ++z[i];
		if (i + z[i] - 1 > r) { l = i; r = i + z[i] - 1; }
	}
}
void exkmp(char *s, int n, char *t, int m) {
	getNxt(t, m);
	for (int i = 1, l = 0, r = 0; i <= n; ++i) {
		if (i <= r) p[i] = min(z[i - l + 1], r - i + 1);
		while (i + p[i] <= n && s[i + p[i]] == t[p[i] + 1]) ++p[i];
		if (i + p[i] - 1 > r) { l = i; r = i + p[i] - 1; }
	}
}
int lenS = 0, lenT = 0;
char s[maxn], t[maxn];
int main() {
	scanf("%s", s + 1);
	scanf("%s", t + 1);
	lenS = strlen(s + 1);
	lenT = strlen(t + 1);
	exkmp(s, lenS, t, lenT);
	long long ans = 0;
	for (int i = 1; i <= lenT; ++i) ans ^= (long long)i * (z[i] + 1);
	printf("%lld\n", ans);
	ans = 0;
	for (int i = 1; i <= lenS; ++i) ans ^= (long long)i * (p[i] + 1);
	printf("%lld\n", ans);
	return 0;
}