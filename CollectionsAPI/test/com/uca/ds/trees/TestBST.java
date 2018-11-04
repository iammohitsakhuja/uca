package com.uca.ds.trees;

public class TestBST {
  public static void main(String[] args) {
    BST<Integer, String> bst = new BST<>();

    for (int i = 1; i <= 100; i++) bst.add(i, "Some value");

    for (int i = 1; i <= 100; i++)
      assert bst.get(i).equals("Some value");

    assert bst.get(0) == null;
    assert bst.get(101) == null;

    assert bst.height() == 100;

    for (int i = 1; i <= 100; i++)
      assert bst.rank(i) == i;

    System.out.println("All tests passed!");
  }
}
