/*
关于manacher的笔记：

将序列用某个值分割
	eg. 1 2 3 -> | 1 | 2 | 3 | 
前后加入一对不同的元素表示头或尾（或者在程序中检查越界）
	eg. $ | 1 | 2 | 3 | %

需要存储的变量
a[]		序列
len[]	以某点为中心的最大回文半径
pos		以扫到的右界最大的元素的编号
r		最大右界 （可用pos+len[pos]-1代替）
ans		答案

*/
template<typename Type>
/* [inline] */void init(Type *p, int n){
	a[] = create a new Type Array in two times n
	a[0]='/'; int cnt=0;
	for(int i=1;i<=n;++i)
		a[2*i-1]='|',a[2*i]=p[i];
	a[2*n+1]='|',a[2*n+2]='\\';
}
template<typename Type>
int manacher(Type *t, int n){
	n = init(t,n);//in some cases, this can be omitted
	int ans = 0;
	int pos = 0, r = 0;
	len[0] = 1;
	for (int i = 1; i <= n; ++i) {
		if (i <= r)
			len[i] = min(len[2 * mid - i], r - i + 1);//对称变换并且不能越过右界

		while (str[i - len[i]] == str[i + len[i]])
			++len[i];
		//尝试扩展.省略掉是否i的最右顶到右界->不必要
		//未检查越界，因为两端点、分隔符互不相同，必然停止。
		//i-len[i]是界外的第一个元素
			
		if (i + len[i] - 1 > r)//尽可能笼罩更大的范围，所以不使用>=
			r = i + len[i] - 1, mid = i;
		if (len[i] >= ans) {
			ans = len[i];//更新答案
		}
	}
	return ans - 1;
}