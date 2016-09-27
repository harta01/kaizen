#include "grader.h"
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = (int)1e5 + 10;

bool possible(int ans, int R, int X[], ll B) {
    if (ans == 0) return true;
    int left = 0, right = ans - 1, mid = left + (ans - 1) / 2;
    ll cost_l = 0, cost_r = 0;
    for (int i = left; i < mid; i++) {
        cost_l += X[mid] - X[i];
    }
    for (int i = mid + 1; i <= right; i++) {
        cost_r += X[i] - X[mid];
    }
    if (cost_l + cost_r <= B) return true;
    while (right + 1 < R) {
        cost_l -= X[mid] - X[left];
        cost_l += (X[mid + 1] - X[mid]) * (mid - left);

        cost_r -= (X[mid + 1] - X[mid]) * (right - mid);
        cost_l += (X[right + 1] - X[mid + 1]);

        if (cost_l + cost_r <= B) return true;
        left++; right++; mid++;
    }
    return false;
}

int besthub(int R, int L, int X[], ll B) {
    int lo = 0, hi = R, mid, ans;
    while (lo <= hi) {
        mid = (lo + hi) / 2;
        if (possible(mid, R, X, B)) {
            ans = mid;
            lo = mid + 1;
        } else hi = mid - 1;
    }
    return ans;
}
