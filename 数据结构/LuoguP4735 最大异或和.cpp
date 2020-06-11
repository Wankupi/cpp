#include <cstdio>
const int maxn = 600001;
const int bit = 23;
int n = 0, m = 0;
struct Node {
	int son[2];
	int late;
} tree[maxn << 5];
int cnt = 0;
int root[maxn];
void insert(int x, int now) {
	int la = root[now > 0 ? now - 1 : 0], p = (root[now] = ++cnt);
	tree[p].late = now;
	for (int i = bit; ~i; --i) {
		bool c = (x >> i) & 1;
		tree[p].son[c ^ 1] = tree[la].son[c ^ 1];
		tree[p].son[c] = ++cnt;
		la = tree[la].son[c];
		p = tree[p].son[c];
		tree[p].late = now;
	}
}
int query(int p, int x, int least) {
	x = ~x;
	int ans = 0;
	for (int i = bit; ~i; --i) {
		int c = (x >> i) & 1;
		if (tree[p].son[c] && tree[tree[p].son[c]].late >= least) {
			ans |= (1 << i);
			p = tree[p].son[c];
		}
		else
			p = tree[p].son[c ^ 1];
	}
	return ans;
}
int main() {
	scanf("%d%d", &n, &m);
	char opt = 0;
	int sum = 0;
	int l = 0, r = 0, x = 0;
	insert(0, 0);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &x);
		insert(sum ^= x, i);
	}
	for (int i = 1; i <= m; ++i) {
		do
			opt = getchar();
		while (opt != 'A' && opt != 'Q');
		if (opt == 'A') {
			scanf("%d", &x);
			insert(sum ^= x, ++n);
		}
		else {
			scanf("%d%d%d", &l, &r, &x);
			printf("%d\n", x = query(root[r - 1], sum ^ x, l - 1));
		}
	}
	return 0;
}