package com.uca.ds.trees;

import java.util.LinkedList;
import java.util.NoSuchElementException;
import java.util.Queue;

public class RedBlackTree<Key extends Comparable<Key>, Value> {

  private static final boolean RED = false;
  private static final boolean BLACK = true;
  private Node root;

  public RedBlackTree() {
    this.root = null;
  }

  public void add(Key key, Value value) throws IllegalArgumentException {
    if (key == null) throw new IllegalArgumentException("Key is null");

    // TODO: Add the case where if value is null, then the element with that key is deleted.

    // Simply do a BST insert into the tree.
    Node newNode = this.bstInsert(key, value);

    // Fix any RBTree property violations after insertion.
    this.fixAfterInsertion(newNode);

    assert this.check();
  }

  private Node bstInsert(Key key, Value value) {
    // Create a new node.
    Node newNode = new Node(key, value);

    // If the tree is empty.
    if (this.isEmpty()) {
      this.root = newNode;
      return newNode;
    }

    Node currNode = this.root; // To keep track of the current node.
    Node parentNode = currNode.parent; // To keep track of previous node, in case current is null.

    int cmp; // Comparator for comparing keys.
    while (currNode != null && (cmp = newNode.key.compareTo(currNode.key)) != 0) {
      parentNode = currNode;
      if (cmp > 0) {
        currNode = currNode.right;
      } else {
        currNode = currNode.left;
      }
    }

    // If a node already exists with the same key.
    if (currNode != null) {
      currNode.value = newNode.value;
      return currNode;
    }

    // Else if currNode is now null.
    cmp = newNode.key.compareTo(parentNode.key);

    if (cmp > 0) parentNode.right = newNode;
    else parentNode.left = newNode;

    newNode.parent = parentNode;

    // Fix sizes.
    while (parentNode != null) {
      parentNode.size++;
      parentNode = parentNode.parent;
    }

    return newNode;
  }

  private void fixAfterInsertion(Node newNode) {

    Node currNode = newNode;
    Node parentNode = currNode.parent;

    // Continue till there are any adjacent reds.
    while (this.getColor(currNode) == RED && this.getColor(parentNode) == RED) {

      Node grandParentNode = parentNode.parent;

      // If parent is the left child of the grandparent.
      if (parentNode == grandParentNode.left) {
        Node uncleNode = grandParentNode.right;

        if (this.getColor(uncleNode) == RED) {
          parentNode.color = uncleNode.color = BLACK;
          grandParentNode.color = RED;
          currNode = grandParentNode;
          parentNode = currNode.parent;
        } else {
          // If current node is right child of its parent, then it's the Left-Right case and a prior
          // left rotation is required. Else, only a right rotation is required.
          if (currNode == parentNode.right) {
            this.rotateLeft(parentNode);

            // Make current node to be the lowest node in the tree.
            currNode = parentNode;
            parentNode = currNode.parent;
          }

          // Change the colors of the parent and grandparent nodes, and do a right rotation on the
          // grandparent.
          parentNode.color = BLACK;
          grandParentNode.color = RED;
          this.rotateRight(grandParentNode);
        }
      } else {
        Node uncleNode = grandParentNode.left;

        if (this.getColor(uncleNode) == RED) {
          parentNode.color = uncleNode.color = BLACK;
          grandParentNode.color = RED;
          currNode = grandParentNode;
          parentNode = currNode.parent;
        } else {
          // If current node is left child of its parent, then it's the Right-Left case and a prior
          // right rotation is required. Else, only a left rotation is required.
          if (currNode == parentNode.left) {
            this.rotateRight(parentNode);

            // Make current node to be the lowest node in the tree.
            currNode = parentNode;
            parentNode = currNode.parent;
          }

          // Change the colors of the parent and grandparent nodes, and do a left rotation on the
          // grandparent.
          parentNode.color = BLACK;
          grandParentNode.color = RED;
          this.rotateLeft(grandParentNode);
        }
      }
    }

    this.root.color = BLACK;
  }

  private void rotateLeft(Node node) {
    // Get the right child of the given node.
    Node rightChild = node.right;

    node.right = rightChild.left;
    if (rightChild.left != null) rightChild.left.parent = node;

    // Make node's parent to be its right child's parent.
    rightChild.parent = node.parent;

    if (node.parent == null) this.root = rightChild;
    else {

      // If node is its parent's left child.
      if (node == node.parent.left) node.parent.left = rightChild;

      // If node is its parent's right child.
      else node.parent.right = rightChild;
    }

    // Make node as the left child of its (previously) right child.
    rightChild.left = node;
    node.parent = rightChild;

    // Update the sizes.
    node.size = this.size(node.left) + this.size(node.right) + 1;
    rightChild.size = this.size(rightChild.left) + this.size(rightChild.right) + 1;
  }

  private void rotateRight(Node node) {
    // Get the left child of the given node.
    Node leftChild = node.left;

    node.left = leftChild.right;
    if (leftChild.right != null) leftChild.right.parent = node;

    // Make node's parent to be its left child's parent.
    leftChild.parent = node.parent;

    if (node.parent == null) this.root = leftChild;
    else {

      // If node is its parent's left child.
      if (node == node.parent.left) node.parent.left = leftChild;

      // If node is its parent's right child.
      else node.parent.right = leftChild;
    }

    // Make node as the right child of its (previously) left child.
    leftChild.right = node;
    node.parent = leftChild;

    // Update the sizes.
    node.size = this.size(node.left) + this.size(node.right) + 1;
    leftChild.size = this.size(leftChild.left) + this.size(leftChild.right) + 1;
  }

  public Value get(Key key) throws IllegalArgumentException {
    if (key == null) throw new IllegalArgumentException("Cannot get value of a null key");

    Node node = this.get(this.root, key);
    return node == null ? null : node.value;
  }

  public boolean contains(Key key) throws IllegalArgumentException {
    return this.get(key) != null;
  }

  public int size() {
    return this.size(this.root);
  }

  public int height() {
    return this.height(this.root);
  }

  public boolean isEmpty() {
    return this.root == null;
  }

  public Key min() throws NoSuchElementException {
    if (this.isEmpty()) throw new NoSuchElementException("Tree is empty while trying to find min");

    return this.min(this.root).key;
  }

  public Key max() throws NoSuchElementException {
    if (this.isEmpty()) throw new NoSuchElementException("Tree is empty while trying to find max");

    return this.max(this.root).key;
  }

  public Iterable<Key> keys() {
    return this.keysInOrder();
  }

  public Iterable<Key> keysInOrder() {
    LinkedList<Key> list = new LinkedList<>();
    this.keysInOrder(this.root, list);
    return list;
  }

  public Iterable<Key> keysLevelOrder() {
    LinkedList<Key> list = new LinkedList<>();
    if (this.isEmpty()) return list;

    Queue<Node> queue = new LinkedList<>();

    queue.add(this.root);
    while (!queue.isEmpty()) {
      Node currNode = queue.remove();
      list.add(currNode.key);

      if (currNode.left != null) queue.add(currNode.left);
      if (currNode.right != null) queue.add(currNode.right);
    }

    return list;
  }

  private Node get(Node node, Key key) {
    if (node == null) return null;

    int cmp = key.compareTo(node.key);

    if (cmp == 0) return node;

    return cmp > 0 ? this.get(node.right, key) : this.get(node.left, key);
  }

  private int size(Node node) {
    return node == null ? 0 : node.size;
  }

  private int height(Node node) {
    return node == null ? 0 : 1 + Math.max(this.height(node.left), this.height(node.right));
  }

  private Node min(Node node) {
    if (node.left == null) return node;
    return this.min(node.left);
  }

  private Node max(Node node) {
    if (node.right == null) return node;
    return this.max(node.right);
  }

  private void keysInOrder(Node node, LinkedList<Key> list) {
    if (node == null) return;
    this.keysInOrder(node.left, list);
    list.add(node.key);
    this.keysInOrder(node.right, list);
  }

  private boolean getColor(Node node) {
    return node == null ? BLACK : node.color;
  }

  private boolean check() {
    boolean isBST = this.isBST();
    boolean isRBTreeBlackHeightValid = this.isRBTreeBlackHeightValid();

    if (!isBST) System.err.println("BST check failed");
    if (!isRBTreeBlackHeightValid) System.err.println("RBTree black height check failed");

    return isBST && isRBTreeBlackHeightValid;
  }

  private boolean isBST() {
    return this.isBST(this.root, null, null);
  }

  private boolean isBST(Node node, Key minKey, Key maxKey) {
    if (node == null) return true;

    if (minKey != null && minKey.compareTo(node.key) >= 0) return false;
    if (maxKey != null && maxKey.compareTo(node.key) <= 0) return false;

    return this.isBST(node.left, minKey, node.key) && this.isBST(node.right, node.key, maxKey);
  }

  private boolean isRBTreeBlackHeightValid() {
    return this.computeBlackHeight(this.root) != -1;
  }

  private int computeBlackHeight(Node node) {
    if (node == null) return 0;

    int leftBlackHeight = this.computeBlackHeight(node.left);
    int rightBlackHeight = this.computeBlackHeight(node.right);

    if (leftBlackHeight == -1 || rightBlackHeight == -1 || leftBlackHeight != rightBlackHeight)
      return -1;
    else return (this.getColor(node) == BLACK ? 1 : 0) + leftBlackHeight;
  }

  private class Node {
    private Key key;
    private Value value;
    private boolean color;
    private int size;
    private Node left;
    private Node right;
    private Node parent;

    Node(Key key, Value value) {
      this.key = key;
      this.value = value;
      this.color = RED;
      this.size = 1;
      this.left = null;
      this.right = null;
      this.parent = null;
    }
  }
}
