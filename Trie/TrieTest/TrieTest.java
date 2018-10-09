public class TrieTest {
  public static void main(String[] args) {
    Trie trie = new Trie();

    trie.push("the");
    trie.push("a");
    trie.push("there");
    trie.push("answer");
    trie.push("any");
    trie.push("by");
    trie.push("bye");
    trie.push("their");

    assert trie.contains("the") == true;
    assert trie.contains("a") == true;
    assert trie.contains("there") == true;
    assert trie.contains("answer") == true;
    assert trie.contains("any") == true;
    assert trie.contains("by") == true;
    assert trie.contains("bye") == true;
    assert trie.contains("their") == true;
    System.out.println("Insertion and searching tests passed!");

    trie.delete("by");
    assert trie.contains("by") == false;

    trie.delete("answer");
    assert trie.contains("answer") == false;
    System.out.println("Deletion tests passed!");

    assert trie.contains("their") == true;
    trie.clear();
    assert trie.contains("their") == false;
    System.out.println("Tree cleared successfully!\n");

    System.out.println("All tests passed!");
  }
}
