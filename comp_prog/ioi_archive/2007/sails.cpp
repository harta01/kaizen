#include <bits/stdc++.h>
using namespace std;

struct pii {
    int x, y;
    pii() {}
    bool operator<(const pii &X)const {
        return x < X.x || x == X.x && y < X.y;
    }
};

typedef long long ll;
const int MAXN = 100010;

int n, arr[MAXN];
pii p[MAXN];
ll tot;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &p[i].x, &p[i].y);
    }
    sort(p, p + n);
    
    for (int i = 0; i < n; i++) {
        int counter = p[i].y;
        for (int j = p[i].x - 1; counter > 0; j--) {
            arr[j]++;
            counter--;
        }
        for (int j = 1; j < p[i].x; j++) {
            int idx = j;
            while (idx && arr[idx] > arr[idx - 1]) {
                swap(arr[idx], arr[idx - 1]);
                idx--;
            }
        }
        /*printf("%d: %d %d\n", i, p[i].x, p[i].y);
        for (int j = 0; j < 5; j++) printf("%d\n", arr[j]);
        printf("\n");*/
    }
    tot = 0;
    for (int i = 0; i < p[n - 1].x; i++) {
        tot += (ll)arr[i] * (ll)(arr[i] - 1) / 2LL;
    }
    cout << tot << endl;
    return 0;
}
