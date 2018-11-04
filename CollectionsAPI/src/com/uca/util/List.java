package com.uca.util;

public interface List<Item extends Comparable<Item>> extends Collections<Item> {
  @Override
  void add(Item item);

  @Override
  void remove(Item item);

  @Override
  int size();

  @Override
  boolean isEmpty();

  @Override
  void clear();
}
