#include <cstdio>
#include <queue>
#include <set>
using namespace std;
int n = 0;
int a[100001], b[100001];
struct Combine {
	Combine(int _a, int _b) : i(_a), j(_b) {}
	int val() const { return a[i] + b[j]; }
	int i, j;
};
inline bool operator<(const Combine &lhs, const Combine &rhs) { return lhs.val() > rhs.val(); }
priority_queue<Combine> q;
set<pair<int, int> > s;
inline void add(int i, int j) {
	Combine c(i, j);
	if (s.find(make_pair(i, j)) == s.end()) {
		s.insert(make_pair(i, j));
		q.push(c);
	}
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for (int i = 1; i <= n; ++i)
		scanf("%d", b + i);
	add(1, 1);
	for (int t = 1; t <= n; ++t) {
		Combine c = q.top();
		q.pop();
		printf("%d ", c.val());
		add(c.i + 1, c.j);
		add(c.i, c.j + 1);
	}
	return 0;
}