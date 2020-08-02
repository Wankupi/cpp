#include <cstdio>
#include <cstring>
#include <queue>
int n = 0, s = 0, t = 0;
int head[1003], nxt[3005], to[3005], opt[3005], cnt = 0;
double k[3005];
inline void insert(int u, int e, double K, int O) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = e;
	k[cnt] = K;
	opt[cnt] = O;
}
double T = 0.0;
inline double val(int i) {
	if (opt[i] == 1)
		return k[i] - T;
	else if (opt[i] == 2)
		return 1.0 / (k[i] + T);
	else
		return k[i];
}
double dis[1003];
bool in[1003];
int time[1003];
bool spfa() {
	std::queue<int> q;
	for (int i = 0; i <= n; ++i) {
		dis[i] = 1.0;
		in[i] = true;
		q.push(i);
	}
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		in[x] = false;
		for (int i = head[x]; i; i = nxt[i]) {
			if (dis[to[i]] < dis[x] * val(i)) {
				dis[to[i]] = dis[x] * val(i);
				if (!in[to[i]]) {
					if (++time[to[i]] > n + 1) return true;
					q.push(to[i]);
				}
			}
		}
	}
	return false;
}
int main() {
	scanf("%d%d%d", &n, &s, &t);
	int O = 0, x = 0, y = 0, K = 0;
	for (int i = 1; i <= s; ++i) {
		scanf("%d%d%d%d", &O, &x, &y, &K);
		insert(y, x, K, O);
	}
	for (int i = 1; i <= t; ++i) {
		scanf("%d%d", &x, &K);
		insert(0, x, K, 3);
		insert(x, 0, 1.0 / K, 3);
	}
	double L = 0.0, R = 100.0;
	bool moveL = false;
	while (R - L > 0.000001) {
		T = 0.5 * (L + R);
		if (spfa()) {
			moveL = true;
			L = T;
		} else
			R = T;
	}
	if (moveL == false) {
		printf("-1");
		return 0;
	}
	printf("%.6lf", L);
	return 0;
}
