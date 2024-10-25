#include <bits/stdc++.h>
using i64 = long long;

void solve () {
    int x, y;
    std::cin >> x >> y;
    int ans = x ^ y;
    ans = ans & (-ans);
    std::cout << ans << "\n";
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