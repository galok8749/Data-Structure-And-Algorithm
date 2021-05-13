/*

You are given an array A of numbers and an array B of size M X 3, having operations as follows.

If B[i][0] = 1, flip( multiply A[i] by -1) the value of A[i] where B[i][1] <= i <= B[i][2] .

If B[i][0] = 2, calculate the sum of the array in given range inclusive of both B[i][1] and B[i][2] .

Return an array of answers to the Type 2 queries.

*/

void build(int node, int s, int e, vector<int> &A, vector<int> &seg) {
	if(s == e) {
		seg[node] = A[s];
		return;
	}

	int mid = (s + e) / 2;
	
	build(2*node, s, mid, A, seg);
	build(2*node+1, mid+1, e, A, seg);

	seg[node] = (seg[2*node] + seg[2*node+1]);
}

int rangeSumQ(int node, int s, int e, int sq, int eq, vector<int> &seg, vector<int> &lazy) {
	
	// any pending update
	if(lazy[node] != 0) {
		seg[node] = -seg[node];

		if(s != e) {
			lazy[2*node] = 1 - lazy[2*node];
			lazy[2*node+1] = 1 - lazy[2*node+1] ;
		}

		lazy[node] = 0;
	}

	//  no overlap
	if(e < s or e < sq or s > eq)
		return 0;

	// complete overlap
	if(sq <= s and e <= eq)
		return seg[node];

	int mid = (s + e) / 2;

	int leftSum = rangeSumQ(2*node, s, mid, sq, eq, seg, lazy);
	int rightSum = rangeSumQ(2*node+1, mid+1, e, sq, eq, seg, lazy);

	return (leftSum + rightSum);
}

void rangeUpdateQ(int node, int s, int e, int sq, int eq, vector<int> &seg, vector<int> &lazy) {

	// any pending update
	if(lazy[node] != 0) {
		seg[node] = -seg[node];

		if(s != e) {
			lazy[2*node] = 1 - lazy[2*node];
			lazy[2*node+1] = 1 - lazy[2*node+1] ;
		}

		lazy[node] = 0;
	}

	//  no overlap
	if(s > e or e < sq or s > eq)
		return;

	// complete overlap
	if(sq <= s and e <= eq) {
		seg[node] = -seg[node];

		if(s != e) {
			lazy[2*node] = 1 - lazy[2*node];
			lazy[2*node+1] = 1 - lazy[2*node+1] ;
		}
		return;
	}
	
	int mid = (s + e) / 2;

	rangeUpdateQ(2*node, s, mid, sq, eq, seg, lazy);
	rangeUpdateQ(2*node+1, mid+1, e, sq, eq, seg, lazy);

	seg[node] = (seg[2*node] + seg[2*node+1]);
}


vector<int> Solution::solve(vector<int> &A, vector<vector<int> > &B) {
	int n = A.size();

	vector<int> seg(4*n);
	vector<int> lazy(4*n, 0);

	build(1, 0, n - 1, A, seg);
    vector<int> ans;
    
	for(int i = 0; i < B.size(); i++) {

		if(B[i][0] == 2) {
			int sq = B[i][1]-1;
			int eq = B[i][2]-1;

			ans.push_back(rangeSumQ(1, 0, n - 1, sq, eq, seg, lazy));

		}
		else {
			int sq = B[i][1]-1;
			int eq = B[i][2]-1;

			rangeUpdateQ(1, 0, n - 1, sq, eq, seg, lazy);
		}
	}
	
	return ans;
}