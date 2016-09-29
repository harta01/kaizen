#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstring>
using namespace std;

const int MAXN = 20010;
const int MAXM = 2001;
const int oo = (int)1e9;

int n, f[2][MAXM][MAXM];
pii p[MAXN];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &p[i].x, &p[i].y);
        p[i].y += 1000;
    }
    prev = 0;
    for (int i = 0; i <= 2000; i++) {
        for (int j = 0; j <= 2000; j++) {
            f[0][i][j] = i + j;
        }
    }
    for (int i = 1; i <= n; i++) {
        next = prev ^ 1;
        for (int j = 0; j <= 2000; j++) {
            for (int k = 0; k <= 2000; k++) {
                f[next][j][k] = oo;
            }
        }
        for (int j = 0; j <= 2000; j++) {
            f[next][j][p[i].y] = min(f[next][j][p[i].y], f[prev][][]);
        }
        prev = next;
    }
    return 0;
}
