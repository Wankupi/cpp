/*
增量构造
*/
#include <cstdio>
struct Node {
	int len, sum;
	Node *fail;
	Node *son[26];
};
Node tr[500005];
int cnt = -1;
Node *New(int L) {
	Node *p = tr + (++cnt);
	p->len = L;
	p->sum = 0;
	p->fail = nullptr;
	for (int i = 0; i < 26; ++i)
		p->son[i] = nullptr;
	return p;
}
char s[500005];
void init() {
	cnt = -1;
	New(0);
	New(-1);
	tr[0].fail = tr + 1;
	tr[1].fail = tr + 0;
}
Node *find(Node *cur, int x) {
	while (s[x] != s[x - cur->len - 1])
		cur = cur->fail;
	return cur;
}
Node *last = tr + 1;
void expand(int i) {
	int c = s[i] - 'a';
	Node *f = find(last, i);
	if (f->son[c] == nullptr) {
		Node *x = New(f->len + 2);
		x->fail = find(f->fail, i)->son[c];
		if (x->fail == 0) x->fail = tr;
		x->sum = x->fail->sum + 1;
		f->son[c] = x; //顺序不能变。
	}
	last = f->son[c];
}
int main() {
	init();
	scanf("%s", s + 1);
	int k = 0;
	for (int i = 1; s[i] != 0; ++i) {
		s[i] = (s[i] - 97 + k) % 26 + 97;
		expand(i);
		k = last->sum;
		printf("%d ", k);
	}
	return 0;
}