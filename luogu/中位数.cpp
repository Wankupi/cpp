#include <cstdio>
#include <vector>
#include <algorithm>
std::vector<int> a;
int main() {
	int n = 0, t = 0;
	scanf("%d", &n);
	for (int i = 1;i <= n; ++i) {
		scanf("%d", &t);
		a.insert(std::upper_bound(a.begin(), a.end(), t), t);
		if(i&1) printf("%d\n", a[i / 2]);
	}
	return 0;
}