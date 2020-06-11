#include <cstdio>
#include <queue>
using namespace std;
priority_queue<int> p;
int a = 0, b = 0, c = 0;
inline int fun(int x) {
	return a * x * x + b * x + c;
}
int val[10001], pos = 0;
int main() {
	int n = 0, m = 0;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d%d", &a, &b, &c);
		for (int x = 1; x <= m; ++x) {
			int v = fun(x);
			if (p.size() < m || v < p.top()) {
				p.push(v);
				if (p.size() > m)
					p.pop();
			} else
				break;
		}
	}
	while (!p.empty()) {
		val[++pos] = p.top();
		p.pop();
	}
	while (pos) {
		printf("%d ", val[pos--]);
	}
	return 0;
}