#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
vector<int> solve(vector<int> &v, int j) {
	if (j > 18) return vector<int>{};
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	bool have = false;
	for (int i : v) if (i & 1) { have = true; break; }
	if (!have) {
		for (int &i : v) i >>= 1;
		return solve(v, j + 1);
	}
	vector<int> a = v;
	for (int &i : a) if (i & 1) i = (i + 1) >> 1; else i >>= 1;
	for (int &i : v) i >>= 1;
	vector<int> &&ans1 = solve(a, j + 1), &&ans2 = solve(v, j + 1);
	ans1.push_back(-(1 << j)); ans2.push_back(1 << j);
	return ans1.size() < ans2.size() ? ans1 : ans2;
}
int main() {
	int n = 0, x = 0;
	vector<int> a;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) { scanf("%d", &x); a.push_back(x); }
	vector<int> &&ans = solve(a, 0);
	printf("%d\n", ans.size());
	for (int i : ans) printf("%d ", i);
	return 0;
}
