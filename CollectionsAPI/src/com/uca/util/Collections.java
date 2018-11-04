package com.uca.util;

public interface Collections<Item extends Comparable<Item>> extends Iterable<Item> {
  void add(Item item);

  void remove(Item item);

  int size();

  boolean isEmpty();

  void clear();
}
