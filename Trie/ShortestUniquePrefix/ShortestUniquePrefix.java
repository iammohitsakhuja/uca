import java.util.ArrayList;

class ShortestUniquePrefix {
  public static ArrayList<String> solve(ArrayList<String> input) {
    Trie trie = new Trie();
    for (String str : input) trie.push(str);

    ArrayList<String> results = new ArrayList<>();
    for (String str : input) results.add(trie.prefix(str));

    return results;
  }

  public static void main(String[] args) {
    ArrayList<String> input = new ArrayList<>(4);
    input.add("zebra");
    input.add("dog");
    input.add("duck");
    input.add("dove");

    ArrayList<String> results = solve(input);
    System.out.println(results);
  }
}
