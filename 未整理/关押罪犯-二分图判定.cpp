#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
constexpr int mP = 20001, mL = 200001;
int n = 0, m = 0;
int head[mP], nxt[mL], to[mL], val[mL], cnt = 0;
inline void insert(int u, int e, int v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }
inline int max(int a, int b) { return a < b ? b : a; }
inline int min(int a, int b) { return a < b ? a : b; }
unsigned char color[mP];//#define 10 and 11 is two color
bool check(int ans) {
	memset(color, 0, sizeof(color));
	queue<int> q;
	int x = 0, y = 0;
	for (int j = 1; j <= n; ++j) {
		if (color[j]) continue;
		color[j] = 2;
		q.push(j);
		while (!q.empty()) {
			x = q.front();
			q.pop();
			for (int i = head[x]; i; i = nxt[i]) {
				if (val[i] <= ans)continue;
				y = to[i];
				if (color[y] == 0) {
					color[y] = color[x] ^ 1;
					q.push(y);
				}
				else if (color[x] == color[y])
					return false;
			}
		}
	}
	return true;
}
int main() {
	scanf("%d%d", &n, &m);
	int a = 0, b = 0, c = 0;
	int l = 0, r = 0, mid = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%d", &a, &b, &c);
		insert(a, b, c); insert(b, a, c);
		r = max(r, c);
	}
	while (l <= r) {
		mid = (l + r) >> 1;
		if (check(mid)) r = mid-1;
		else l = mid + 1;
	}
	printf("%d", r + 1);
	return 0;
}