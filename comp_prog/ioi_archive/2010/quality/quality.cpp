#include "grader.h"
#include <bits/stdc++.h>
using namespace std;

int rectangle(int R, int C, int H, int W, int Q[3001][3001]) {
	auto acceptable = [R, C, H, W, Q](int median) {
		int sum[R][C];
		memset(sum, 0, sizeof(sum));

		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				sum[i][j] = (Q[i][j] > median) ? 1 : -1;
				if (i - 1 >= 0) sum[i][j] += sum[i - 1][j];
				if (j - 1 >= 0) sum[i][j] += sum[i][j - 1];
				if (i - 1 >= 0 && j - 1 >= 0) sum[i][j] -= sum[i - 1][j - 1];
			}
		}
		for (int startX = 0; startX < R - H + 1; startX++) {
			for (int startY = 0; startY < C - W + 1; startY++) {
				int endX = startX + H - 1;
				int endY = startY + W - 1;
				int tot = sum[endX][endY];
				if (startX - 1 >= 0) tot -= sum[startX - 1][endY];
				if (startY - 1 >= 0) tot -= sum[endX][startY - 1];
				if (startX - 1 >= 0 && startY - 1 >= 0) tot += sum[startX - 1][startY - 1];
				if (tot < 0) return true;
			}
		}
		return false;
	};

	int lo = 1, hi = R * C, mid, ans;
	while (lo <= hi) {
		mid = lo + (hi - lo) / 2;
		if (acceptable(mid)) {
			ans = mid;
			hi = mid - 1;
		} else lo = mid + 1;
	}
	return ans;
}
