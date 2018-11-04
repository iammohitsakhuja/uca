package com.uca.ds.trees;

public class TestRedBlackTree {
  private final static int MAX_SIZE = 100;

  private static void checkAscending() {
    System.out.println("Ascending: ");
    RedBlackTree<Integer, String> redBlackTree = new RedBlackTree<>();

    for (int i = 1; i <= MAX_SIZE; i++) redBlackTree.add(i, "Some value: " + i);

    System.out.println("Size: " + redBlackTree.size());
    System.out.println("Height: " + redBlackTree.height());

    System.out.println();
  }

  private static void checkDescending() {
    System.out.println("Descending: ");
    RedBlackTree<Integer, String> redBlackTree = new RedBlackTree<>();

    for (int i = MAX_SIZE; i >= 1; i--) redBlackTree.add(i, "Some value: " + i);

    System.out.println("Size: " + redBlackTree.size());
    System.out.println("Height: " + redBlackTree.height());

    System.out.println();
  }

  public static void main(String[] args) {
    checkAscending();
    checkDescending();
  }
}
