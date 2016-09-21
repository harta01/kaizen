#include "molecules.h"
#include <bits/stdc++.h>
using namespace std;

struct pii {
    int x, y;
    pii() {}
    pii(int _x, int _y) {
        x = _x; y = _y;
    }
    bool operator <(const pii &X) const {
        return x < X.x;
    }
};
typedef long long ll;
const int MAXN = (int)2e5 + 10;
pii p[MAXN];

vector<int> find_subset(int l, int u, vector<int> w) {
    int n = w.size();
    for (int i = 0; i < n; i++) {
        p[i] = pii(w[i], i);
    }
    
    sort(p, p + n);

    int curr = 0;
    ll tot = 0;
    vector<int> arr;
    for (int i = 0; i < n; i++) {
        tot += p[i].x;
        while (tot > u) {
            tot -= p[curr].x;
            curr++;
        }
        if (tot >= l && tot <= u) {
            for (int j = curr; j <= i; j++) {
                arr.push_back(p[j].y);
            }
            return arr;
        }
    }
    return arr;
}
