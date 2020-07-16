#include <cstdio>
typedef long long ll;
const int maxn = 200003;
int read() {
    int x = 0, c = getchar();
    while (c < '0' && c > '9') c = getchar();
    while ('0' <= c && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
    return x;
}
int n = 0, m = 0;
int head[maxn], left[maxn], nxt[maxn], cnt = 0;
ll p[maxn], w[maxn];
void insert(int R, int L,int v) {
    nxt[++cnt] = head[R];
    head[R] = cnt;
    left[cnt] = L;
    p[cnt] = v;
}
ll ma[maxn<<2], lazy[maxn<<2];
inline ll max(ll a, ll b) { return a<b?b:a; }
inline void pushDown(int p) {
    ma[p << 1] += lazy[p];    
    ma[p << 1 | 1] += lazy[p];
    lazy[p << 1] += lazy[p];
    lazy[p << 1 | 1] += lazy[p];
    lazy[p] = 0;
}
inline void pushUp(int p) {
    ma[p] = max(ma[p<<1], ma[p<<1|1]);
}
void plus(int p,int L,int R,int l,int r, ll v) {
    if(l <= L && R <= r) {
        ma[p]+=v;
        lazy[p]+=v;
        return;
    }
    pushDown(p);
    int mid = (L+R)>>1;
    if(l <=mid) plus(p<<1,L,mid, l,r,v);
    if(r>mid) plus(p<<1|1,mid+1,R,l,r,v);
    pushUp(p);
}
int main() {
    n = read(); m = read();
    for (int i = 1;i<=n;++i) w[i] = read();
    int L = 0, R = 0, P = 0;
    for(int i=1;i<=m;++i) {
        L=read(); R=read(); P=read();
        insert(R,L,P);
    }
    ll ans = 0;
    for(int i = 1;i<=n;++i) {
        plus(1,1,n,i,i,ans);
        plus(1,1,n,1,i,-w[i]);
        for(int j = head[i];j;j=nxt[j]) {
            plus(1,1,n,1,left[j], p[j]);
        }
        ans = max(ans,ma[1]);
    }
    printf("%lld", ans);
    return 0;
}