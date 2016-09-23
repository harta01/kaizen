#include <bits/stdc++.h>
using namespace std;

const int MAXN = 101;
const int MAXM = 2001;
int n, m, r[MAXN], w[MAXM], q, loc[MAXM];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &r[i]);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d", &w[i]);
    }
    priority_queue<int, vector<int>, greater<int> > pq;
    for (int i = 1; i <= n; i++) pq.push(i);
    int ans = 0;
    queue<int> pending;
    for (int i = 0; i < 2 * m; i++) {
        scanf("%d", &q);
        if (q < 0) {
            pq.push(loc[-q]);
            if (pending.size()) {
                q = pending.front();
                loc[q] = pq.top();
                ans += r[loc[q]] * w[q];
                pending.pop();
                pq.pop();
            }
        } else {
            if (pq.size() == 0) {
                pending.push(q);
                continue;
            }
            loc[q] = pq.top();
            ans += r[loc[q]] * w[q];
            pq.pop();
        }
    }
    printf("%d\n", ans);
    return 0;
}
