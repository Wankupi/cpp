#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
int n = 0, m = 0;
int t[3001], a0 = 0;
int a[3001];
inline int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
bool check() {
	if (t[1]) return false;
	int GCD = 0;
	for (int i = 2; i <= 3000; ++i)
		if (t[i]) GCD = gcd(i, GCD);
	return GCD == 1;
}
struct Distance {
	Distance(int Iden, int _dis) : id(Iden), d(_dis) {}
	int id, d;
};
bool operator<(const Distance &lhs, const Distance &rhs) {
	return lhs.d > rhs.d;
}
int dis[3001];
bool confirm[3001];
void dij() {
	memset(dis, 0x3f, sizeof dis);
	priority_queue<Distance> q;
	dis[0] = 0;
	q.push(Distance(0, 0));
	while (!q.empty()) {
		int x = q.top().id;
		q.pop();
		if (confirm[x]) continue;
		confirm[x] = true;
		for (int i = 2; i <= a[0]; ++i)
			if (dis[(x + a[i]) % a0] > dis[x] + a[i]) {
				dis[(x + a[i]) % a0] = dis[x] + a[i];
				q.push(Distance((x + a[i]) % a0, dis[(x + a[i]) % a0]));
			}
	}
}
int main() {
	scanf("%d %d", &n, &m);
	int x = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &x);
		for (int j = 0; j <= m; ++j)
			if (x > j)
				t[x - j] = 1;
	}
	if (!check()) {
		puts("-1");
		return 0;
	}
	for (int i = 1; i <= 3000; ++i)
		if (t[i]) a[++a[0]] = i;
	a0 = a[1];
	dij();
	int ans = 0;
	for (int i = 0; i < a0; ++i)
		if (dis[i] > ans) ans = dis[i];
	printf("%d", ans - a0);
	return 0;
}