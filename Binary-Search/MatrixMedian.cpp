/*

Given a matrix of integers A of size N x M in which each row is sorted.

Find and return the overall median of the matrix A.

NOTE: No extra memory is allowed.

NOTE: Rows are numbered from top to bottom and columns are numbered from left to right.

Problem Constraints
1 <= N, M <= 10^5

1 <= N*M <= 10^6

1 <= A[i] <= 10^9

N*M is odd

*/

int Solution::findMedian(vector<vector<int> > &A) {
    int row = A.size();
    int col = A[0].size();
    
    // median can be any element so , search space is 1 to INT_MAX
    
    int lo = 1, hi = INT_MAX;
    int n = (row * col) / 2;
    
    int ans;
    
    while(lo <= hi) {
        int cnt = 0;
        
        int mid = (lo + hi) / 2;
        for(int i = 0; i < A.size(); i++) {
            // element less or equal to mid
            int ele = upper_bound(A[i].begin(), A[i].end(), mid) - A[i].begin();
            cnt +=ele;
        }
        
        // median is at (n/2+1)th element
        if(cnt >= (n  + 1)) { // valid part so update and look for better ans
            ans = mid;
            hi = mid - 1;
        }
        else { // invalid part so move to valid part
            lo = mid + 1;
        }
        
        // cout << mid << " " << cnt << " " << ans << endl; 
    }
    
    return ans;
}
