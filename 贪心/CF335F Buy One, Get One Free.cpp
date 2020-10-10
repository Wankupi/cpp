#include <cstdio>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;
typedef long long ll;
int n = 0;
ll sum = 0;
map<ll, int, greater<ll> > a;
priority_queue<ll, vector<ll>, greater<ll> > q, tmp;
int main() {
	scanf("%d", &n);
	ll x = 0;
	for (int i = 1; i <= n; ++i) scanf("%lld", &x), sum += x, ++a[x];
	int left = 0;
	for (auto const &obj : a) {
		ll v = obj.first; int c = obj.second;
		while (left > 0 && c > 0) {
			tmp.push(v);
			--left; --c;
		}
		while(c >= 2 && (!q.empty() && 2 * v > q.top())) {
			if (q.top() < v) {  tmp.push(v); tmp.push(v); }
			else { tmp.push(2 * v - q.top()); tmp.push(q.top()); }
			q.pop();
			c -= 2;
		}
		if (c > 0 && !q.empty() && q.top() < v) q.pop(), q.push(v);
		while (!tmp.empty()) { q.push(tmp.top()); tmp.pop(); }
		left += c;
	}
	ll free = 0;
	while (!q.empty()) { free += q.top(); q.pop(); }
	printf("%lld", sum - free);
	return 0;
}