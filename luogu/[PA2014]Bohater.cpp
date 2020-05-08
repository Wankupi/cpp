#include <algorithm>
#include <cstdio>
using namespace std;
int n = 0;
long long z = 0;
struct Data {
	int d, a;
	int id;
};
// inline bool cmp1(const Data &lhs, const Data &rhs) {
// 	return lhs.d - lhs.a < rhs.d - rhs.a;
// }
inline bool cmp2(const Data &lhs, const Data &rhs) {
	return lhs.d < rhs.d;
}
inline bool cmp3(const Data &lhs, const Data &rhs) {
	return lhs.a > rhs.a;
}
Data A[100003], B[100003];
int cA = 0, cB = 0;
int main() {
	scanf("%d%lld", &n, &z);
	int a = 0, d = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", &d, &a);
		if (a >= d) {
			++cA;
			A[cA].a = a;
			A[cA].d = d;
			A[cA].id = i;
		} else {
			++cB;
			B[cB].a = a;
			B[cB].d = d;
			B[cB].id = i;
		}
	}
	sort(A + 1, A + cA + 1, cmp2);
	sort(B + 1, B + cB + 1, cmp3);
	bool ok = true;
	for (int i = 1; i <= cA && ok; ++i) {
		if (A[i].d >= z) {
			printf("NTE\n");
			return 0;
		}
		z += A[i].a - A[i].d;
	}
	for (int i = 1; i <= cB && ok; ++i) {
		if (B[i].d >= z) {
			printf("NTE\n");
			return 0;
		}
		z += B[i].a - B[i].d;
	}
	printf("TAK\n");
	for (int i = 1; i <= cA; ++i)
		printf("%d ", A[i].id);
	for (int i = 1; i <= cB; ++i)
		printf("%d ", B[i].id);
	return 0;
}