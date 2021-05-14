/*
problem link

https://leetcode.com/problems/subsets/
*/

class Solution {
public:
    void printAllSubset(int idx, vector<int> &temp, vector<int> &nums, vector<vector<int> > &ans) {        
        // one of the subset
        ans.push_back(temp);
        
        for(int i = idx; i < nums.size(); i+=1) {
            // take element now all subset will start with nums[i]
            temp.push_back(nums[i]);
            printAllSubset(i + 1, temp, nums, ans);
            
            // do not take element
            temp.pop_back();
        }
    }
    
    vector<vector<int>> subsets(vector<int>& nums) {
        
        vector<vector<int>> ans;
        vector<int> temp;
        
        printAllSubset(0, temp, nums, ans);
        
        return ans;
    }
};