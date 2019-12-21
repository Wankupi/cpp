#include <cstdio>
int score[5][5] = {
	{0, 0, 1, 1, 0},
	{1, 0, 0, 1, 0},
	{0, 1, 0, 0, 1},
	{0, 0, 1, 0, 1},
	{1, 1, 0, 0, 0}};
int a[201], b[201];
int main(){
	int n = 0, na = 0, nb = 0;
	scanf("%d%d%d", &n, &na, &nb);
	for (int i = 0; i != na;++i)
		scanf("%d",a + i);
	for (int i = 0; i != nb;++i)
		scanf("%d", b + i);
	int sa = 0, sb = 0;
	for (int i = 0; i != n;++i){
		sa += score[a[i % na]][b[i % nb]];
		sb += score[b[i % nb]][a[i % na]];
	}
	printf("%d %d", sa, sb);
	return 0;
}