//
// Created by root on 7/30/17.
//

#ifndef LEETCODE_C_652_FIND_DUPLICATE_SUBTREES_H
#define LEETCODE_C_652_FIND_DUPLICATE_SUBTREES_H

#include <henry.h>
#include "binarytree.h"

namespace _652{
  TreeNode* constructTreeNode(){
    TreeNode* R=new TreeNode(0);
    int k=3;
    TreeNode* c=R;
    while(k--)
      c->right = new TreeNode(0), c=c->right;
    k=2, c=R;
    while(k--)
      c->left = new TreeNode(0), c=c->left;
    return R;
  }

  struct Solution {
    unordered_map<string, int> m;
    vector<TreeNode*> r;
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* R) {
      dfs(R, 0);
      return r;
    }
    string dfs(TreeNode* n, int level){
      if (!n) return "x";
      string s = dfs(n->left, level+1);
      s += "," + to_string(n->val);
      s += "," + dfs(n->right, level+1)+""; // inorder OK!
      //string s = dfs(n->right) + ","+to_string(n->val) +"," + dfs(n->left)+"-"; // reverse-inorder OK!
      //string s = to_string(n->val) +"," + dfs(n->left) + ","+ dfs(n->right);  // preorder OK
      //string s = dfs(n->right) + ","+ dfs(n->left) + "," + to_string(n->val); // reverse-preorder OK
      //string s = dfs(n->left) + ","+ dfs(n->right) + "," + to_string(n->val); // postorder OK
      //string s =  to_string(n->val)+ ","+dfs(n->right) + ","+ dfs(n->left);   // reverse-postorder OK
      //cout << "level " << level << ": "<< s << endl;
      if (m[s]++ == 1) r.push_back(n);
      return s;
    }
  };

  void test(){
    Solution sln;
    TreeNode* R=constructTreeNode();
    sln.findDuplicateSubtrees(R);
  }

}


#endif //LEETCODE_C_652_FIND_DUPLICATE_SUBTREES_H
