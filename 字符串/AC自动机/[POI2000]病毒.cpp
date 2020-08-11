#include <cstdio>
#include <queue>
using std::queue;
int tr[30500][2], fail[30500], ct = 0;
bool end[30500];
inline void insert(char *s) {
	int p = 0;
	while (*s) {
		int c = *s++ - '0';
		if (tr[p][c] == 0) {
			tr[p][c] = ++ct;
		}
		p = tr[p][c];
	}
	end[p] = true;
}
void getFail() {
	queue<int> q;
	for (int i = 0; i <= 1; ++i)
		if (tr[0][i]) q.push(tr[0][i]);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		end[x] |= end[fail[x]];
		for (int i = 0; i <= 1; ++i)
			if (tr[x][i]) {
				fail[tr[x][i]] = tr[fail[x]][i];
				q.push(tr[x][i]);
			}
			else
				tr[x][i] = tr[fail[x]][i];
	}
}
bool vis[30500];
bool dfs(int x) {
	if (end[x]) return false;
	if (vis[x]) return true;
	vis[x] = true;
	for (int i = 0; i <= 1; ++i) {
		if (!end[tr[x][i]])
			if (dfs(tr[x][i])) return true;
	}
	vis[x] = false;
	return false;
}
int n = 0;
char str[30005];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", str);
		insert(str);
	}
	getFail();
	if (dfs(0))
		printf("TAK");
	else
		printf("NIE");
	return 0;
}