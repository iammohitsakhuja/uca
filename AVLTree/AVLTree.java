/**
 * Represents the AVL Tree data structure.
 *
 * @author Mohit Sakhuja
 */
import java.util.LinkedList;
import java.util.NoSuchElementException;
import java.util.Queue;

public class AVLTree<Key extends Comparable<Key>, Value> {
  private Node root; /* Root node of the tree. */

  /** Represents an inner node of the tree. */
  private class Node {
    private Key key;
    private Value value;
    private Node left;
    private Node right;
    private int height; /* Height of each node >= 1. */
    private int size; /* Size of each node >= 1. */

    public Node(Key key, Value value) {
      this.key = key;
      this.value = value;
      this.left = null;
      this.right = null;
      this.height = 1;
      this.size = 1;
    }
  }

  /** Initializes an empty AVL tree. */
  public AVLTree() {
    this.root = null;
  }

  /** Returns the size of the tree. */
  public int size() {
    return this.size(this.root);
  }

  /** Returns the height of the tree. */
  public int height() {
    return this.height(this.root);
  }

  /** Returns true if the tree is empty, false otherwise. */
  public boolean isEmpty() {
    return this.root == null;
  }

  /** Returns the value associated with the given key. */
  public Value get(Key key) throws IllegalArgumentException {
    if (key == null) throw new IllegalArgumentException("Cannot get value of a null key");

    Node x = this.get(this.root, key);
    if (x == null) return null;

    return x.value;
  }

  /** Checks if the table contains the given key. */
  public boolean contains(Key key) throws IllegalArgumentException {
    return this.get(key) != null;
  }

  /**
   * Puts a key-value pair into the tree if the key is not already present in the tree. Else,
   * updates the value for the given key.
   */
  public void put(Key key, Value value) throws IllegalArgumentException {
    if (key == null) throw new IllegalArgumentException("key is null");
    if (value == null) {
      this.delete(key);
      return;
    }
    this.root = put(this.root, key, value);

    assert this.check();
  }

  /** Deletes the node with the given key from the tree. */
  public void delete(Key key) {
    if (key == null) throw new IllegalArgumentException("key is null while deleting");
    if (!this.contains(key)) return;
    this.root = this.delete(this.root, key);

    assert this.check();
  }

  /** Deletes the left most node from the tree. */
  public void deleteMin() throws NoSuchElementException {
    if (this.isEmpty())
      throw new NoSuchElementException("Tree is empty while trying to delete min");
    this.root = this.deleteMin(this.root);

    assert this.check();
  }

  /** Deletes the right most node from the tree. */
  public void deleteMax() throws NoSuchElementException {
    if (this.isEmpty())
      throw new NoSuchElementException("Tree is empty while trying to delete max");
    this.root = this.deleteMax(this.root);

    assert this.check();
  }

  /** Gets the minimum key in the tree. */
  public Key min() throws NoSuchElementException {
    if (this.isEmpty()) throw new NoSuchElementException("Tree is empty while trying to find min");
    return this.min(this.root).key;
  }

  /** Gets the maximum key in the tree. */
  public Key max() throws NoSuchElementException {
    if (this.isEmpty()) throw new NoSuchElementException("Tree is empty while trying to find max");
    return this.max(this.root).key;
  }

  /** Returns the largest key in the tree, less than or equal to the given key. */
  public Key floor(Key key) throws IllegalArgumentException, NoSuchElementException {
    if (key == null) throw new IllegalArgumentException("key is null in floor()");
    if (this.isEmpty()) throw new NoSuchElementException("tree is empty in floor()");

    Node x = this.floor(this.root, key);
    if (x == null) return null;

    return x.key;
  }

  /** Returns the smallest key in the tree, greater than or equal to the given key. */
  public Key ceiling(Key key) throws IllegalArgumentException, NoSuchElementException {
    if (key == null) throw new IllegalArgumentException("key is null in ceiling()");
    if (this.isEmpty()) throw new NoSuchElementException("tree is empty in ceiling()");

    Node x = this.ceiling(this.root, key);
    if (x == null) return null;

    return x.key;
  }

  /** Returns the kth smallest key in the tree, k lies between [1, size]. */
  public Key select(int k) throws IllegalArgumentException {
    if (k < 1 || k > this.size()) throw new IllegalArgumentException("Invalid k in select()");
    return this.select(this.root, k).key;
  }

  /** Returns the number of keys in the tree less than or equal to the given key. */
  public int rank(Key key) throws IllegalArgumentException {
    if (key == null) throw new IllegalArgumentException("key is null in rank()");
    return this.rank(this.root, key);
  }

  /** Returns all keys in the tree. */
  public Iterable<Key> keys() {
    return this.keysInOrder();
  }

  /** Returns a list of keys of nodes traversed in an in-order fashion. */
  public Iterable<Key> keysInOrder() {
    LinkedList<Key> list = new LinkedList<>();
    this.keysInOrder(this.root, list);
    return list;
  }

  /** Returns a list of keys of nodes traversed in a level-order fashion. */
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

  /** Helper function that returns the size of the given subtree. */
  private int size(Node node) {
    if (node == null) return 0;
    return node.size;
  }

  /** Helper function that returns the height of the given subtree. */
  private int height(Node node) {
    if (node == null) return 0;
    return node.height;
  }

  /** Helper function that puts a key-value pair into the subtree starting from x. */
  private Node put(Node x, Key key, Value value) {
    if (x == null) return new Node(key, value);

    int cmp = key.compareTo(x.key);
    if (cmp < 0) x.left = put(x.left, key, value);
    else if (cmp > 0) x.right = put(x.right, key, value);
    else {
      x.value = value;
      return x;
    }

    // Update the augmented data.
    x.height = Math.max(height(x.left), height(x.right)) + 1;
    x.size = size(x.left) + size(x.right) + 1;

    return this.balance(x);
  }

  /** Balances the subtree starting from x. */
  private Node balance(Node x) {
    // If subtree at x is right-leaning.
    if (this.balanceFactor(x) < -1) {
      // If subtree at x.right is left-leaning.
      if (this.balanceFactor(x.right) > 0) x.right = rotateRight(x.right);
      x = rotateLeft(x);
    }
    // If subtree at x is left-leaning.
    else if (this.balanceFactor(x) > 1) {
      // If subtree at x.left is right leaning.
      if (this.balanceFactor(x.left) < 0) x.left = rotateLeft(x.left);
      x = rotateRight(x);
    }

    return x;
  }

  /**
   * Helper function that returns the difference in heights of the left subtree and the right
   * subtree.
   */
  private int balanceFactor(Node x) {
    return height(x.left) - height(x.right);
  }

  /** Right rotates the subtree starting from x. */
  private Node rotateRight(Node x) {
    Node leftChild = x.left;

    // Rotate.
    x.left = leftChild.right;
    leftChild.right = x;

    // Update heights.
    x.height = Math.max(height(x.left), height(x.right)) + 1;
    leftChild.height = Math.max(height(leftChild.left), height(leftChild.right)) + 1;

    // Update sizes.
    leftChild.size = size(x);
    x.size = size(x.left) + size(x.right) + 1;

    return leftChild;
  }

  /** Left rotates the subtree starting from x. */
  private Node rotateLeft(Node x) {
    Node rightChild = x.right;

    // Rotate.
    x.right = rightChild.left;
    rightChild.left = x;

    // Update heights.
    x.height = Math.max(height(x.left), height(x.right)) + 1;
    rightChild.height = Math.max(height(rightChild.left), height(rightChild.right)) + 1;

    // Update sizes.
    rightChild.size = size(x);
    x.size = size(x.left) + size(x.right) + 1;

    return rightChild;
  }

  /** Helper function that returns the node associated with the given key in the given subtree. */
  private Node get(Node x, Key key) {
    while (x != null && key.compareTo(x.key) != 0) {
      if (key.compareTo(x.key) < 0) x = x.left;
      else x = x.right;
    }

    return x;
  }

  /** Helper function that deletes the left most node from the given subtree. */
  private Node deleteMin(Node x) {
    if (x.left == null) return x.right;
    x.left = this.deleteMin(x.left);

    x.height = Math.max(height(x.left), height(x.right)) + 1;
    x.size = size(x.left) + size(x.right) + 1;

    return this.balance(x);
  }

  /** Helper function that deletes the right most node from the given subtree. */
  private Node deleteMax(Node x) {
    if (x.right == null) return x.left;
    x.right = this.deleteMax(x.right);

    x.height = Math.max(height(x.left), height(x.right)) + 1;
    x.size = size(x.left) + size(x.right) + 1;

    return this.balance(x);
  }

  /** Helper function that returns the node with the minimum key in the subtree starting from x. */
  private Node min(Node x) {
    if (x.left == null) return x;
    return this.min(x.left);
  }

  /** Helper function that returns the node with the maximum key in the subtree starting from x. */
  private Node max(Node x) {
    if (x.right == null) return x;
    return this.max(x.right);
  }

  /** Helper function to delete a key from the given subtree starting at x. */
  private Node delete(Node x, Key key) {
    int cmp = key.compareTo(x.key);

    if (cmp < 0) x.left = this.delete(x.left, key);
    else if (cmp > 0) x.right = this.delete(x.right, key);
    else {
      if (x.left == null) return x.right;
      else if (x.right == null) return x.left;
      else {
        Node nodeToBeDeleted = x;
        x = this.max(nodeToBeDeleted.left);
        x.left = this.deleteMax(nodeToBeDeleted.left);
        x.right = nodeToBeDeleted.right;
      }
    }

    x.size = this.size(x.left) + this.size(x.right) + 1;
    x.height = Math.max(this.height(x.left), this.height(x.right)) + 1;

    return this.balance(x);
  }

  /**
   * Helper function that returns the node with the largest key in the given subtree, less than or
   * equal to the given key.
   */
  private Node floor(Node x, Key key) {
    if (x == null) return null;

    int cmp = key.compareTo(x.key);
    if (cmp == 0) return x;
    if (cmp < 0) return this.floor(x.left, key);

    Node floor = this.floor(x.right, key);
    if (floor != null) return floor;
    return x;
  }

  /**
   * Helper function that returns the node with the smallest key in the given subtree, greater than
   * or equal to the given key.
   */
  private Node ceiling(Node x, Key key) {
    if (x == null) return null;

    int cmp = key.compareTo(x.key);
    if (cmp == 0) return x;
    if (cmp > 0) return this.ceiling(x.right, key);

    Node ceiling = this.ceiling(x.left, key);
    if (ceiling != null) return ceiling;

    return x;
  }

  /**
   * Helper function that returns the node with the kth smallest key in the subtree, k lies between
   * [1, size of subtree].
   */
  private Node select(Node x, int k) {
    if (x == null) return null;

    int currK = this.size(x.left) + 1;
    if (currK == k) return x;
    if (currK > k) return this.select(x.left, k);

    return this.select(x.right, k - currK);
  }

  /**
   * Helper function that returns the number of keys in the subtree less than or equal to the given
   * key.
   */
  private int rank(Node x, Key key) {
    if (x == null) return 0;

    int cmp = key.compareTo(x.key);
    if (cmp == 0) return this.size(x.left) + 1;
    if (cmp < 0) return this.rank(x.left, key);

    return this.size(x.left) + 1 + this.rank(x.right, key);
  }

  /** Helper function that puts the keys of the subtree into the list, in in-order fashion. */
  private void keysInOrder(Node x, LinkedList<Key> list) {
    if (x == null) return;
    this.keysInOrder(x.left, list);
    list.add(x.key);
    this.keysInOrder(x.right, list);
  }

  /**
   * Check whether the the given tree does not break any rules of the AVL property, and the BST
   * property.
   */
  private boolean check() {
    boolean isAVL = this.isAVL();
    boolean isBST = this.isBST();
    boolean isSizeConsistent = this.isSizeConsistent();
    boolean isRankConsistent = this.isRankConsistent();

    if (!isAVL) System.out.println("AVL check failed");
    if (!isBST) System.out.println("BST check failed");
    if (!isSizeConsistent) System.out.println("Size consistency check failed");
    if (!isRankConsistent) System.out.println("Rank consistency check failed");

    if (!isAVL || !isBST || !isSizeConsistent || !isRankConsistent) return false;

    return true;
  }

  /** Checks if the AVL property holds for the tree. */
  private boolean isAVL() {
    return this.isAVL(this.root);
  }

  /** Helper function that checks if the AVL property holds for the given subtree. */
  private boolean isAVL(Node x) {
    if (x == null) return true;
    int balanceFactor = this.balanceFactor(x);
    if (balanceFactor < -1 || balanceFactor > 1) return false;
    return this.isAVL(x.left) && this.isAVL(x.right);
  }

  /** Checks if the BST property holds for the tree. */
  private boolean isBST() {
    return this.isBST(this.root, null, null);
  }

  /** Helper function that checks if the BST property holds for the given subtree. */
  private boolean isBST(Node x, Key minKey, Key maxKey) {
    if (x == null) return true;

    // Equality ensures that no two nodes exist with the same key.
    if (minKey != null && minKey.compareTo(x.key) >= 0) return false;
    if (maxKey != null && maxKey.compareTo(x.key) <= 0) return false;

    return this.isBST(x.left, minKey, x.key) && this.isBST(x.right, x.key, maxKey);
  }

  /** Checks that the sizes are consistent for each of the nodes in the tree. */
  private boolean isSizeConsistent() {
    return this.isSizeConsistent(this.root);
  }

  /**
   * Helper function that checks whether the sizes are consistent for each of the nodes in the
   * subtree.
   */
  private boolean isSizeConsistent(Node x) {
    if (x == null) return true;
    if (x.size != this.size(x.left) + this.size(x.right) + 1) return false;
    return this.isSizeConsistent(x.left) && this.isSizeConsistent(x.right);
  }

  /** Checks that the ranks are consistent for each of the nodes in the tree. */
  private boolean isRankConsistent() {
    for (int i = 1; i <= this.size(); i++) if (i != this.rank(this.select(i))) return false;
    for (Key key : this.keys()) if (key.compareTo(this.select(this.rank(key))) != 0) return false;
    return true;
  }
}
