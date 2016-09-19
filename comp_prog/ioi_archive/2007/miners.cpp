#include <bits/stdc++.h>
using namespace std;

const int MAXN = (int)1e5 + 1;
const int oo = (int)1e5;

int n, f[2][13][13], cost[13][4], s_int[MAXN], next_state[13][4];
char s[MAXN];

int to_int(char c) {
    if (c == 'M') return 1;
    if (c == 'F') return 2;
    return 3;
}

void arr_reset(int idx) {
    for (int m1 = 0; m1 < 13; m1++) {
        for (int m2 = 0; m2 < 13; m2++) {
            f[idx][m1][m2] = -oo;
        }
    }
}

pair<int, int> calc(int mask, int c) {
    bool used[4];
    memset(used, 0, sizeof(used));

    int c1, c2;
    c1 = c2 = 0;
    if (mask <= 3) {
        c2 = mask;
    } else {
        c2 = mask % 3;
        c1 = mask / 3;
        if (c2 == 0) {
            c2 += 3;
            c1--;
        }
    }
    used[c1] = used[c2] = used[c] = 1;

    int cnt = 0;
    for (int i = 1; i <= 3; i++) {
        cnt += used[i];
    }
    return {cnt, c2 * 3 + c};
}

int main() {
    scanf("%d", &n);
    scanf("%s", s);
    for (int i = 0; i < n; i++) {
        s_int[i] = to_int(s[i]);
    }

    memset(cost, 0, sizeof(cost));
    for (int i = 0; i < 13; i++) {
        for (int j = 1; j <= 3; j++) {
            pair<int, int> next_res = calc(i, j);
            cost[i][j] = next_res.first;
            next_state[i][j] = next_res.second;
        }
    }

    int prev, next;
    prev = 0;
    arr_reset(prev);
    f[prev][0][0] = 0;
    
    for (int i = 0; i < n; i++) {
        next = 1 - prev;
        arr_reset(next);
        
        for (int m1 = 0; m1 < 13; m1++) {
            for (int m2 = 0; m2 < 13; m2++) {
                if (f[prev][m1][m2] < 0) continue;
                // put at m1
                int next_m = next_state[m1][s_int[i]];
                f[next][next_m][m2] = max(f[next][next_m][m2], f[prev][m1][m2] + cost[m1][s_int[i]]);

                // put at m2
                next_m = next_state[m2][s_int[i]];
                f[next][m1][next_m] = max(f[next][m1][next_m], f[prev][m1][m2] + cost[m2][s_int[i]]);
            }
        }
        prev = next;
    }
    int ans = 0;
    for (int m1 = 0; m1 < 13; m1++) {
        for (int m2 = 0; m2 < 13; m2++) {
            ans = max(ans, f[next][m1][m2]);
        }
    }
    printf("%d\n", ans);
    return 0;
}
