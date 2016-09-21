#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1001;
#define pb push_back

int c, n, a, b;
bool m[MAXN][MAXN];

int f[2][MAXN][MAXN];

int prev(int x) {
    int res = x - 1;
    if (res < 1) res = c;
    return res;
}

int next(int x) {
    int res = x + 1;
    if (res > c) res = 1;
    return res;
}

int check(int type, int x, int y) {
    if (type == 0) {
        if (x == prev(y)) return f[type][x][y] = 1;
    } else {
        if (x == next(y)) return f[type][x][y] = 1;
    }
    if (f[type][x][y] != -1) return f[type][x][y];
    if (type == 0) {
        if (m[y][prev(y)] && check(type, x, prev(y))) {
            return f[type][x][y] = 1;
        }
        if (m[y][next(x)] && check(1 - type, y, next(x))) {
            return f[type][x][y] = 1;
        }
    } else {
        if (m[y][next(y)] && check(type, x, next(y))) {
            return f[type][x][y] = 1;
        }
        if (m[y][prev(x)] && check(1 - type, y, prev(x))) {
            return f[type][x][y] = 1;
        }

    }
    return f[type][x][y] = 0;
}

vector<int> compute(int type, int x, int y) {
    vector<int> res;
    while (1) {
        //cout << type << ' ' << x << ' ' << y << endl;
        res.pb(y);
        if (type == 0) {
            if (x == prev(y)) {
                return res;
            }
        } else {
            if (x == next(y)) {
                return res;
            }
        }
        if (type == 0) {
            if (m[y][prev(y)] && check(type, x, prev(y))) {
                y = prev(y);
                continue;
            }
            if (m[y][next(x)] && check(1 - type, y, next(x))) {
                type = 1 - type;
                int temp = x;
                x = y;
                y = next(temp);
                continue;
            }
        } else {
            if (m[y][next(y)] && check(type, x, next(y))) {
                y = next(y);
                continue;
            }
            if (m[y][prev(x)] && check(1 - type, y, prev(x))) {
                type = 1 - type;
                int temp = x;
                x = y;
                y = prev(temp);
                continue;
            }
        }

    }
    return res;
}

int main() {
    scanf("%d%d", &c, &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &a, &b);
        m[a][b] = m[b][a] = 1;
    }

    memset(f, -1, sizeof(f));
    for (int i = 1; i <= c; i++) {
        for (int j = 1; j <= c; j++) {
            if (m[i][j]) {
                if (check(0, i, j) && check(0, j, i)) {
                    vector<int> v1 = compute(0, i, j);
                    vector<int> v2 = compute(0, j, i);
//                    printf("V: %d %d\n", i, j);
                    for (int k = v1.size() - 1; k >= 0; k--) {
                        printf("%d\n", v1[k]);
                    }
//                    printf("\n");
                    for (int k = 0; k < v2.size(); k++) {
                        printf("%d\n", v2[k]);
                    }
                    return 0;
                }
            }
        }
    }
    printf("-1\n");
    return 0;
}
