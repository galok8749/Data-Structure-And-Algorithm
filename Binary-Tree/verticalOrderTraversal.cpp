/*
Given a binary tree, return a 2-D array with vertical order traversal of it. Go through the example and image for more details.
NOTE: If 2 Tree Nodes shares the same vertical level then the one with lesser depth will come first.

 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
vector<vector<int> > Solution::verticalOrderTraversal(TreeNode* A) {
    if(A == NULL)
        return {};
    vector<vector<int> > ans;
    unordered_map<int, vector<int> > mp;
    
    queue<pair<TreeNode*, int> > Q;
    Q.push({A, 0});
    
    int l = 0, r = 0;
    
    while(!Q.empty()) {
        auto fnt = Q.front(); Q.pop();
        TreeNode *root = fnt.first;
        l = min(l, fnt.second);
        r = max(r, fnt.second);
        
        mp[fnt.second].push_back(root->val);
        
        if(root->left) Q.push({root->left, fnt.second - 1});
        if(root->right) Q.push({root->right, fnt.second + 1});
    }
    
    while(l<=r) {
        ans.push_back(mp[l]);
        ++l;
    }
    
    return ans;
}
