class AVLTreeTest {
  public static void main(String[] args) {
    final int SIZE = 6;
    int[] keys = new int[] {10, 20, 30, 40, 50, 25};

    // Constructor.
    AVLTree<Integer, Integer> tree = new AVLTree<>();

    // Put.
    for (int i = 0; i < SIZE; i++) tree.put(keys[i], i);

    // Traversal.
    System.out.println(tree.keys());
    System.out.println(tree.keysLevelOrder());

    System.out.println("Floor of 15: " + tree.floor(15));
    System.out.println("Ceiling of 15: " + tree.ceiling(15));

    // Size, height, isEmpty.
    System.out.println("Size: " + tree.size());
    System.out.println("Height: " + tree.height());
    System.out.println("Is empty: " + tree.isEmpty());

    // Get.
    for (int key : keys) System.out.println("(" + key + ", " + tree.get(key) + ")");
    System.out.println("Value for key 60 (non-existing): " + tree.get(60));

    // Contains.
    for (int i = 0; i < SIZE; i++)
      System.out.println("Contains " + keys[i] + ": " + tree.contains(keys[i]));
    System.out.println("Contains 60 (non-existing): " + tree.contains(60));

    // Min and max.
    System.out.println("Min: " + tree.min());
    System.out.println("Max: " + tree.max());

    // Delete min and Delete max.
    System.out.println("\nDeleting min and max...");
    tree.deleteMin();
    tree.deleteMax();
    System.out.println("Min after deleting min: " + tree.min());
    System.out.println("Max after deleting max: " + tree.max());
    System.out.println("Size: " + tree.size());
    System.out.println("Height: " + tree.height());
    System.out.println("Is empty: " + tree.isEmpty());

    // Delete.
    System.out.println("Before deleting 30, tree contains 30: " + tree.contains(30));
    tree.delete(30);
    System.out.println("After deleting 30, tree contains 30: " + tree.contains(30));
    System.out.println("Size: " + tree.size());
    System.out.println("Height: " + tree.height());

    // Check if it deletes a node when value is null.
    System.out.println(tree.contains(40));
    tree.put(40, null);
    System.out.println(tree.contains(40));
  }
}
