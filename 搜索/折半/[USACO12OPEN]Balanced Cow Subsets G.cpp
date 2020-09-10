// Accepted with O2
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
int n = 0, Mid = 0;
int a[21];
struct State {
	int st;
	long long sum;
};
inline bool operator<(State const &lhs, State const &rhs) { return lhs.sum < rhs.sum; }
vector<State> A, B;
void dfs(int d, int limit, long long sum, int st) {
	if (d > limit) {
		if (limit == Mid) A.push_back({ st, sum });
		else B.push_back({ st,sum });
		return;
	}
	dfs(d + 1, limit, sum, st);
	dfs(d + 1, limit, sum + a[d], st | (1 << (d - 1)));
	dfs(d + 1, limit, sum - a[d], st | (1 << (d - 1)));
}
bool ok[1 << 20];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	Mid = n / 2;
	dfs(1, Mid, 0, 0);
	dfs(Mid + 1, n, 0, 0);
	sort(A.begin(), A.end());
	sort(B.begin(), B.end());
	int i = 0, j = B.size() - 1, last = 0;
	for (; i < A.size(); ++i) {
		while (j > 0 && A[i].sum + B[j].sum > 0) --j;
		last = j;
		while (A[i].sum + B[j].sum == 0) {
			ok[A[i].st | B[j].st] = true;
			--j;
		}
		if (i + 1 < A.size() && A[i + 1].sum == A[i].sum) j = last;
	}
	int cnt = 0;
	for (i = 1; i < (1 << n); ++i) cnt += ok[i];
	printf("%d", cnt);
	return 0;
}