#include "grader.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1500;
int n;
vector<int> par, cnt;
vector<vector<int> > calc;

int find(int x) {
    if (x != par[x]) return par[x] = find(par[x]);
    return par[x];
}

void initialize(int _n) {
    n = _n;
    par.resize(n);
    cnt.resize(n);
    calc.resize(n);
    for (int i = 0; i < n; i++) {
        par[i] = i;
        cnt[i] = 1;
        calc[i].resize(n, 0);
    }
}

void merge(int u, int v, int pu, int pv) {
    par[pv] = pu;
    cnt[pu] += cnt[pv];
    for (int i = 0; i < n; i++) {
        calc[pu][i] += calc[pv][i];
        calc[i][pu] += calc[i][pv];
    }
}

int hasEdge(int u, int v) {
    int pu = find(u);
    int pv = find(v);
    int tot = cnt[pu] * cnt[pv];
    if (tot - calc[pu][pv] == 1) {
        if (cnt[pu] < cnt[pv]) {
            swap(pu, pv);
            swap(u, v);
        }
        merge(u, v, pu, pv);
        return 1;
    } else {
        calc[pu][pv]++;
        calc[pv][pu]++;
    }
    return 0;
}
