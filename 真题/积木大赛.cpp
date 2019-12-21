#include <cstdio>
int main(){
	int n = 0;
	scanf("%d", &n);
	int cnt = 0, last = 0, h = 0;
	for (int i = 1; i <= n;++i){
		scanf("%d", &h);
		if(h<last)
			cnt += last - h;
		last = h;
	}
	cnt += last;
	printf("%d", cnt);
	return 0;
}