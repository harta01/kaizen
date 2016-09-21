#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1001;
const int oo = (int)1e9;

struct pii {
    int x, y;
    pii() {}
    pii(int _x, int _y) {
        x = _x; y = _y;
    }
};

int n, m, a, b, c, d, dp[MAXN][MAXN], lg2[MAXN], max_val = 0, temp[MAXN][MAXN];
int rmq[MAXN][MAXN][10];
pii inner, outer;

void build_log_table(int size) {
    for (int i = 1; i < size; i++) lg2[i] = log2(i);
}

void input() {
    scanf("%d%d%d%d%d%d", &m, &n, &a, &b, &c, &d);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &dp[i][j]);
            dp[i][j] = dp[i][j] + dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1];
        }
    }
}

// calculate total value of rectangle (s_x, s_y), (e_x, e_y) 
int calc(int s_x, int s_y, int e_x, int e_y) {
    return dp[e_x][e_y] - dp[e_x][s_y - 1] - dp[s_x - 1][e_y] + dp[s_x - 1][s_y - 1];
}

// query the min value given range
int query(int row, int c1, int c2) {
    int diff = lg2[c2 - c1 + 1];
    return min(rmq[row][c1][diff], rmq[row][c2 - (1 << diff) + 1][diff]);
}

int main() {
    build_log_table(MAXN);

    input();

    // rmq[i][j][k] computes the best rectangle of size d x c with upper left coordinate
    // starting at (i, j) .. (i, j + 2^k - 1)
    for (int i = 1; i <= n - d + 1; i++) {
        for (int j = 1; j <= m - c + 1; j++) {
            rmq[i][j][0] = calc(i, j, i + d - 1, j + c - 1);
        }
        for (int k = 1; k < 10; k++) {
            for (int j = 1; j + (1 << k) - 1 <= m - c + 1; j++) {
                rmq[i][j][k] = min(rmq[i][j][k - 1], rmq[i][j + (1 << (k - 1))][k - 1]);
            }
        }
    }

    for (int s_col = 2; s_col <= m - a + 2; s_col++) {
        int e_col = s_col + (a - 2) - 1;
        for (int s_row = 2; s_row <= n - d; s_row++) {
            temp[s_col][s_row] = query(s_row, s_col, e_col - c + 1);
        }
    }
    // rmq[s_col][s_row][k] computes the best rectangle of size d x c with upper left coordinate
    // starting at (s_row, s_col) .. (s_row + 2^k - 1, s_col + a - c - 2)
    for (int s_col = 2; s_col <= m - a + 2; s_col++) {
        int e_col = s_col + (a - 2) - 1;
        for (int s_row = 2; s_row <= n - d; s_row++) {
            rmq[s_col][s_row][0] = temp[s_col][s_row];
        }
        for (int k = 1; k < 10; k++) {
            for (int s_row = 2; s_row + (1 << k) - 1 <= n - d; s_row++) {
                rmq[s_col][s_row][k] = min(rmq[s_col][s_row][k - 1], rmq[s_col][s_row + (1 << (k - 1))][k - 1]);
            }
        }
    }

    // find the best pyramid
    for (int i = 1; i <= n - b + 1; i++) {
        int s_x = i, e_x = i + b - 1;

        for (int j = 1; j <= m - a + 1; j++) {
            int s_y = j, e_y = j + a - 1;

            int tot = calc(s_x, s_y, e_x, e_y) - query(s_y + 1, s_x + 1, e_x - d);
            if (tot > max_val) {
                max_val = tot;
                outer = pii(i, j);
            }
        }
    }

    // find inner rectangle upper left coordinate
    int min_val = oo;
    for (int s_row = outer.x + 1; s_row <= outer.x + b - 1 - d; s_row++) {
        for (int s_col = outer.y + 1; s_col <= outer.y + a - 1 - c; s_col++) {
            int tot = calc(s_row, s_col, s_row + d - 1, s_col + c - 1);
            if (tot < min_val) {
                min_val = tot;
                inner = pii(s_row, s_col);
            }
        }
    }
    printf("%d %d\n", outer.y, outer.x);
    printf("%d %d\n", inner.y, inner.x);
    return 0;
}
