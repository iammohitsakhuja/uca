package com.uca.util;

public class TestLinkedList {
  public static void main(String[] args) {
    LinkedList<Integer> list = new LinkedList<>();
    assert list.size() == 0;
    assert list.isEmpty();

    list.add(1);
    list.add(2);
    list.add(3);

    assert list.size() == 3;
    assert !list.isEmpty();

    System.out.println("All tests passed!");
  }
}
