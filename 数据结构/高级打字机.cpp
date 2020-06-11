#include <cstdio>
#include <cctype>
inline void read(char &C) { do C = getchar(); while (!isalpha(C)); }
int n = 0;
int root[100001];
struct Node {
	char v;
	int last[20];
	int len;
};
Node a[100001];
int cnt = 0;
void insert(int &p, char c) {
	a[++cnt].last[0] = p; a[cnt].len = a[p].len + 1; a[cnt].v = c;
	p = cnt;
	for (int j = 1; j <= 18;++j)
		a[p].last[j] = a[a[p].last[j - 1]].last[j - 1];
}
char query(int p, int x) {
	int jump = a[p].len - x;
	for (int j = 18; ~j;--j) if(jump&(1<<j)) p = a[p].last[j];
	return a[p].v;
}
struct CHANGE { int pos, last[20]; };
int change[100001], ccnt = 0;
int main() {
	scanf("%d", &n);
	char opt = 0, c = 0; int x = 0;
	for (int i = 1; i <= n;++i) {
		root[i] = root[i - 1];
		read(opt);
		if(opt!='Q')
			change[++ccnt] = i;
		switch (opt) {
		case 'T':
			read(c); insert(root[i], c);
			break;
		case 'U':
			scanf("%d", &x);
			change[ccnt] = change[ccnt - x - 1];
			root[i] = root[change[ccnt]];
			break;
		case 'Q':
			scanf("%d", &x);
			printf("%c\n", query(root[i], x));
			break;
		}
	}
	return 0;
}