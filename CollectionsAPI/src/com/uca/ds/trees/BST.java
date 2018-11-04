package com.uca.ds.trees;

import com.uca.util.Iterator;
import com.uca.util.Iterable;

public class BST<Key extends Comparable<Key>, Value> implements Iterable<Key> {

  private class Node {
    private Key key;
    private Value value;
    private Node left;
    private Node right;
    private int size; // Represents the size of the subtree from the node.

    Node(Key key, Value value) {
      this.key = key;
      this.value = value;
      this.left = null;
      this.right = null;
      this.size = 1;
    }
  }

  private Node root;

  public BST() {
    this.root = null;
  }

  public void add(Key key, Value value) {
    this.root = this.add(this.root, key, value);
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

  public int rank(Key key) {
    return this.rank(this.root, key);
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

    node.size = this.size(node.left) + this.size(node.right) + 1;

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

  private int size(Node node) {
    return node == null ? 0 : node.size;
  }

  private int rank(Node node, Key key) {
    if (node == null) return 0;

    int cmp = key.compareTo(node.key);

    if (cmp == 0) return 1 + this.size(node.left);

    if (cmp < 0) return this.rank(node.left, key);
    else return 1 + this.size(node.left) + this.rank(node.right, key);
  }
}
