#include <bits/stdc++.h>
using namespace std;

int seg[400005];
int lazy[400005];
int A[100005];

// lazy propagation : whatever node we passing the pending update should be done

void construct(int node, int s, int e) {
	//  we reach leaf node that represent the array element
	if(s == e) {
		seg[node] = A[s];
		return;
	}

	int mid = (s + e) / 2;

	construct(2*node, s, mid);
	construct(2*node + 1, mid + 1, e);

	seg[node] = max(seg[2*node], seg[2*node + 1]);
}

int rangeQ(int node, int s, int e, int sq, int eq) {

	if(lazy[node] != 0) {
		// complete the pending update
		seg[node] +=lazy[node];

		if(s != e) {
			// set the lazy value for children
			lazy[2*node] +=lazy[node];
			lazy[2*node+1] +=lazy[node];
		}
		lazy[node] = 0;
	}

	// if node range completely lie outside query range
	if(s > e or e < sq or s > eq)
		return INT_MIN;

	// if node range completely lie inside query range
	if(sq <= s and e <= eq) {
		return seg[node];
	}

	int mid = (s + e) / 2;

	int leftMax = rangeQ(2*node, s, mid, sq, eq);
	int rightMax = rangeQ(2*node + 1, mid + 1, e, sq, eq);

	return max(leftMax, rightMax);
}

void updateQ(int node, int s, int e, int sq, int eq, int val) {

	if(lazy[node] != 0) {
		// complete the pending update
		seg[node] +=lazy[node];
		if(s != e) {
			lazy[2*node] +=val;
			lazy[2*node+1] +=val;
		}
		lazy[node] = 0;
	}

	// if node range completely lie outside query range
	if(s > e or e < sq or s > eq)
		return;

	// if node range completely lie inside query range
	if(sq <= s and e <= eq) {
		// add val to current node
		seg[node] +=val;

		// if current node is not leaf node
		if(s != e) {
			// set the lazy value for children

			lazy[2*node] += val;
		    lazy[2*node + 1] += val;
		}
		return;
	}

	int mid = (s + e) / 2;

	updateQ(2*node, s, mid, sq, eq, val);
	updateQ(2*node+1, mid + 1, e, sq, eq, val);
	
	seg[node] = max(seg[2*node], seg[2*node + 1]);
}

int main() {

	int n;
	cin >> n;

	for(int i = 0; i < n; i++)
		cin >> A[i];

	memset(lazy, 0, sizeof(lazy));
	memset(seg, 0, sizeof(seg));

	// seg tree index start from 1 we pass start node of seg tree and range of array 
	construct(1, 0, n - 1);

	// for(int i = 1; i <= 4*n; i++) {
	// 	cout << seg[i] << " ";
	// }
	// cout << endl;

	updateQ(1, 0, n - 1, 3, 5, 4);
	// sq and eq are ranges of query
	cout << rangeQ(1, 0, n - 1, 2, 5) << endl;

	

}

