import java.io.*;
import java.math.*;
import java.text.*;
import java.util.*;
import java.util.regex.*;

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

  void insert(int data) {
    TreeNode newNode = new TreeNode(data);

    if (this.root == null) {
      this.root = newNode;
      return;
    }

    TreeNode currNode = this.root;
    while (currNode.left != null || currNode.right != null) {
      if (data <= currNode.data) {
        if (currNode.left != null) currNode = currNode.left;
        else break;
      } else {
        if (currNode.right != null) currNode = currNode.right;
        else break;
      }
    }

    if (data <= currNode.data) currNode.left = newNode;
    else currNode.right = newNode;
  }

  LinkedList<TreeNode> getPreOrderTraversal() {
    LinkedList<TreeNode> preOrderTraversal = new LinkedList<>();

    Stack<TreeNode> stack = new Stack<>();

    TreeNode currNode = this.root;

    while (!stack.isEmpty() || currNode != null) {
      while (currNode != null) {
        if (currNode.right != null) stack.push(currNode.right);

        preOrderTraversal.add(currNode);
        currNode = currNode.left;
      }

      if (stack.isEmpty()) break;

      currNode = stack.pop();
    }

    return preOrderTraversal;
  }
}

public class ValidBST {
  public static void main(String args[]) throws Exception {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    Scanner scanner = new Scanner(System.in);

    // Get the number of queries to be performed.
    int numQueries = scanner.nextInt();

    while (numQueries-- > 0) {
      // Get the number of nodes in the current query.
      int numNodes = scanner.nextInt();

      // Get the pre order traversal for the current query.
      int[] givenPreOrder = new int[numNodes];
      for (int i = 0; i < numNodes; i++) givenPreOrder[i] = scanner.nextInt();

      // Insert these elements into the tree.
      Tree tree = new Tree();
      for (int i = 0; i < givenPreOrder.length; i++) tree.insert(givenPreOrder[i]);

      LinkedList<Tree.TreeNode> preOrderTraversal = tree.getPreOrderTraversal();

      boolean isValidBST = true;
      for (int i = 0; i < givenPreOrder.length && !preOrderTraversal.isEmpty(); i++) {
        if (givenPreOrder[i] != preOrderTraversal.pollFirst().data) {
          isValidBST = false;
          break;
        }
      }

      if (isValidBST) System.out.println("YES");
      else System.out.println("NO");
    }
  }
}
