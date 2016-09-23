#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2010;

struct pii {
    int x, y, z;
    pii() {};
    pii(int _x, int _y, int _z) {
        x = _x; y = _y; z = _z;
    }
    bool operator<(const pii &X)const {
        return x > X.x || x == X.x && y > X.y || x == X.x && y == X.y && z < X.z;
    }
};

int N, T, P, arr[MAXN][MAXN], score[MAXN];
pii p[MAXN];

int main() {
    scanf("%d%d%d", &N, &T, &P);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= T; j++) {
            scanf("%d", &arr[i][j]);
            if (arr[i][j] == 0) score[j]++;
        }
    }
    for (int i = 1; i <= N; i++) {
        int tot = 0, cnt = 0;
        for (int j = 1; j <= T; j++) {
            tot += score[j] * arr[i][j];
            cnt += arr[i][j];
        }
        p[i] = pii(tot, cnt, i);
    }
    sort(p + 1, p + 1 + N);
    for (int i = 1; i <= N; i++) {
        if (p[i].z == P) {
            printf("%d %d\n", p[i].x, i);
        }
    }
    return 0;
}
