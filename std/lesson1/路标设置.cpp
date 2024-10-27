#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define PII pair<int, int>
#define PLL pair<LL, LL>
#define xx first
#define yy second
#define endl '\n'
const int N = 2e5 + 10;
int L, n, k;
int a[N];
bool check1(int x, int k){
    int t = 0;
    for(int i = 1;i < n;i++){
        if(a[i] - a[i - 1] > x)t += (a[i] - a[i - 1] - 1) / x;
    }
    if(k < t)return false;
    return true;
}

//显然，我们不需要等到最后再去return
//一种可行的优化是

bool check2(int x, int k){
    for(int i = 1;i < n;i++){
        if(a[i] - a[i - 1] > x)k -= (a[i] - a[i - 1] - 1) / x;
        if(k < 0)return false;
    }
    return true;
}

//及时结束循环可以避免一些可能的错误

void solve(){
    cin >> L >> n >> k;
    for(int i = 0;i < n;i++)cin >> a[i];
    int l = 1, r = L;
    while(l < r){
        int mid = l + r >> 1;
        if(check1(mid, k))r = mid;
        else l = mid + 1;
    }
    cout << l;
}
int main(){
    int T = 1;
//    cin >> T;
    while(T--){
        solve();
    }
}