# lesson 1

## 学习方法
对于没有计划参加算法竞赛的同学， acwing 算法基础课对企业笔试面试匹配得很好，可以直接参考学习。
笔试之前到 leetcode 上刷题，基本可以满足需求。

对于有计划参加算法竞赛的同学，我觉得 acwing 算法基础课的安排是稍显不合理的。
我个人推荐的入门学习顺序是：
+ 贪心
+ 二分查找、二分答案、三分
+ dfs、bfs 和 简单剪枝
+ 栈、队列、二叉堆、并查集
+ 线性 dp、背包 dp、区间 dp
+ 位运算、整除理论、组合计数
+ 图论基础、拓扑排序、最短路、最小生成树
+ ST 表、最近公共祖先
+ DAG 上 dp、树形 dp、状压 dp
+ 单调栈和单调队列
+ 树状数组和线段树
+ 字符串哈希、kmp 和 trie 树

关于学习方式，可以到 [洛谷](https://www.luogu.com.cn/) 找以【模板】开头的题目题解学习，然后做官方和用户分享的题单中的简单题。
这部分一定不要花太多时间，争取在大一下学期之前结束。

系统学习完上面的内容后，就可以开始到 [CodeForces](https://codeforces.com/) 上刷题了。可以在 problemset 中筛选题目难度，从 rating 1200 开始一道一道做。
遇到不会的科技就根据题解中提到的关键字去找模板题学习。如果有时间也可以打打这上面的比赛，作为自己阶段学习成果的证明。

[AtCoder](https://atcoder.jp/) 上的 Atcoder Beginner Contest 是很好的锻炼自己算法模板和常见套路的地方。这里面题通常比较简单，属于是学过了就肯定能做出来。

对高级科技有需求的，到 [OIwiki](https://oi-wiki.org/) 目录里面找不会的学。比如主席树、平衡树、网络流等。在 XCPC 中一般不作为铜牌题及以下的点考察。

学习过程中可以整理一个自己的算法模板库，[引流](https://github.com/nephrenn233/Templates-in-Competitive-Programming)，因为 XCPC 是开卷考试。

推荐阅读：[ACM 怎么样零基础到入门？ - geruome的回答 - 知乎](https://www.zhihu.com/question/26823471/answer/2423361138)

## 时间复杂度
衡量算法快慢的函数。大 $O$ 记号表示上界。规定计算机进行一次基本运算（加减乘除模、swap、比较等）所用时间为一个小常数。

+ 冒泡、选择排序：$O(n^2)$
+ 快速、归并排序：$O(n\log n)$

假设一个算法消耗时间的函数为
$$
\begin{equation}
    T(n) = \left\{
    \begin{aligned}
    1 &\qquad (n = 1) \\
    T\left(\dfrac{n}{2}\right) + 2n &\qquad (n > 1)
    \end{aligned}
    \right.
\end{equation}
$$

展开可得 $T(n) = n + 2n \log_2 n$ .

忽略掉常数项和低阶项，用大 O 记号表示为 $O(n\log n)$ .

+ $O(n)$
```cpp
for (int i = 1; i <= n; ++i) {
    x += 1;
}
```
+ $O(n^2)$
```cpp
for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
        x += 1;
    }
}
```
+ $O(n^3)$
```cpp
string s[n + 1], t[n + 1];
// s[i], t[i] 长度 <= n
for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
        if (s[i] == t[j]) ++cnt;
    }
}
```
+ $O(\sqrt{n})$
```cpp
for (int i = 2; i * i <= n; ++i) {
    if (n % i == 0) break;
}
```
+ $O(n\log n)$
```cpp
for (int i = 1; i <= n; ++i) {
    for (int j = 1; j * i <= n; ++j) {
        x += 1;
    }
    // 调和级数
}
```

## 二分答案
前期学习中的一个**重难点**

使用二分答案要满足两个条件：
+ 答案满足单调性
+ 容易验证一个解是否是满足题意的。
+ 及时return `check` 函数有时会避免一些可能的错误
+ 考虑边界问题



[P3853 [TJOI2007\] 路标设置 - 洛谷 | 计算机科学教育新生态](https://www.luogu.com.cn/problem/P3853)

[数字组合](https://ac.nowcoder.com/acm/problem/235260)

## 位运算

例题选讲
1. [NIT orz!](https://codeforces.com/problemset/problem/1696/A)
2. [Odd One Out](https://codeforces.com/problemset/problem/1915/A)
3. [XOR Sequences](https://codeforces.com/problemset/problem/1979/B)
4. [XOR Mixup](https://codeforces.com/problemset/problem/1698/A)
