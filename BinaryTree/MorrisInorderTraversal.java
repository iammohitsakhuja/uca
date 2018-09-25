class Tree {
  static class TreeNode {
    int data;
    TreeNode left;
    TreeNode right;

    TreeNode(int data) {
      this(data, null, null);
    }

    TreeNode(int data, TreeNode left, TreeNode right) {
      this.data = data;
      this.left = left;
      this.right = right;
    }
  }

  TreeNode root;

  Tree() {
    this.root = null;
  }

  void morrisInorderTraversal() {
    TreeNode currNode = this.root;

    while (currNode != null) {
      // Go to the leftmost node of the current subtree.
      if (currNode.left == null) {
        System.out.println(currNode.data);
        currNode = currNode.right;
      } else {
        // prevNode represents the predecessor of the current node in the binary tree.
        TreeNode prevNode = currNode.left;
        while (prevNode.right != null && prevNode.right != currNode) prevNode = prevNode.right;

        // If this node has not been visited before, then link it to to the current node.
        if (prevNode.right == null) {
          prevNode.right = currNode;
          currNode = currNode.left;
        } else {
          // Otherwise, if this node has been visited before, then break its link.
          prevNode.right = null;
          System.out.println(currNode.data);
          currNode = currNode.right;
        }
      }
    }
  }
}

class MorrisInorderTraversal {
  public static void main(String[] args) {
    /* Constructed binary tree is
              1
            /   \
          2      3
        /  \
      4     5
    */

    Tree binaryTree = new Tree();
    binaryTree.root = new Tree.TreeNode(1);
    binaryTree.root.left = new Tree.TreeNode(2);
    binaryTree.root.right = new Tree.TreeNode(3);
    binaryTree.root.left.left = new Tree.TreeNode(4);
    binaryTree.root.left.right = new Tree.TreeNode(5);

    binaryTree.morrisInorderTraversal();
  }
}
