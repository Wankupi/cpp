#include <cstdio>
#include <cstring>
const int maxn = 100003;
inline int min(int a, int b) { return a < b ? a : b; }
int n = 0, d = 0, m = 0;
char road[50005];
int uncertain[10];
struct Rule {
	int i, p;
	int j, q;
};
Rule rules[100003];
int head[100003], nxt[200003], to[200003], cnt = 0;
inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }
inline bool fABC01(int i, int s) {
	if (road[i] == 0)
		return s != 1;
	else if (road[i] == 1)
		return s != 0;
	else /*  if (road[i] == 2)  */
		return s;
}
inline int f01ABC(int i, int s) {
	if (road[i] == 0)
		return s + 1;
	else if (road[i] == 1)
		return s == 0 ? 0 : 2;
	else /* if (road[i] == 2) */
		return s;
}
void CreateMap() {
	cnt = 0;
	memset(head, 0, sizeof head);
	for (int i = 1; i <= m; ++i) {
		if (road[rules[i].i] == rules[i].p || road[rules[i].j] == rules[i].q) {
			if (road[rules[i].i] != rules[i].p)
				insert(rules[i].i + fABC01(rules[i].i, rules[i].p) * n, rules[i].i + (!fABC01(rules[i].i, rules[i].p)) * n);
			continue;
		}
		insert(rules[i].i + fABC01(rules[i].i, rules[i].p) * n,
			rules[i].j + fABC01(rules[i].j, rules[i].q) * n);
		insert(rules[i].j + (!fABC01(rules[i].j, rules[i].q)) * n,
			rules[i].i + (!fABC01(rules[i].i, rules[i].p)) * n);
	}
}

int dfn[maxn], low[maxn], cdfn = 0;
int stack[maxn], top = 0, sym[maxn], scc = 0;
bool in[maxn];
void tarjanClear() {
	memset(dfn, 0, sizeof dfn);
	memset(low, 0, sizeof low);
	memset(sym, 0, sizeof sym);
	cdfn = 0;
	top = 0;
	scc = 0;
}
void tarjan(int x) {
	dfn[x] = low[x] = ++cdfn;
	stack[++top] = x;
	in[x] = true;
	for (int i = head[x]; i; i = nxt[i])
		if (!dfn[to[i]]) {
			tarjan(to[i]);
			low[x] = min(low[x], low[to[i]]);
		}
		else if (in[to[i]])
			low[x] = min(low[x], dfn[to[i]]);
	if (dfn[x] == low[x]) {
		int y = 0;
		++scc;
		do {
			y = stack[top--];
			in[y] = false;
			sym[y] = scc;
		} while (y != x);
	}
}
int main() {
	scanf("%d%d", &n, &d);
	scanf("%s", road + 1);
	for (int i = 1; i <= n; ++i) {
		if (road[i] == 'a')
			road[i] = 0;
		else if (road[i] == 'b')
			road[i] = 1;
		else if (road[i] == 'c')
			road[i] = 2;
		if (road[i] == 'x')
			uncertain[++uncertain[0]] = i;
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i) {
		scanf("%d", &rules[i].i);
		do rules[i].p = getchar(); while (rules[i].p < 'A' || rules[i].p > 'C');
		scanf("%d", &rules[i].j);
		do rules[i].q = getchar(); while (rules[i].q < 'A' || rules[i].q > 'C');
		rules[i].p -= 'A';
		rules[i].q -= 'A';
	}
	for (int st = 0; st < (1 << d); ++st) {
		for (int j = 0; j < d; ++j)
			road[uncertain[j + 1]] = ((st >> j) & 1);
		CreateMap();
		tarjanClear();
		for (int i = 1; i <= 2 * n; ++i) if (!dfn[i]) tarjan(i);
		bool sign = true;
		for (int i = 1; i <= n && sign; ++i)
			if (sym[i] == sym[i + n])
				sign = false;
		if (sign) {
			for (int i = 1; i <= n; ++i) {
				if (sym[i] < sym[i + n]) putchar('A' + f01ABC(i, 0));
				else putchar('A' + f01ABC(i, 1));
			}
			printf("\n");
			return 0;
		}
	}
	printf("-1");
	return 0;
}