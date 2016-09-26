#include <bits/stdc++.h>
using namespace std;

const int MAXN = 801;

struct pii {
    int x, y, z;
    pii() {}
    pii(int _x, int _y) {
        x = _x; y = _y;
    }
    pii(int _x, int _y, int _z) {
        x = _x; y = _y; z = _z;
    }
};

int dx[] = {-1, 1, 0, 0};
int dy[] = { 0, 0,-1, 1};

int n, s;
char mp[MAXN][MAXN];
int mp2[MAXN][MAXN];
bool visited[MAXN][MAXN];
pii start;

bool valid(int x, int y) {
    return x >= 0 && y >= 0 && x < n && y < n && mp[x][y] != 'T';
}

bool can_pass(int t) {
    if (t == -1) return true;
    queue<pii> q;
    memset(mp2, -1, sizeof(mp2));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mp[i][j] == 'H') {
                mp2[i][j] = 0;
                q.push(pii(i, j, 0));
            }
        }
    }
    while (!q.empty()) {
        pii front = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = front.x + dx[i];
            int ny = front.y + dy[i];
            if (valid(nx, ny)) {
                if (mp2[nx][ny] != -1) continue;
                if (mp[nx][ny] == 'D') continue;
                mp2[nx][ny] = max(front.z - t + 1, 0);
                q.push(pii(nx, ny, front.z + 1));
            }
        }
    }
    if (mp2[start.x][start.y] == 0) return false;
    memset(visited, false, sizeof(visited));
    visited[start.x][start.y] = true;
    // check if Mecho can reach Mecho's home, D
    q.push(pii(start.x, start.y, 0));
    while (!q.empty()) {
        pii front = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = front.x + dx[i];
            int ny = front.y + dy[i];
            if (valid(nx, ny)) {
                if (mp[nx][ny] == 'D') return true;
                if (visited[nx][ny]) continue;
                if ((front.z + 1) < mp2[nx][ny] * s) {
                    visited[nx][ny] = true;
                    q.push(pii(nx, ny, front.z + 1));
                }
            }
        }
    }
    return false;
}

int main() {
    scanf("%d%d", &n, &s);
    for (int i = 0; i < n; i++) {
        scanf("%s", mp[i]);
        for (int j = 0; j < n; j++) {
            if (mp[i][j] == 'M') {
                start = pii(i, j);
            }
        }
    }
    int lo = 0, hi = n * n, mid, ans = -1;
    while (lo <= hi) {
        mid = (lo + hi) / 2;
        if (can_pass(mid)) {
            ans = mid;
            lo = mid + 1;
        } else hi = mid - 1;
    }
    printf("%d\n", ans);
    return 0;
}
