#include <cstdio>
#include <cstring>
#include <cctype>
char M[1010], S[1010], k[110];
bool b[1010];//是否是大写
int main(){
	scanf("%s %s", k, S);
	int lS = strlen(S), lk = strlen(k);
	for (int i = 0; i != lS;++i){
		b[i] = isupper(S[i]);
		S[i] = tolower(S[i]);
	}
	for (int i = 0; i != lk;++i)
		k[i] = tolower(k[i]);
	for (int i = 0; i != lS;++i){
		M[i] = S[i] - (k[i % lk] - 'a');
		if(M[i]<'a')
			M[i] += 26;
		if(b[i])
			M[i] = toupper(M[i]);
	}
	M[lS] = 0;
	printf(M);
	return 0;
}