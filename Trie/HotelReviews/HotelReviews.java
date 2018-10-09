import java.util.ArrayList;
import java.util.Collections;

class HotelReviews {
  private static class ReviewString implements Comparable<ReviewString> {
    int index;
    int count;

    ReviewString(int index, int count) {
      this.index = index;
      this.count = count;
    }

    public int compareTo(ReviewString x) {
      return x.count - this.count;
    }
  }

  public static ArrayList<Integer> solve(String A, ArrayList<String> B) {
    Trie trie = new Trie();

    // Add good words to trie.
    String[] goodWords = A.split("_");
    for (String word : goodWords) trie.push(word);

    // Create an array to hold the index as well as count of a string.
    ArrayList<ReviewString> array = new ArrayList<>();

    for (int i = 0; i < B.size(); i++) {
      String[] words = B.get(i).split("_");
      int count = 0;
      for (String word : words) if (trie.contains(word)) count++;

      array.add(new ReviewString(i, count));
    }

    Collections.sort(array);

    ArrayList<Integer> results = new ArrayList<>();
    for (int i = 0; i < array.size(); i++) results.add(array.get(i).index);

    return results;
  }

  public static void main(String[] args) {
    String goodWords = "cool_ice_wifi";
    ArrayList<String> reviews = new ArrayList<>(3);
    reviews.add("water_is_cool");
    reviews.add("cold_ice_drink");
    reviews.add("cool_wifi_speed");

    ArrayList<Integer> results = solve(goodWords, reviews);
    System.out.println(results.toString());
  }
}
