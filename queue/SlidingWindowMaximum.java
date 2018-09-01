import java.util.Deque;
import java.util.LinkedList;

class SlidingWindowMaximum {
  static void addToQueue(Deque<Integer> q, int[] array, int i) {
    // Remove any elements smaller than array[i] from the end of the queue.
    while (!q.isEmpty() && array[i] >= array[q.peekLast()]) {
      q.removeLast();
    }

    // Add the index of the current element to the end of the queue.
    q.addLast(i);
  }

  static void findMaximum(int[] array, int windowLength) {
    // Create a doubly-ended queue to hold the indices.
    Deque<Integer> q = new LinkedList<>();

    // Add appropriate indices from the first window to the queue.
    for (int i = 0; i < windowLength; i++) {
      addToQueue(q, array, i);
    }

    // Maximum element amongst the first window.
    System.out.println(array[q.peek()]);

    for (int i = windowLength; i < array.length; i++) {
      // If window goes beyond the first index that is contained in the queue, remove that index.
      if (i - windowLength == q.peek()) q.pop();

      addToQueue(q, array, i);
      System.out.println(array[q.peek()]);
    }
  }

  public static void main(String[] args) {
    int[] array = new int[] {28, 52, 37, 43, 57, 34, 20, 99, 80, 87, 43, 16, 13, 37, 65};

    findMaximum(array, 4);
  }
}
