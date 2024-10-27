//直接枚举 n^4 显然超时
//枚举前三纬，二分最后一维 n^3 + logn 超时
//这里需要进一步优化
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define PII pair<int, int>
#define PLL pair<LL, LL>
#define xx first
#define yy second
#define endl '\n'
const int N = 1010;
int a[N], b[N], c[N], d[N];
LL ab[N * N], cd [N * N];
void solve(){
    int n, abn = 0, cdn = 0;
    cin >> n;
    for(int i = 0;i < n;i++)cin >> a[i] >> b[i] >> c[i] >> d[i];
    for(int i = 0;i < n;i++) {
        for (int j = 0; j < n; j++) {
            ab[abn++] = a[i] + b[j];
            cd[cdn++] = c[i] + d[j];
        }
    }
    LL cnt = 0;
    sort(cd, cd + cdn);
    for(int i = 0;i < abn;i++){
        int L, R, l = 0, r = cdn - 1;
        while(l < r){
            int mid = l + r >> 1;
            if(cd[mid] >= -ab[i])r = mid;
            else l = mid + 1;
        }
        L = l, l = 0, r = cdn - 1;
        while(l < r){
            int mid = l + r >> 1;
            if(cd[mid] > -ab[i])r = mid;
            else l = mid + 1;
        }
        R = r;
        cnt += R - L;
    }
    cout << cnt;
}
int main(){
    int T = 1;
//    cin >> T;
    while(T--){
        solve();
    }
}
//需要提醒的是，此代码是有问题的
//剩余工作留给各位