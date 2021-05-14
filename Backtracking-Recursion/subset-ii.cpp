// https://leetcode.com/problems/subsets-ii/

// Eliminate the dup with sort and then the condition: 
// 1- do not put this element inside, if it has same element before && the former dup has not been put into it. 
// Because otherwise, you better off put the former dup into the vector instead of this (latter dup) one.

class Solution {
public:
    void allUniqueSubset(int idx, vector<int> &temp, vector<int> &nums, vector<vector<int>> &ans) {
        ans.push_back(temp);
        
        for(int i = idx; i < nums.size(); i++) {
            if(i > idx and nums[i] == nums[i - 1]) continue;
            
            temp.push_back(nums[i]);
            allUniqueSubset(i + 1, temp, nums, ans);
            temp.pop_back();
        }
    }
    
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        
        sort(nums.begin(), nums.end());
        
        vector<vector<int>> ans;
        vector<int> temp;
        
        allUniqueSubset(0, temp, nums, ans);
        
        return ans;
    }
};
