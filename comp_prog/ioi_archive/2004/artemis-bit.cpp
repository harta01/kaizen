#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <set>
using namespace std;

const int MAXN = 20001;
const int MAXW = 64001;

struct pii {
    int x, y, z;
    pii() {}

    bool operator<(const pii&X)const {
        return x < X.x || (x == X.x && y < X.y);
    }
};

int N, T, ans, ansX, ansY;
int tree[MAXN], mp[MAXW];
pii p[MAXN];

void update(int h, int v) {
    for (int i = h; i < MAXN; i += (i & -i)) {
        tree[i] += v;
    }
}

int query(int h) {
    int res = 0;
    for (int i = h; i >= 1; i -= (i & -i)) {
        res += tree[i];
    }
    return res;
}

int main() {
    scanf("%d%d", &N, &T);
    set<int> sy;
    for (int i = 1; i <= N; i++) {
        scanf("%d%d", &p[i].x, &p[i].y);
        sy.insert(p[i].y);
        p[i].z = i;
    }
    int cnt = 1;
    for (set<int>::iterator it=sy.begin(); it!=sy.end(); it++) {
        mp[*it] = cnt++;
    }
    for (int i = 1; i <= N; i++) {
        p[i].y = mp[p[i].y];
    }
    sort(p, p + N);
    ans = N + 1;
    memset(tree, 0, sizeof(tree));
    for (int i = 1; i <= N - T + 1; i++) {
        if (i == 1) {
            update(p[i].y, 1);
            for (int j = i + 1; j < T; j++) {
                update(p[j].y, 1);
            }
        }
        for (int j = i + T - 1; j <= N; j++) {
            update(p[j].y, 1);
            int maxi = max(p[i].y, p[j].y);
            int mini = min(p[i].y, p[j].y);
            int sum = query(maxi) - query(mini - 1);
            if (sum >= T && sum < ans) {
                ans = sum;
                ansX = p[i].z;
                ansY = p[j].z;
            }
        }
        for (int j = i + T; j <= N; j++) {
            update(p[j].y, -1);
        }
        update(p[i].y, -1);
    }
    printf("%d %d\n", ansX, ansY);
    return 0;
}
