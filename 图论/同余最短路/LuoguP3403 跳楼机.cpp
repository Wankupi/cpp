#include <cstdio>
#include <cstring>
#include <queue>
typedef long long ll;
ll h = 0, x = 0, y = 0, z = 0;
ll f[100003];
bool in[100003];
int main() {
	scanf("%lld%lld%lld%lld", &h, &x, &y, &z);
	if (x == 1 || y == 1 || z == 1) {
		printf("%lld", h);
		return 0;
	}
	memset(f, 0x3f, sizeof f);
	f[1] = 1;
	std::queue<int> q;
	q.push(1);
	in[1] = true;
	while (!q.empty()) {
		int id = q.front();
		q.pop();
		in[id] = false;
		if (f[(id + y) % x] > f[id] + y) {
			f[(id + y) % x] = f[id] + y;
			if (!in[(id + y) % x]) {
				q.push((id + y) % x);
				in[(id + y) % x] = true;
			}
		}
		if (f[(id + z) % x] > f[id] + z) {
			f[(id + z) % x] = f[id] + z;
			if (!in[(id + z) % x]) {
				q.push((id + z) % x);
				in[(id + z) % x] = true;
			}
		}
	}
	ll ans = 0;
	for (int i = 0; i < x; ++i)
		if (h >= f[i]) ans += (h - f[i]) / x + 1;
	printf("%lld", ans);
	return 0;
}