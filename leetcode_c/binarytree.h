#pragma once

/*struct TreeNode {
  int val=0;
  TreeNode *l=0;
  TreeNode *r=0;
  TreeNode(int v):val(v),l(0),r(0) {}
};*/

// https://upload.wikimedia.org/wikipedia/commons/thumb/f/f7/Binary_tree.svg/192px-Binary_tree.svg.png

TreeNode* createTree1(){
  TreeNode *R = new TreeNode(2);
  R->left = new TreeNode(7);
  R->right = new TreeNode(5);
  R->right->right= new TreeNode(9);
  R->right->right->left = new TreeNode(4);

  R->left->left = new TreeNode(2);
  R->left->right = new TreeNode(6);
  R->left->right->left = new TreeNode(5);
  R->left->right->right = new TreeNode(11);
  return R;
}


