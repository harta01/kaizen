#include <bits/stdc++.h>
using namespace std;

const int MAXN = 51;
const int oo = (int)1e9;
int n, m, dp[MAXN][MAXN], f[MAXN][MAXN][MAXN][MAXN];

int query(int x1, int y1, int x2, int y2) {
    return dp[x2][y2] - dp[x2][y1 - 1] - dp[x1 - 1][y2] + dp[x1 - 1][y1 - 1];
}

int best(int x1, int y1, int x2, int y2) {
    if (x1 == x2 && y1 == y2) return 0;
    int tot = query(x1, y1, x2, y2);
    if (f[x1][y1][x2][y2] != -1) return f[x1][y1][x2][y2];
    int res = oo;
    for (int i = x1; i < x2; i++) {
        res = min(res, best(x1, y1, i, y2) + best(i + 1, y1, x2, y2));
    }
    for (int i = y1; i < y2; i++) {
        res = min(res, best(x1, y1, x2, i) + best(x1, i + 1, x2, y2));
    }
    return f[x1][y1][x2][y2] = res + tot;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &dp[i][j]);
            dp[i][j] = dp[i][j] + dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1];
        }
    }
    memset(f, -1, sizeof(f));
    printf("%d\n", best(1, 1, n, m));
    return 0;
}
