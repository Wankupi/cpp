#include <cstdio>
#include <cstdlib>
int const maxn = 2000007;
class Treap {
public:
	void insert(int val);
	void erase(int val);
	int getRank(int val);
	int findRank(int k);
	int pre(int val);
	int next(int val);
	
private:
	struct Node {
		int val, key;
		int t, siz;
		Node *fa, *(ch[2]);
	};
	Node tr[maxn];
	Node *root;
	int cnt;
private:
	Node *make_Node(int val);
	bool iden(Node *x) { return x->fa ? x->fa->ch[1] == x : 0; }
	void rotate(Node *x);
	void connnect(Node *s, Node *f, int relative) {
		if (s) s->fa = f;
		if (f) f->ch[relative] = s; else root = s;
	}
	void update(Node *x) { if (x) { x->siz = x->t + (x->ch[0] ? x->ch[0]->siz : 0) + (x->ch[1] ? x->ch[1]->siz : 0); } }
	void flush(Node *x) { while (x) { update(x); x = x->fa; } }
};

inline Treap::Node* Treap::make_Node(int val) {
	Node *p = tr + ++cnt;
	p->val = val;
	p->key = rand();
	p->t = p->siz = 1;
	return p;
}

void Treap::rotate(Node *x) { // confirm x has father.
	Node *f = x->fa, *ff = f->fa;
	int m = iden(x), n = iden(x->fa);
	connnect(x->ch[m ^ 1], f, m);
	connnect(x, ff, n);
	connnect(f, x, m ^ 1);
	update(f);
	update(x);
}

void Treap::insert(int val) {
	if (root == nullptr) {
		root = make_Node(val);
		return;
	}
	Node *p = root;
	while (p) {
		if (p->val == val) { ++p->t; break; }
		int c = (p->val < val);
		if (p->ch[c] == nullptr) {
			p->ch[c] = make_Node(val);
			p->ch[c]->fa = p;
			p = p->ch[c];
			break;
		}
		p = p->ch[c];
	}
	while (p->fa && p->key > p->fa->key) rotate(p);
	if (p->fa == nullptr) root = p;
	flush(p);
}

void Treap::erase(int val) {
	Node *p = root;
	while (p && p->val != val) {
		int c = (p->val < val);
		p = p->ch[c];
	}
	if (p == nullptr) return;
	if (--p->t > 0) {
		flush(p);
		return;
	}
	while (p->ch[0] || p->ch[1]) {
		int c = (p->ch[0] && p->ch[1]) ? (p->ch[0]->key < p->ch[1]->key) : (p->ch[0] ? 0 : 1);
		rotate(p->ch[c]);
	}
	Node *f = p->fa;
	if (f == nullptr) root = nullptr;
	else f->ch[iden(p)] = nullptr;
	flush(f);
}

int Treap::getRank(int val) {
	int k = 0;
	Node *p = root;
	while (p) {
		if (p->val > val) {
			p = p->ch[0];
			continue;
		}
		k += (p->ch[0] ? p->ch[0]->siz : 0);
		if (p->val == val) break;
		k += p->t;
		p = p->ch[1];
	}
	return k + 1;
}

int Treap::findRank(int k) {
	Node *p = root;
	while (p && k) {
		if (p->ch[0] && p->ch[0]->siz >= k) {
			p = p->ch[0];
			continue;
		}
		k -= (p->ch[0] ? p->ch[0]->siz : 0);
		if (p->t >= k) return p->val;
		k -= p->t;
		p = p->ch[1];
	}
	return 0;
}

int Treap::pre(int val) {
	Node *p = root, *ans = nullptr;
	while (p) {
		if (p->val < val) {
			ans = p;
			p = p->ch[1];
		}
		else p = p->ch[0];
	}
	return ans ? ans->val : 0;
}

int Treap::next(int val) {
	Node *p = root, *ans = nullptr;
	while (p) {
		if (p->val > val) {
			ans = p;
			p = p->ch[0];
		}
		else p = p->ch[1];
	}
	return ans ? ans->val : 0;
}

Treap tr;
int main() {
	int n = 0, m = 0, opt = 0, x = 0, last = 0;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &x);
		tr.insert(x);
	}
	int ans = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d", &opt, &x);
		x ^= last;
		if (opt == 1) tr.insert(x);
		else if (opt == 2) tr.erase(x);
		else if (opt == 3) last = tr.getRank(x);
		else if (opt == 4) last = tr.findRank(x);
		else if (opt == 5) last = tr.pre(x);
		else last = tr.next(x);
		if (opt >= 3) ans ^= last;
	}
	printf("%d", ans);
	return 0;
}