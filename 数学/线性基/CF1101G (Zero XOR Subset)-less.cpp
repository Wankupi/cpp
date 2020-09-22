#include <algorithm>
#include <cstdio>
int n = 0;
unsigned int a[200003], s[200003];
unsigned int base[32], cnt = 0;
void insert(unsigned int x) {
	for (int i = 31; ~i && x; --i)
		if ((x >> i) & 1) {
			if (base[i])
				x ^= base[i];
			else
				std::swap(base[i], x), ++cnt;
		}
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%u", a + i);
		s[i] = s[i - 1] ^ a[i];
	}
	if (s[n] == 0) {
		printf("-1");
		return 0;
	}
	for (int i = 1; i <= n; ++i) {
		insert(s[i]);
	}
	printf("%u", cnt);
	return 0;
}