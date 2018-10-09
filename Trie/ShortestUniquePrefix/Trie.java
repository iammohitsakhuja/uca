public class Trie {
  static final int ALPHABET_SIZE = 26;
  TrieNode root;

  private class TrieNode {
    int frequency;
    TrieNode[] next;

    TrieNode() {
      this.frequency = 0;
      this.next = new TrieNode[ALPHABET_SIZE];
      for (int i = 0; i < ALPHABET_SIZE; i++) this.next[i] = null;
    }
  }

  public Trie() {
    this.root = new TrieNode();
  }

  public void push(String str) {
    TrieNode currNode = this.root;

    for (char character : str.toCharArray()) {
      int j = character - 'a';
      if (currNode.next[j] == null) currNode.next[j] = new TrieNode();

      currNode = currNode.next[j];
      currNode.frequency++;
    }
  }

  public String prefix(String str) {
    TrieNode currNode = this.root;

    StringBuilder result = new StringBuilder();
    for (char character : str.toCharArray()) {
      int j = character - 'a';
      if (currNode.next[j].frequency == 1) {
        result.append(character);
        return result.toString();
      }

      result.append(character);
      currNode = currNode.next[j];
    }

    return result.toString();
  }
}
