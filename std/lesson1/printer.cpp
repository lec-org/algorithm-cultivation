#include <bits/stdc++.h>
using i64 = long long;

void solve () {
    int n, k;
    std::cin >> n >> k;

    std::vector<i64> t(n), l(n), w(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> t[i] >> l[i] >> w[i];
    }

    auto check = [&](i64 mid) -> bool {
        i64 res = 0;
        for (int i = 0; i < n; ++i) {
            i64 tt = mid;
            i64 now = tt / (t[i] * l[i] + w[i]) * l[i];
            tt = std::min(tt % (t[i] * l[i] + w[i]), t[i] * l[i]);
            now += tt / t[i];
            res += now;

            if (res >= k) return true;
        }

        return res >= k;
    };

    i64 L = 0, R = 2e18;
    while (L < R) {
        i64 mid = (L + R) / 2;
        if (check(mid)) R = mid;
        else L = mid + 1;
    }

    std::cout << L << "\n";
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