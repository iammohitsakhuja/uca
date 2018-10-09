import java.util.Iterator;
import java.util.NoSuchElementException;

public class Stack<Item> implements Iterable<Item> {
  private Node<Item> top; // Top of stack.
  private int size; // Size of the stack.

  // Helper Linked List.
  private static class Node<Item> {
    private Item item;
    private Node<Item> next;

    Node(Item item) {
      this.item = item;
      this.next = null;
    }

    @Override
    public String toString() {
      return this.item.toString();
    }
  }

  /** Initializes an empty stack. */
  public Stack() {
    this.top = null;
    this.size = 0;
  }

  /**
   * Returns true if this stack is empty.
   *
   * @return true if this stack is empty; false otherwise.
   */
  public boolean isEmpty() {
    return this.top == null;
  }

  /** Returns the number of items in this stack. */
  public int size() {
    return this.size;
  }

  /**
   * Adds the item to this stack.
   *
   * @param item - item to be added to the list.
   */
  public void push(Item item) {
    Node<Item> newNode = new Node<>(item);
    newNode.next = this.top;
    this.top = newNode;

    this.size++;
  }

  /** Removes an element from the top of the stack. */
  public void pop() {
    if (this.isEmpty()) throw new NoSuchElementException("Stack underflow");

    Node<Item> topNode = this.top;
    this.top = this.top.next;

    topNode.next = null;
    this.size--;
  }

  /**
   * Returns the item in the top most element.
   *
   * @return item - item in the topmost element.
   */
  public Item top() {
    if (this.isEmpty()) throw new NoSuchElementException("Stack underflow");
    return this.top.item;
  }

  /**
   * Returns an iterator to the stack. Enables fancy features like For-Each loop.
   *
   * @return iterator - an iterator to the stack.
   */
  public Iterator<Item> iterator() {
    Iterator<Item> itr =
        new Iterator<Item>() {
          Node<Item> currNode = top;

          @Override
          public boolean hasNext() {
            return currNode != null;
          }

          @Override
          public Item next() {
            Node<Item> prevNode = currNode;
            currNode = currNode.next;
            return prevNode.item;
          }

          @Override
          public void remove() {
            throw new UnsupportedOperationException();
          }
        };

    return itr;
  }

  /**
   * Unit tests the {@code Stack} data type.
   *
   * @param args the command-line arguments.
   */
  public static void main(String[] args) {
    Stack<Integer> s = new Stack<Integer>();
    s.push(5);
    s.push(7);
    s.push(3);

    assert s.size() == 3;
    assert s.top() == 3;
    s.pop();
    assert s.top() == 7;
    s.pop();
    assert s.top() == 5;
    s.pop();
    assert s.size() == 0;
    System.out.println("All tests passed!");

    for (Integer a : s) System.out.println(a);
  }
}
