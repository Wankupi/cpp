#include <cstdio>
#include <vector>
using namespace std;
int const maxn = 200003;
int n = 0, m = 0;
int X[maxn], Y[maxn], d[maxn];
vector<int> G[maxn];
int tag[maxn];
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d", X + i, Y + i);
		++d[X[i]];
		++d[Y[i]];
	}
	for (int i = 1; i <= m; ++i) {
		if (d[X[i]] > d[Y[i]] || (d[X[i]] == d[Y[i]] && X[i] > Y[i])) std::swap(X[i], Y[i]);
		G[X[i]].push_back(Y[i]);
	}
	int ans = 0;
	for (int x = 1; x <= n; ++x) {
		for (auto i : G[x]) tag[i] = x;
		for (auto y : G[x])
			for (auto z : G[y])
				if (tag[z] == x)
					++ans;
	}
	printf("%d", ans);
	return 0;
}