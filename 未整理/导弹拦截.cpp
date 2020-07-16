#include <iostream>
#include <algorithm>
using namespace std;
int maxLJ[100001], lj = 0;
int minU[100001], use = 0;
bool cmp(int a, int b) { return a > b; };
int main() {
	int a = 0;
	while (cin >> a) {
		if (maxLJ[lj] >= a || lj == 0)
			maxLJ[++lj] = a;
		else	*upper_bound(maxLJ + 1, maxLJ + lj + 1, a, cmp) = a;
		if (minU[use] < a || use == 0)
			minU[++use] = a;
		else	*lower_bound(minU + 1, minU + use + 1, a) = a;
	}
	cout << lj << endl << use;
	return 0;
}