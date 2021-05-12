/*
Given an integer array A of size N.

You have to perform two types of query, in each query you are given three integers x,y,z.

If x = 0, then update A[y] = z.
If x = 1, then output the minimum element in the array A between index y and z inclusive.
Queries are denoted by a 2-D array B of size M x 3 where B[i][0] denotes x, B[i][1] denotes y, B[i][2] denotes z.

*/

void build(int node, int s, int e, vector<int> &A, vector<int> &seg) {
    
    // base case
    if(s == e) {
        seg[node] = A[s];
        return;
    }
    
    int mid = (s + e) / 2;
    
    build(2*node, s, mid, A, seg);
    build(2*node+1, mid+1, e, A, seg);
    
    seg[node] = min(seg[2*node] , seg[2*node+1]);
}

int rangeQ(int node, int s, int e, int qs, int qe, vector<int> &seg) {
    
    // if node range completely lie outside query range
    if(e < qs or s > qe)
        return INT_MAX;
    
     // if node range completely lie inside query range
     if(qs <= s and e <= qe)
        return seg[node];
    
    // if node range and query range partially overlap
	// search in left and right children
	
	int mid = (s + e) / 2;
	
	int leftMin = rangeQ(2*node, s, mid, qs, qe, seg);
	int rightMin = rangeQ(2*node + 1, mid + 1, e, qs, qe, seg);
	
	return min(leftMin, rightMin);
}

void updateQ(int node, int s, int e, vector<int> &A, vector<int> &seg, int idxQ , int val) {
    
    // if query idx is completely outside the node range 
    if(idxQ < s or idxQ > e)
        return;
        
    // we reach the idxQ value update node value
    if(s == e) {
        A[idxQ] = val;
        seg[node] = val;
        return;
    }
    
    int mid = (s + e) / 2;
    
    if(idxQ > mid) {
        // move right child
        updateQ(2*node+1, mid+1, e, A, seg, idxQ , val);
    }
    else {
        // move left child
        updateQ(2*node, s, mid, A, seg, idxQ , val);
    }
    
    // update the parent node value 
    
    seg[node] = min(seg[2*node] , seg[2*node+1]);
}
vector<int> Solution::solve(vector<int> &A, vector<vector<int> > &B) {
    // given query range is 1 based
    
    int n = A.size();
    vector<int> seg(4*n);
    
    // build seg tree 1 based index in array
    // value passing seg-node index, (seg tree range)start, end, array A, Array seg tree 
    build(1, 0, n - 1, A, seg);
    
    // for(int i = 1; i < seg.size(); i++) {
    //     cout << i << " - " << seg[i] << endl;
    // }
    
    vector<int> ans;
    
    for(int i = 0; i < B.size(); i++) {
        int x = B[i][0];
        int y = B[i][1];
        int z = B[i][2];
        
        // update query
        if(x == 0) {
            // node index, start, end, A[], seg[], index of update, update value
            updateQ(1, 0, n - 1, A, seg, y - 1, z);
        }
        else {
            ans.push_back( rangeQ(1, 0, n - 1, y-1, z-1, seg) );
        }
    }
    return ans;
}
