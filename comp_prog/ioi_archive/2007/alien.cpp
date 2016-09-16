#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct pii {
    int x, y;
    bool is_black;
    pii() {}
    pii(int _x, int _y) {
        x = _x;
        y = _y;
        is_black = false;
    }
    pii(int _x, int _y, bool _is_black) {
        x = _x; y = _y; is_black = _is_black;
    }
};

const int oo = (int)2e9 + 10;

int n, start_x, start_y, minX, minY, maxX, maxY;
int dirX[] = {-1, 1, 0, 0};
int dirY[] = { 0, 0,-1, 1};
char s[10];
pii point;

bool query_cell(ll x, ll y) {
    if (x < 1 || y < 1 || x > n || y > n) return false;
//    printf("examine %d %d\n", x, y);
//    fflush(stdout);
    cout << "examine " << x << ' ' << y << endl;
    scanf("%s", s);
    return s[0] == 't';
}

pii step_over(int x, int y, ll step, int dX, int dY) {
    ll nX = x + step * dX;
    ll nY = y + step * dY;
    return pii(nX, nY, query_cell(nX, nY));
}

pii trace(int x, int y, int dX, int dY) {
    ll step = 1;
    while (true) {
        pii res = step_over(x, y, step, dX, dY);
        if (res.is_black) {
            step = step * 2;
            x = res.x;
            y = res.y;
        }
        else {
            step = step / 2;
            break;
        }
    }
    for (ll i = step; i >= 1; i /= 2) {
        pii res = step_over(x, y, i, dX, dY);
        if (res.is_black) {
            x = res.x;
            y = res.y;
        }
    }
    return pii(x, y);
}

int main() {
    scanf("%d%d%d", &n, &start_x, &start_y);

    // scan 1 box to determine M
    maxX = -1; maxY = -1;
    minX = oo; minY = oo;
    for (int i = 0; i < 4; i++) {
        point = trace(start_x, start_y, dirX[i], dirY[i]);
        maxX = max(maxX, point.x);
        maxY = max(maxY, point.y);

        minX = min(minX, point.x);
        minY = min(minY, point.y);
    }
    int m = maxY - minY + 1;
    // printf("%d %d\n", minX, minY);
    // printf("%d %d\n", maxX, maxY);
    // printf("%d\n", m);

    // find center of smaller square
    int center_x, center_y;
    center_x = ((ll)maxX + minX) / 2;
    center_y = ((ll)maxY + minY) / 2;

    // printf("%d %d %d\n", center_x, center_y, m);

    // found the center, move to middle
    // check neighboring squares (horizontal only)
    bool is_black = true;
    while (is_black) {
        is_black = query_cell(center_x - 2 * m, center_y);
        if (is_black) {
            center_x = center_x - 2 * m;
        }
    }
    bool is_group_three = query_cell(center_x + 2LL * m, center_y) && query_cell(center_x + 4LL * m, center_y);
    if (is_group_three) {
        center_x = center_x + 2 * m;
    } else {
        center_x = center_x + m;
        center_y = center_y - m;
    }

    // check neighboring squares (vertical only)
    is_black = true;
    while (is_black) {
        is_black = query_cell(center_x, center_y - 2 * m);
        if (is_black) {
            center_y = center_y - 2 * m;
        }
    }
    center_y = center_y + 2 * m;

    cout << "solution " << center_x << ' ' << center_y << endl;
    return 0;
}
