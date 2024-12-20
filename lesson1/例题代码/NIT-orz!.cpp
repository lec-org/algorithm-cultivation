#include <bits/stdc++.h>
using i64 = long long;

void solve () {
    int n, z;
    std::cin >> n >> z;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    int ans = *max_element(a.begin(), a.end());

    for (int i = 0; i < n; ++i) {
        ans = std::max(ans, (z | a[i]));
    }

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