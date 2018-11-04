package com.uca.ds.trees;

import com.uca.util.Iterator;
import com.uca.util.Iterable;

public class LeftLeaningRedBlackTree<Key extends Comparable<Key>, Value> implements Iterable<Key> {

  private class Node {
    private Key key;
    private Value value;
    private boolean color;
    private int size;
    private Node left;
    private Node right;

    Node(Key key, Value value) {
      this.key = key;
      this.value = value;
      this.color = RED;
      this.size = 1;
      this.left = null;
      this.right = null;
    }
  }

  private static final boolean RED = false;
  private static final boolean BLACK = true;

  private Node root;

  public LeftLeaningRedBlackTree() {
    this.root = null;
  }

  public void add(Key key, Value value) {
    this.root = this.add(this.root, key, value);
    this.root.color = BLACK;
    assert this.check();
  }

  public Value get(Key key) {
    Node node = this.get(this.root, key);
    return node == null ? null : node.value;
  }

  public int height() {
    return this.height(this.root);
  }

  public int size() {
    return this.size(this.root);
  }

  public boolean isLeftLeaningRedBlack() {
    return this.isLeftLeaningRedBlack(this.root)
        && (this.root == null || this.getColor(this.root) == BLACK);
  }

  @Override
  public Iterator<Key> iterator() {
    return null;
  }

  private Node add(Node node, Key key, Value value) {
    if (node == null) return new Node(key, value);

    int cmp = key.compareTo(node.key);

    if (cmp == 0) node.value = value;
    else if (cmp > 0) node.right = this.add(node.right, key, value);
    else node.left = this.add(node.left, key, value);

    // Rotate and/or swap colors according to conditions of a left-leaning RBT.
    if (this.getColor(node.left) == BLACK && this.getColor(node.right) == RED)
      node = this.leftRotate(node);

    if (this.getColor(node.left) == RED && this.getColor(node.left.left) == RED)
      node = this.rightRotate(node);

    if (this.getColor(node.left) == RED && this.getColor(node.right) == RED)
      node = this.swapColor(node);

    // Update the size.
    node.size = 1 + this.size(node.left) + this.size(node.right);

    return node;
  }

  private Node get(Node node, Key key) {
    if (node == null) return null;

    int cmp = key.compareTo(node.key);

    if (cmp == 0) return node;

    return cmp > 0 ? this.get(node.right, key) : this.get(node.left, key);
  }

  private int height(Node node) {
    return node == null ? 0 : 1 + Math.max(this.height(node.left), this.height(node.right));
  }

  private boolean getColor(Node node) {
    return node == null ? BLACK : node.color;
  }

  private int size(Node node) {
    return node == null ? 0 : node.size;
  }

  private Node leftRotate(Node node) {
    Node rightChild = node.right;
    node.right = rightChild.left;
    rightChild.left = node;

    rightChild.color = node.color;
    node.color = RED;

    return rightChild;
  }

  private Node rightRotate(Node node) {
    Node leftChild = node.left;
    node.left = leftChild.right;
    leftChild.right = node;

    leftChild.color = node.color;
    node.color = RED;

    return leftChild;
  }

  private Node swapColor(Node node) {
    node.left.color = node.right.color = node.color;
    node.color = RED;
    return node;
  }

  private boolean check() {
    return this.isLeftLeaningRedBlack();
  }

  private boolean isLeftLeaningRedBlack(Node node) {
    if (node == null) return true;

    if (this.getColor(node.left) == BLACK && this.getColor(node.right) == RED)
      return false;

    if (this.getColor(node.left) == RED && this.getColor(node.left.left) == RED)
      return false;

    if (this.getColor(node.left) == RED && this.getColor(node.right) == RED)
      return false;

    return this.isLeftLeaningRedBlack(node.left) && this.isLeftLeaningRedBlack(node.right);
  }
}
