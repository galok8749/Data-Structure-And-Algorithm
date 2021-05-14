/*
https://leetcode.com/problems/combination-sum/
*/

class Solution {
public:
    
    void allCombinationSum(int start, int target, vector<int> &candidates, vector<int> &temp, vector<vector<int>> &ans) {
        if(target < 0)
            return;
        
        if(target == 0) {
            ans.push_back(temp);
        }
        
        for(int i = start; i < candidates.size(); i++) {
            temp.push_back(candidates[i]);
            allCombinationSum(i, target - candidates[i], candidates, temp, ans);
            temp.pop_back();
        }
        
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        
        vector<vector<int>> ans;
        vector<int> temp;
        
        allCombinationSum(0, target, candidates, temp, ans);
        
        return ans;
    }
};