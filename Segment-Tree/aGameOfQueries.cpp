/*
You are given an array A of numbers, which is circular and an array B of size M X 3, having operations as follows.

If B[i][0] is not equal to 2, increase all numbers in the segment [ B[i][1], B[i][2] ] by B[i][0] .

If B[i][0] = 2, calculate the minimum of the array in given range inclusive of both B[i][1] and B[i][2] .

Return an array of answers to the Type 2 queries.

Assuming circular segments, if we consider 5 elements and the segment [3, 1], we refer to index sequence [3, 4, 0, 1].
*/

void build(int node, int s, int e, vector<int> &A, vector<int> &seg) {
	if(s == e) {
		seg[node] = A[s];
		return;
	}

	int mid = (s + e) / 2;
	
	build(2*node, s, mid, A, seg);
	build(2*node+1, mid+1, e, A, seg);

	seg[node] = min(seg[2*node], seg[2*node+1]);
}

int rangeMinQ(int node, int s, int e, int sq, int eq, vector<int> &seg, vector<int> &lazy) {
	
	// any pending update
	if(lazy[node] != 0) {
		seg[node] +=lazy[node];

		if(s != e) {
			lazy[2*node] += lazy[node];
			lazy[2*node+1] += lazy[node];
		}

		lazy[node] = 0;
	}

	//  no overlap
	if(e < s or e < sq or s > eq)
		return INT_MAX;

	// complete overlap
	if(sq <= s and e <= eq)
		return seg[node];

	int mid = (s + e) / 2;

	int leftMin = rangeMinQ(2*node, s, mid, sq, eq, seg, lazy);
	int rightMin = rangeMinQ(2*node+1, mid+1, e, sq, eq, seg, lazy);

	return min(leftMin, rightMin);
}

void rangeUpdateQ(int node, int s, int e, int sq, int eq, int val, vector<int> &seg, vector<int> &lazy) {

	// any pending update
	if(lazy[node] != 0) {
		seg[node] +=lazy[node];

		if(s != e) {
			lazy[2*node] += lazy[node];
			lazy[2*node+1] += lazy[node];
		}

		lazy[node] = 0;
	}

	//  no overlap
	if(s > e or e < sq or s > eq)
		return;

	// complete overlap
	if(sq <= s and e <= eq) {
		seg[node] +=val;

		if(s != e) {
			lazy[2*node] += val;
			lazy[2*node+1] += val;
		}
		return;
	}
	
	int mid = (s + e) / 2;

	rangeUpdateQ(2*node, s, mid, sq, eq, val, seg, lazy);
	rangeUpdateQ(2*node+1, mid+1, e, sq, eq, val, seg, lazy);

	seg[node] = min(seg[2*node], seg[2*node+1]);
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

			if(sq <= eq) {
				ans.push_back(rangeMinQ(1, 0, n - 1, sq, eq, seg, lazy));
			}
			else { // circular query
				int x = rangeMinQ(1, 0, n - 1, sq, n-1, seg, lazy);
				int y = rangeMinQ(1, 0, n - 1, 0, eq, seg, lazy);
				ans.push_back(min(x, y));
			}
		}
		else {
			int val = B[i][0];
			int sq = B[i][1]-1;
			int eq = B[i][2]-1;

			if(sq <= eq) {
				rangeUpdateQ(1, 0, n - 1, sq, eq, val, seg, lazy);
			}
			else { // circular query
				rangeUpdateQ(1, 0, n - 1, sq, n-1, val, seg, lazy);
				rangeUpdateQ(1, 0, n - 1, 0, eq, val, seg, lazy);
			}
		}
	}
	
	return ans;
}