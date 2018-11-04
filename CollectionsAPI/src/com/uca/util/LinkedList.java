package com.uca.util;

import java.util.NoSuchElementException;

public class LinkedList<Item extends Comparable<Item>> implements List<Item> {
  private class Node {
    private Item item;
    private Node next;

    Node(Item item) {
      this.item = item;
      this.next = null;
    }
  }

  private Node head;
  private int size;

  public LinkedList() {
    this.head = null;
    this.size = 0;
  }

  @Override
  public void add(Item item) {
    this.head = this.add(item, this.head);
    this.size++;
  }

  @Override
  public void remove(Item item) {
    this.head = this.remove(item, this.head);
    this.size--;
  }

  @Override
  public int size() {
    return this.size;
  }

  @Override
  public boolean isEmpty() {
    return this.size == 0;
  }

  @Override
  public void clear() {
    this.head = null;
    this.size = 0;
  }

  @Override
  public Iterator<Item> iterator() {
    return new Iterator<Item>() {
      private Node itr = head;

      public boolean hasNext() {
        return this.itr != null;
      }

      public Item next() {
        if (!hasNext()) throw new NoSuchElementException();

        Item item = this.itr.item;
        this.itr = this.itr.next;
        return item;
      }
    };
  }

  private Node add(Item item, Node node) {
    if (node == null) return new Node(item);

    node.next = this.add(item, node.next);
    return node;
  }

  private Node remove(Item item, Node node) {
    // If element not found.
    if (node == null) return null;

    if (item.equals(node.item)) return node.next;

    node.next = this.remove(item, node.next);
    return node;
  }
}
