/*
https://leetcode.com/problems/combination-sum-ii/
*/

class Solution {
public:
    
    void allSubsetSum(int idx, int sum, vector<int> &candidates, vector<vector<int>> &ans, vector<int> &temp) {
        if(sum < 0)
            return;

        if(sum == 0) {
            ans.push_back(temp);
            return;
        }

        for(int i = idx; i < candidates.size(); i++) {
            if(i > idx and candidates[i] == candidates[i-1]) continue;

            temp.push_back(candidates[i]);
            allSubsetSum(i+1, sum - candidates[i], candidates, ans, temp);
            temp.pop_back();
        }
}

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());

        vector<vector<int>> ans;
        vector<int> temp;

        allSubsetSum(0, target, candidates, ans, temp);

        return ans;
    }
};