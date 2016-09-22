#include "grader.h"
#include <bits/stdc++.h>
using namespace std;

struct pii {
    int x, y;
    pii() {}
    pii(int _x, int _y) {
        x = _x; y = _y;
    }
    bool operator<(const pii &X) const {
        return x < X.x || (x == X.x && y < X.y);
    }
};

struct cf {
    bool operator()(const pii &X, const pii &Y) const {
        return X.y < Y.y;
    }
};

const int MAXT = (int)1e6 + 10;

pii toy[MAXT];

bool compare_size(pii X, pii Y) {
    return X.y < Y.y;
}

bool can_solve(int capacity, int A, int B, int T, int X[], int Y[], int W[], int S[]) {
    for (int i = 0; i < T; i++) {
        toy[i] = pii(W[i], S[i]);
    }

    sort(toy, toy + T);
    priority_queue<pii, vector<pii>, cf> pq;

    int idx = 0;
    for (int i = 0; i < A; i++) {
        // capture those toys that can be consumed by X[i]
        while (idx < T && toy[idx].x < X[i]) {
            pq.push(toy[idx++]);
        }
        // pop the largest size possible as this is the most optimal way for robots of type Y to handle
        // the smaller toys remaining the better
        for (int j = 0; j < capacity && !pq.empty(); j++) {
            pq.pop();
        }
    }
    while (idx < T) pq.push(toy[idx++]);

    vector<pii> remaining_toys;
    while (!pq.empty()) {
        remaining_toys.push_back(pq.top());
        pq.pop();
    }
    sort(remaining_toys.begin(), remaining_toys.end(), compare_size);

    idx = 0;
    for (int i = 0; i < B; i++) {
        int used = 0;
        while (idx < remaining_toys.size() && remaining_toys[idx].y < Y[i] && used < capacity) {
            idx++;
            used++;
        }
    }
    return idx == remaining_toys.size();
}

int putaway(int A, int B, int T, int X[], int Y[], int W[], int S[]) {
    sort(X, X + A);
    sort(Y, Y + B);

    int ans = -1, lo = 1, hi = T, mid;
    while (lo <= hi) {
        mid = (lo + hi) / 2;
        if (can_solve(mid, A, B, T, X, Y, W, S)) {
            ans = mid;
            hi = mid - 1;
        } else lo = mid + 1;
    }
    return ans;
}
