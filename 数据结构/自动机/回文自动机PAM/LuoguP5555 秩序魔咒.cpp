#include <cstdio>
#include <queue>
using std::queue;
const int maxn = 260850;
struct PAM {
	struct Node {
		int len;
		Node *fail;
		Node *son[26];
	};
	char *s;
	Node tr[maxn];
	void init() {
		tr[0].fail = tr + 1;
		tr[1].fail = tr + 0;
		tr[0].len = 0;
		tr[1].len = -1;
		for (int i = 0; i < 26; ++i)
			tr[0].son[i] = tr[1].son[i] = tr;
		last = tr + 1;
		cnt = 1;
	}
	void expand(int i) {
		int c = s[i] - 'a';
		Node *f = getFa(last, i);
		if (f->son[c] == tr) {
			Node *x = New();
			x->len = f->len + 2;
			x->fail = getFa(f->fail, i)->son[c];
			f->son[c] = x;
		}
		last = f->son[c];
	}
	void make() {
		init();
		for (int i = 1; s[i]; ++i)
			expand(i);
	}
private:
	int cnt = 0;
	Node *last;
	Node *New() {
		Node *x = tr + (++cnt);
		x->len = 0;
		x->fail = nullptr;
		for (int i = 0; i < 26; ++i) x->son[i] = tr + 0;
		return x;
	}
	Node *getFa(Node *cur, int x) {
		while (s[x] != s[x - cur->len - 1]) cur = cur->fail;
		return cur;
	}
};
int n = 0, m = 0;
char s1[maxn], s2[maxn];
PAM A, B;
int ans = 0, time = 0;
struct State {
	PAM::Node *p1, *p2;
};
void bfs() {
	queue<State> q;
	q.push({ A.tr, B.tr });
	q.push({ A.tr + 1, B.tr + 1 });
	while (!q.empty()) {
		State st = q.front(); q.pop();
		if (st.p1->len > ans) {
			ans = st.p1->len;
			time = 1;
		}
		else if (st.p1->len == ans) ++time;
		for (int i = 0; i < 26; ++i)
			if (st.p1->son[i] != A.tr && st.p2->son[i] != B.tr)
				q.push({ st.p1->son[i], st.p2->son[i] });
	}
}
int main() {
	scanf("%d %d\n%s\n%s", &n, &m, s1 + 1, s2 + 1);
	A.s = s1;
	B.s = s2;
	A.make();
	B.make();
	bfs();
	printf("%d %d", ans, time);
	return 0;
}