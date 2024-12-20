#include <bits/stdc++.h>
using i64 = long long;

void solve () {
    int a, b, c;
    std::cin >> a >> b >> c;

    std::cout << (a ^ b ^ c) << "\n";
}

int main () {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int Task = 1;
    std::cin >> Task;
    while (Task--) {
        solve();
    }

    return 0;
}