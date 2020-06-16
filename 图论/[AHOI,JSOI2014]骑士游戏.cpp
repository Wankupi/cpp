#include <cstdio>
#include <queue>
using namespace std;
typedef long long ll;
int n = 0;
ll s[200001];

int head[200001], nxt[1000001], to[1000001], cnt = 0; // Zheng
inline void insert(int u, int e) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = e;
}
int head2[200001], nxt2[1000001], to2[1000001], cnt2 = 0; // Fan
inline void insert2(int u, int e) {
	nxt2[++cnt2] = head2[u];
	head2[u] = cnt2;
	to2[cnt2] = e;
}
ll dis[200001];
bool inQ[200001];
void spfa() {
	queue<int> q;
	for (int i = 1; i <= n; ++i) {
		inQ[i] = true;
		q.push(i);
	}
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		inQ[x] = false;
		ll sum = s[x];
		for (int i = head[x]; i; i = nxt[i])
			sum += dis[to[i]];
		if (sum < dis[x]) {
			dis[x] = sum;
			for (int i = head2[x]; i; i = nxt2[i])
				if (!inQ[to2[i]]) {
					q.push(to2[i]);
					inQ[to2[i]] = true;
				}
		}
	}
}
int main() {
	scanf("%d", &n);
	int r = 0, x = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%lld%lld%d", s + i, dis + i, &r);
		for (int j = 1; j <= r; ++j) {
			scanf("%d", &x);
			insert(i, x);
			insert2(x, i);
		}
	}
	spfa();
	printf("%lld", dis[1]);
	return 0;
}