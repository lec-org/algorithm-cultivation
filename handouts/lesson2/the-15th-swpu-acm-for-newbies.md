[比赛链接（非公开）](https://ac.nowcoder.com/acm/contest/72175)
# H - 找0
## 题意
给定整数 $a, b$ 满足 $0\leq a, b\leq 10^4$，求 $a\times b$ 的结尾 $0$ 的个数。

## 题解
直接模拟就可以，注意 $a\times b = 0$ 时特判
*题面锅了导致卡了好久还吃了四发罚时（，出题人还我一血*
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll a, b;
ll ans;

int main()
{ 
    cin >> a >> b;

    a *= b;

    if(a == 0)
    {
        cout << 1;
        return 0;
    }
    
    while(a % 10 == 0 && a)
    {
        ++ans;
        a = a / 10;
    }
    cout << ans;   
    return 0;
}
```

# I - 找0_pro
## 题意
相比 H 题只修改了数据范围为 $1 \leq a, b\leq 10^{14}$。
## 题解
### 解法1

注意到 $1\leq a\times b \leq 10^28$，直接使用 `__int128` 或高精度就可以。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 lll;
lll a, b;
ll ans;

lll rd()
{
	lll res = 0;
	char ch = getchar();
	while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)) res = res * 10 + ch - '0', ch = getchar();
	return res;
}

signed main()
{  
	a = rd(), b = rd();
	a = a * b; 
	if(a == 0)
	{
		printf("1");
		return 0;
	}
	while(a && a % 10 == 0)
	{
		++ans;
		a /= 10;
	}
	printf("%lld", ans);
	return 0;
}
```

### 解法2
考虑乘法过程，能够产生 $0$ 的组合只有 $2\times 5 = 10$，因此我们可以统计 $a, b$ 中 $2, 5$ 因子的个数，较少的一个即为答案。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll a, b;
ll cnt2, cnt5;

int main()
{
    cin >> a >> b;
    if(a == 0 || b == 0)
    {
        cout << 1;
        return 0;
    }
    while(a % 2 == 0 && a) ++cnt2, a /= 2;
    while(a % 5 == 0 && a) ++cnt5, a /= 5;
    while(b % 2 == 0 && b) ++cnt2, b /= 2;
    while(b % 5 == 0 && b) ++cnt5, b /= 5;
    cout << min(cnt2, cnt5);
    return 0;
}
```

# B - 作文批改
## 题意
给出 $n$ 个单词构成若干个句子。要求：
- 每个句子以 `.` 结尾
- 每个句子的第一个单词首字母大写，其余单词除 “I” 外均小写
- “I（我）” 在任何位置都要大写
输出不满足要求的字母个数。
## 题解
根据题意大力模拟。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;

int n;
string s;
int flag = 0;
int ans = 0;

signed main()
{  
    cin >> n;
    
	for(int i = 1; i <= n; ++i)
	{
		cin >> s;
		if(flag == 0)
		{
			flag = 1;
			if(s.size() == 1 && s[0] == 'i') ++ans;
			else if('a' <= s[0] && s[0] <= 'z') ++ans;
			for(int j = 1; j < s.size(); ++j)
			{
				if('A' <= s[j] && s[j] <= 'Z') ++ans;
				if(s[j] == '.') flag = 0;
			}
		}
		else
		{
			if(s.size() == 1 && s[0] == 'i') 
			{
				++ans;
			}
			else
			{
				for(int j = 0; j < s.size(); ++j)
				{
					if('A' <= s[j] && s[j] <= 'Z')
					{
						++ans;
					}
					if(s[j] == '.') flag = 0;
				}	
			}

		}
	}

	cout << ans;

	return 0;
}
```

# J - 黎明神剑
## 题意
给定 $n \times m(1\leq n, m\leq 500)$ 大小的由 `*`、`#`、`?` 组成的棋盘，求最大的只含 `#` 和 `?` 连通块面积，并使得代价最小，其中 `#` 的代价为 $1$，`?`的代价为 $2$。

## 题解
遍历整个棋盘，从未访问过的 `#` 或 `?` 开始跑 dfs，更新答案。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e2 + 10;

int n, m;
int g[MAXN][MAXN];
int ans1, ans2;

int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0}};
bool legal(int x, int y)
{
	if(g[x][y] == 0) return false;
	if(x < 1 || x > n || y < 1 || y > m) return false;
	return true;
}

void dfs(int x, int y, int &res1, int &res2)
{
	if(!legal(x, y)) return;
	++res1;
	res2 += g[x][y];
	g[x][y] = 0;
	
	for(int i = 0; i < 4; ++i)
	{
		int nx = x + dir[i][0], ny = y + dir[i][1];
		dfs(nx, ny, res1, res2);
	}
}

signed main()
{
  	cin >> n >> m;
  	for(int i = 1; i <= n; ++i)
  	{
  		char ch = getchar();
  		for(int j = 1; j <= m; ++j)
  		{
  			ch = getchar();
  			if(ch == '*') g[i][j] = 0;
  			else if(ch == '#') g[i][j] = 1;
  			else g[i][j] = 2;
		}
	}
	
    int res1 = 0, res2 = 0;
	for(int i = 1; i <= n; ++i)
	{
		for(int j = 1; j <= m; ++j)
		{
            res1 = res2 = 0;
			if(g[i][j]) dfs(i, j, res1, res2);
			if(res1 > ans1 || (res1 == ans1 && res2 < ans2)) ans1 = res1, ans2 = res2;
		}
	}
	
	cout << ans1 << ' ' << ans2;
	
    return 0;
}
```

# C - 找找acm
## 题意
给出长度为 $N$ 的字符串和 $Q$ 个询问，每次询问 $[l, r]$ 中有多少个字串为 `acm`
## 题解
先遍历一遍字符串，在 `acm` 子串的 `m` 位置处记录加一，预处理出前缀和。
对于每个询问，由于 `acm` 长度为 $3$，因此答案应该为 `sum[r] - sum[l + 1]` 而不是一般前缀和的 `sum[r] - sum[l - 1]`
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int MAXN = 1e6 + 10;

int n, m;
string s;
int sum[MAXN];

signed main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    cin >> s;
    
    for(int i = 0; i + 2 < s.size(); ++i)
    {
        if(s.substr(i, 3) == "acm") ++sum[i + 2];
    }
    
    for(int i = 2; i < n; ++i) sum[i] += sum[i - 1];
    
    while(m--)
    {
        int l, r;
        cin >> l >> r;
        cout << sum[r] - sum[l + 1] << '\n';
    }
    return 0;
}
```

# K - 重构代码
## 题意
没人读得懂题意。

## 题解
根据样例说明倒推。将 ${a_n}$ 从小到大排序后，相邻两项做差，删去前 $m - 1$ 大的差值剩下求和就是答案。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
typedef pair<int, int> pii;
const int INF = 0x3f3f3f3f;
const int MAXN = 2e5 + 10;

int x, n, m, a[MAXN];

priority_queue<int, vector<int>, less<int> > q;
int vis[MAXN];
int ans;

signed main()
{  
	ios::sync_with_stdio(false);
	cin >> x >> n >> m;
	for(int i = 1; i <= n; ++i)
	{
		cin >> a[i];
	}
	sort(a + 1, a + 1 + n);
    
    for(int i = 1; i < n; ++i)
    {
        q.push(a[i + 1] - a[i]);
    }
    --m;
    while(!q.empty() && m--)
    {
        q.pop();
    }
    
    while(!q.empty())
    {
        ans += q.top();
        q.pop();
    }
    
	cout << ans;
	return 0;
}
```

# M - 养生的大学生
## 题意
给出 $n$ 杯初始质量为 $1$ 的茶，相同质量可以合并为一杯（质量累加）。求合并到最终杯数小于等于 $m$ 还需要多少杯质量为 $1$ 的茶。

## 题解
每次合并后茶的质量是 $2$ 的幂，所以 $n$ 的二进制中 $1$ 的个数就是合并后茶的杯数，对应的 $2$ 的幂就是这杯茶的质量。
每次取最低位 $1$ 作为添加的茶的质量，然后在该位加一，直到 $1$ 的个数小于等于 $m$。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
typedef pair<int, int> pii;
const int INF = 0x3f3f3f3f;
const int MAXN = 2e5 + 10;

int n, m, ans;

signed main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    
    cin >> n >> m;
    
    while(__builtin_popcount(n) > m)
    {
        ans += n & (-n);
        n += n & (-n);
    }
    cout << ans;
	return 0;
}
```

# F - 两点距离
## 题意
给出 $N$ 个点，定义两点之间距离为 $min\{|x_i - x_j|, |y_i - y_j|\}$ ，求两个不同点之间的最大距离。
## 题解
二分距离，难点在如何 `check`。
先将点按 $x$ 排序，固定一个点，枚举其余满足 $|x_i - x_j| \geq mid$ 的点，判断 $|y_i - y_j|$ 的最大值是否也大于等于 $mid$。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAXN = 2e5 + 10;

int n;
struct point
{
    int x, y;
}p[MAXN];

bool check(int mid)
{
    int mmin = INF, mmax = -114514;
    for(int i = 1, j = 1; i <= n; ++i)
    {
        while(j < i && p[i].x - p[j].x >= mid)
        {
            mmin = min(mmin, p[j].y);
            mmax = max(mmax, p[j].y);
            ++j;
        }
        if(p[i].y - mmin >= mid || mmax - p[i].y >= mid) return true;
    }
    return false;
}

void fast_io() {ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);}
signed main()
{
    fast_io();
    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> p[i].x >> p[i].y;
    
    sort(p + 1, p + 1 + n, [](point a, point b){return a.x < b.x;});
    
    int l = 0, r = 1e9, mid;
    while(l < r)
    {
        mid = (l + r + 1) >> 1;
        if(check(mid)) l = mid;
        else r = mid - 1;
    }
    
    cout << l;
    return 0;
}
```

# A - 数一数三角形
## 题意
给定一个正 $N$ 边形，每条边上有 $A_i$ 个特殊点。以特殊点作为顶点构造三角形，每个点只能使用一次，每个三角形互不相交，求能构造出的三角形的最大数量。
## 题解
考虑最终情况，将三角形构造完后，要么剩下的点不够构造出三角形，要么剩下的点共线于特殊点最多的边上。
两种情况答案分别为 $\dfrac{\sum_{i=1}^n A_i}{3}$ 和 $\sum_{i=1}^n A_i - \max_{i=1}^n A_i$，两者取最小即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5 + 10;

int n, a[MAXN], sum, mmax;

void fast_io() {ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);}
signed main()
{
    fast_io();
    cin >> n;
    for(int i = 1; i <= n; ++i)
    {
        cin >> a[i];
        sum += a[i];
        mmax = max(mmax, a[i]);
    }
    cout << min(sum / 3, sum - mmax);
    return 0;
}
```

# E - 简单DP
## 题意
向盒子中加入或者删去一个写有整数 $x$ 的球，每次操作后输出取盒子中一些球组合成 $k$ 的方案数。
## 题解
每次操作后对当前球跑一次背包就可以。
转移方程为 $dp[i] = dp[i] \pm dp[i - x]$，注意枚举背包容量的顺序。
```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 5e3 + 10;
const int MOD = 998244353;

int q, k;
int dp[MAXN];

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> q >> k;
    dp[0] = 1;
    while(q--)
    {
        char op; int x;
        cin >> op >> x;
        if(op == '+')
        {
            for(int i = k; i >= x; --i)
                dp[i] = (dp[i] + dp[i - x]) % MOD;
        }
        else
        {
            for(int i = x; i <= k; ++i)
                dp[i] = (dp[i] - dp[i - x] + MOD) % MOD;
        }
        cout << dp[k] << '\n';
    }
}
```

# D - 字符串相约
## 题意
给定只由 $0$ 和 $1$ 组成的两个长度相等的字符串，以 $0$ 开头，以 $1$ 结尾。可以执行如下操作任意次：
- 如果 $s_l = s_r$，则 $s_i = s_l (i \in [l,r])$
询问若干次操作后能否使得两个字符串相等。
## 题解
注意到字符串首尾一定分别为 $0$ 和 $1$，如果最后两个字符串可以相等，则一定形如 `000011111`。判断两字符串是否在相同位置拥有 `01` 字串即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e3 + 11;

int t;
string a, b;
int ans;

void fast_io() {ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);}
signed main()
{
    fast_io();
    cin >> t;
    while(t--)
    {
        ans = 0;
        cin >> a >> b;
        for(int i = 0; i < a.size() - 1; ++i)
        {
            if(a[i] == b[i] && a[i] == '0' && a[i + 1] == b[i + 1] && a[i + 1] == '1')
            {
                ans = 1;
                break;
            }
        }
        cout << (ans ? "YES\n" : "NO\n");
    }
    return 0;
}
```

# L - 概率机器人
## 题意
给定 $n\times m$ 的网格，每个单元格有一个价值，走到某一单元格可以获得当前单元格价值。从某一单元格向下走和向右走分别有一个概率。求从 $(1,1)$ 出发到网格边界能获得价值的期望。
## 题解
每个单元格都可以向下或向右走，dfs 的复杂度为 $O(2^{nm})$，一定会超时。注意到某一单元格的答案一定只能从下方单元格和右方单元格转移过来，所以 dp 倒序遍历，复杂度为 $O(nm)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3 + 10;

int n, m, v[MAXN][MAXN], p[MAXN][MAXN];
double ans;

double dp[MAXN][MAXN];

void fast_io() {ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);}
signed main()
{
    fast_io();
    cin >> n >> m;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
            cin >> v[i][j];

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
            cin >> p[i][j];

    for(int i = n; i >= 1; --i)
    {
        for(int j = m; j >= 1; --j)
        {
            dp[i][j] += v[i][j] + dp[i + 1][j] * p[i][j] * 1.0 / 100 + dp[i][j + 1] * (100 - p[i][j]) * 1.0 / 100;
        }
    }

    cout << floor(dp[1][1] + 0.5);
    return 0;
}
```

# G - 每日一颗?
## 题意
给出数列 ${a_n}$，可以进行至多 $k$ 次操作，每次操作可以对其中任意一个元素加一或者减一。求若干次操作后数列中最长的公差为 $114514$ 的等差数列（下标连续）的长度
## 题解
最重要的一步转化是 $a_i = a_i - 114514\times i$，原来的等差数列问题转化为每个数相等的问题。
可以证明到相等的基准选择中位数时需要进行的操作数是最小的，类似于货仓选址问题。
每次枚举起点向后扩展长度，用平衡树维护当前中位数。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int MAXN = 2e5 + 10;
const int DIF = 114514;

int n, k, a[MAXN];

int val[MAXN], rnd[MAXN], son[MAXN][2], sz[MAXN];
int root, tot;

void clear(int p)
{
    val[p] = rnd[p] = son[p][0] = son[p][1] = sz[p] = 0;
}

void push_up(int p)
{
    sz[p] = sz[son[p][0]] + sz[son[p][1]] + 1;
}

int merge(int u, int v)
{
    if(!u || !v) return u | v;

    if(rnd[u] > rnd[v])
    {
        son[v][0] = merge(u, son[v][0]);
        push_up(v);
        return v;
    }
    else
    {
        son[u][1] = merge(son[u][1], v);
        push_up(u);
        return u;
    }
}

void split_val(int p, int k, int &x, int &y)
{
    if(!p) x = y = 0;
    else
    {
        if(val[p] <= k)
        {
            x = p;
            split_val(son[p][1], k, son[p][1], y);
        }
        else
        {
            y = p;
            split_val(son[p][0], k, x, son[p][0]);
        }
        push_up(p);
    }
}

void split_rnk(int p, int k, int &x, int &y)
{
    if(!p) x = y = 0;
    else
    {
        if(sz[son[p][0]] < k)
        {
            x = p;
            split_rnk(son[p][1], k - sz[son[p][0]] - 1, son[p][1], y);
        }
        else
        {
            y = p;
            split_rnk(son[p][0], k, x, son[p][0]);
        }
        push_up(p);
    }
}

void insert(int x)
{
    int u = ++tot, a, b;
    rnd[u] = rand();
    val[u] = x;
    sz[u] = 1;
    split_val(root, x, a, b);
    root = merge(merge(a, u), b);
}

void remove(int x)
{
    int a, b, c, d;
    split_val(root, x - 1, a, b);
    split_rnk(b, 1, c, d);
    clear(c);
    root = merge(a, d);
}

int query_val(int &p, int k)
{
    int a, b, c, d, res;
    split_rnk(p, k - 1, a, b);
    split_rnk(b, 1, c, d);
    res = val[c];
    p = merge(a, merge(c, d));
    return res;
}

int ans;

void fast_io() {ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);}
signed main()
{
    srand(0721);
    fast_io();
    cin >> n >> k;
    for(int i = 1; i <= n; ++i)
    {
        cin >> a[i];
        a[i] -= i * DIF;
    }
    
    for(int i = 1, j = i; i <= n && j <= n; ++i)
    {
        while(j <= n)
        {
            insert(a[j]);
            int len = j - i + 1;
            int x = query_val(root, (len + 1) / 2);
            int res = 0;
            for(int l = i; l <= j; ++l)
            {
                res += abs(x - a[l]);
            }
            if(res <= k) ans = max(ans, len), ++j;
            else
            {
                while(sz[root] > 0) remove(query_val(root, 1));
                break;
            }
        }
    }
    cout << ans;
}
```