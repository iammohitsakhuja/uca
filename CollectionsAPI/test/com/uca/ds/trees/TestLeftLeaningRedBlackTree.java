package com.uca.ds.trees;

public class TestLeftLeaningRedBlackTree {
  private static final int MAX_SIZE = 100;

  private static void checkAscending() {
    LeftLeaningRedBlackTree<Integer, String> leftLeaningRedBlackTree =
        new LeftLeaningRedBlackTree<>();

    for (int i = 1; i <= MAX_SIZE; i++) leftLeaningRedBlackTree.add(i, "Some value");

    assert leftLeaningRedBlackTree.isLeftLeaningRedBlack();

    for (int i = 1; i <= MAX_SIZE; i++) assert leftLeaningRedBlackTree.get(i).equals("Some value");
    assert leftLeaningRedBlackTree.get(0) == null;
    assert leftLeaningRedBlackTree.get(MAX_SIZE + 1) == null;

    System.out.println("Height (asc): " + leftLeaningRedBlackTree.height());
  }

  private static void checkDescending() {
    LeftLeaningRedBlackTree<Integer, String> leftLeaningRedBlackTree =
        new LeftLeaningRedBlackTree<>();

    for (int i = MAX_SIZE; i >= 1; i--) leftLeaningRedBlackTree.add(i, "Some value");

    assert leftLeaningRedBlackTree.isLeftLeaningRedBlack();

    for (int i = MAX_SIZE; i >= 1; i--) assert leftLeaningRedBlackTree.get(i).equals("Some value");
    assert leftLeaningRedBlackTree.get(0) == null;
    assert leftLeaningRedBlackTree.get(MAX_SIZE + 1) == null;

    System.out.println("Height (desc): " + leftLeaningRedBlackTree.height());
  }

  public static void main(String[] args) {
    checkAscending();
    checkDescending();
    System.out.println("All tests passed!");
  }
}
