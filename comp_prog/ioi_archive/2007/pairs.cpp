#include <bits/stdc++.h>
using namespace std;

const int MAXN = (int)1e5 + 10;
const int MAXB2 = 75000;
const int MAXB3 = 75;
typedef long long ll;

int B, N, D, M, curr, MAXZ;
vector<vector<int> > arr, t_arr;
ll res;
vector<int> tree2;
vector<vector<vector<int> > > tree3;

bool cf(vector<int> arr1, vector<int> arr2) {
    for (int i = 0; i < arr1.size(); i++) {
        if (arr1[i] != arr2[i]) return arr1[i] < arr2[i];
    }
    return 0;
}

void init() {
    if (B == 2) {
        MAXZ = MAXB2 * 2 + 1;
        tree2.resize(MAXZ);
    } else if (B == 3) {
        MAXZ = MAXB3 * 4 + 1;
        tree3.resize(MAXZ);
        for (int i = 0; i < MAXZ; i++) {
            tree3[i].resize(MAXZ);
            for (int j = 0; j < MAXZ; j++) {
                tree3[i][j].resize(MAXZ);
            }
        }
    }
}

void update(int idx, int val) {
    vector<int> tmp = t_arr[idx];
    if (B == 1) return;
    if (B == 2) {
        for (int i = tmp[1] + MAXB2; i < MAXZ; i += (i & -i)) {
            tree2[i] += val;
        }
    } else {
        for (int i = tmp[1] + MAXB3 * 2; i < MAXZ; i += (i & -i)) {
            for (int j = tmp[2] + MAXB3 * 2; j < MAXZ; j += (j & -j)) {
                for (int k = tmp[3] + MAXB3 * 2; k < MAXZ; k += (k & -k)) {
                    tree3[i][j][k] += val;
                }
            }
        }
    }
}

int query(int x) {
    int res = 0;
    for (int i = min(MAXZ - 1, x + MAXB2); i > 0; i -= (i & -i)) {
        res += tree2[i];
    }
    return res;
}

int query2(int x, int y, int z) {
    int res = 0;
    for (int i = min(MAXZ - 1, x + MAXB3 * 2); i > 0; i -= (i & -i)) {
        for (int j = min(MAXZ - 1, y + MAXB3 * 2); j > 0; j -= (j & -j)) {
            for (int k = min(MAXZ - 1, z + MAXB3 * 2); k > 0; k -= (k & -k)) {
                res += tree3[i][j][k];
            }
        }
    }
    return res;
}

int compute(int idx) {
    if (B == 1) return idx - curr;
    // -D .. D
    vector<int> tmp = t_arr[idx];
    int res = 0;
    int D2 = D + 1;
    if (B == 2) {
        res = query(tmp[1] + D) - query(tmp[1] - D2);
    } else {
        res = query2(tmp[1] + D, tmp[2] + D, tmp[3] + D);

        res -= query2(tmp[1] + D, tmp[2] + D, tmp[3] - D2);
        res -= query2(tmp[1] + D, tmp[2] - D2, tmp[3] + D);
        res -= query2(tmp[1] - D2, tmp[2] + D, tmp[3] + D);

        res += query2(tmp[1] + D, tmp[2] - D2, tmp[3] - D2);
        res += query2(tmp[1] - D2, tmp[2] + D, tmp[3] - D2);
        res += query2(tmp[1] - D2, tmp[2] - D2, tmp[3] + D);

        res -= query2(tmp[1] - D2, tmp[2] - D2, tmp[3] - D2);
    }
    return res;
}

int main() {
    scanf("%d%d%d%d", &B, &N, &D, &M);
    arr.resize(N);
    t_arr.resize(N);
    for (int i = 0; i < N; i++) {
        arr[i].resize(B);
        for (int j = 0; j < B; j++) {
            scanf("%d", &arr[i][j]);
        }

        if (B == 1) t_arr[i].push_back(arr[i][0]);
        else if (B == 2) {
            t_arr[i].push_back(arr[i][0] + arr[i][1]);
            t_arr[i].push_back(arr[i][0] - arr[i][1]);
        } else {
            t_arr[i].push_back(arr[i][0] + arr[i][1] + arr[i][2]);
            t_arr[i].push_back(arr[i][0] + arr[i][1] - arr[i][2]);
            t_arr[i].push_back(arr[i][0] - arr[i][1] + arr[i][2]);
            t_arr[i].push_back(arr[i][0] - arr[i][1] - arr[i][2]);
        }
    }

    sort(t_arr.begin(), t_arr.end(), cf);

    res = 0;
    curr = 0;
    init();
    for (int i = 0; i < N; i++) {
        while (curr < i && t_arr[i][0] > D + t_arr[curr][0]) {
            update(curr++, -1);
        }
        res += compute(i);
        update(i, 1);
    }
    printf("%lld\n", res);
    return 0;
}
