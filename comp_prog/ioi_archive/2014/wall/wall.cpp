#include "grader.h"
#include <bits/stdc++.h>
using namespace std;



void insert(int node, int type, int left, int right, int h) {
    if (left == right) {
    }
    insert(node * 2, type, left, mid, h);
    insert(node * 2 + 1, type, mid + 1, right, h);
}

void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[]) {
    for (int i = 0; i < k; i++) {
        insert(1, op[i], left[i], right[i], height[i]);
    }
    for (int i = 0; i < n; i++) {
        finalHeight[i] = query(i, i);
    }
    return;
}
