#include <bits/stdc++.h>
using namespace std;

const int MAXN = (int)3e6 + 10;

int n, m, cnt[52], res;
char s1[MAXN], s2[MAXN];

int to_int(char c) {
    if (c >= 'a' && c <= 'z') return c - 'a';
    return c - 'A' + 26;
}

int main() {
    // for (char c = 'a'; c <= 'z'; c++) printf("%c %d\n", c, to_int(c));
    // for (char c = 'A'; c <= 'Z'; c++) printf("%c %d\n", c, to_int(c));
    scanf("%d%d", &n, &m);
    scanf("%s", s1);
    scanf("%s", s2);

    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++) {
        cnt[to_int(s1[i])]--;
        cnt[to_int(s2[i])]++;
    }
    bool found = true;
    res = 0;
    for (int i = 0; i < 52; i++) {
        if (cnt[i]) {
            found = false;
            break;
        }
    }
    if (found) res++;
    for (int i = n; i < m; i++) {
        cnt[to_int(s2[i - n])]--;
        cnt[to_int(s2[i])]++;

        found = true;
        for (int j = 0; j < 52; j++) {
            if (cnt[j]) {
                found = false;
                break;
            }
        }
        if (found) res++;
    }
    printf("%d\n", res);
    return 0;
}
