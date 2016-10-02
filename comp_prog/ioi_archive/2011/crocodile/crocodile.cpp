#include "grader.h"
#include <bits/stdc++.h>
using namespace std;

#define pb push_back

struct pii {
	int x, y;

	pii() {}
	pii(int _x, int _y) {
		x = _x; y = _y;
	}
};

struct cf {
	bool operator()(const pii &X, const pii&Y)const {
		return X.y > Y.y;
	}
};

const int MAXN = (int)1e5;
const int oo = (int)1e9;

vector<pii> g[MAXN];
vector<pii> d[MAXN];

bool cf2(pii a, pii b) {
	return a.y < b.y;
}

int travel_plan(int N, int M, int R[][2], int L[], int K, int P[]) {
	for (int i = 0; i < M; i++) {
		g[R[i][0]].pb(pii(R[i][1], L[i]));
		g[R[i][1]].pb(pii(R[i][0], L[i]));
	}
	// initialize priority queue
	priority_queue<pii, vector<pii>, cf> pq;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 2; j++) {
			d[i].pb(pii(-1, oo));
		}
	}
	for (int i = 0; i < K; i++) {
		pq.push(pii(P[i], 0));

		d[P[i]][0].y = d[P[i]][1].y = 0;
	}

	while (!pq.empty()) {
		pii top = pq.top();
		pq.pop();

		if (top.y != d[top.x][1].y) continue;

		for (int i = 0; i < g[top.x].size(); i++) {
			pii next = g[top.x][i];
			bool visited = false;
			for (int j = 0; j < d[next.x].size(); j++) {
				if (d[next.x][j].x == top.x) { // if from same parent
					visited = true;
					break;
				}
			}
			if (visited) continue;
			d[next.x].pb(pii(top.x, next.y + d[top.x][1].y));
			sort(d[next.x].begin(), d[next.x].end(), cf2);
			d[next.x].pop_back();

			for (int j = 0; j < d[next.x].size(); j++) {
				if (d[next.x][j].x == top.x) {
					pq.push(pii(next.x, d[next.x][j].y));
				}
			}
		}
	}
	return d[0][1].y;
}
