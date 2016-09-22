#include "grader.h"
#include <bits/stdc++.h>
using namespace std;

struct pii {
    int state, position;
    pii() {}
    pii(int _state, int _position) {
        state = _state;
        position = _position;
    }
};

int check(int arr[], int N, int start, int end, int state, vector<int> v, bool used[]) {
    int arr2[N];
    for (int i = 0; i < v.size(); i++) v[i] = 1 - state;
    for (int i = start; i <= end; i++) {
        v[i] = state;
    }
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        if (used[i]) arr2[i] = arr[i];
        else arr2[i] = v[cnt++];
    }
    return tryCombination(arr2);
}

pii solve(int idx, int N, int arr[], bool used[]) {
    int arr2[N], reply, state;

    vector<int> v;
    v.resize(N - idx, 0);

    int cnt = 0, pos;
    for (int i = 0; i < N; i++) {
        if (used[i]) arr2[i] = arr[i];
        else arr2[i] = v[cnt++];
    }
    reply = tryCombination(arr2);
    if (reply != idx) {
        state = 0;
    } else state = 1;

    // probe the correct position to open gate-idx
    int lo = 0, hi = N - idx - 1;
    while (lo != hi) {
        int mid = (lo + hi) / 2;

        // reset arr
        reply = check(arr, N, lo, mid, state, v, used);
        if (reply != idx) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    cnt = 0, pos = 0;
    while (cnt < hi) {
        if (used[pos]) {
            pos++;
            continue;
        }
        pos++;
        cnt++;
    }
    while (used[pos]) pos++;
    return pii(state, pos);
}

void exploreCave(int N) {
    int arr[N], control[N];
    bool used[N];

    memset(arr, 0, sizeof(arr));
    memset(used, 0, sizeof(used));
    for (int i = 0; i < N; i++) {
        pii ans = solve(i, N, arr, used);
        arr[ans.position] = ans.state;
        control[ans.position] = i;
        used[ans.position] = true;
    }
    answer(arr, control);
}
