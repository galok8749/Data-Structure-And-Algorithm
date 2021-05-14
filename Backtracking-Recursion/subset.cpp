/*
problem link

https://leetcode.com/problems/subsets/

The subset problem is all about choice, whether you want certain element inside the vector or not. 
For example, [1, 2, 3], starting with pos = 0. At pos = 0, you push 1 into temp, then recursively call the function. 
Then this reclusive call is a "crossroad". 
Inside the call (with all other calls inside), you have the "1" chosen and every vector you produce will begin with 1. 
When the call returns (ie. you pop 1 out), you are on the other road of the crossroad, which does not contain 1. 
These are just the first "choice" you are faced. And after that you face with other similar choices.

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