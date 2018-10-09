public class Trie {
  // private static final int ALPHABET_SIZE = 26;
  // private static final int FIRST_ALPHABET = 'a';
  private static final int ALPHABET_SIZE = 128;
  private static final int FIRST_ALPHABET = 0;
  private TrieNode root;

  private static class TrieNode {
    private boolean isWord;
    private TrieNode[] next;

    private TrieNode() {
      this.isWord = false;
      this.next = new TrieNode[ALPHABET_SIZE];
    }
  }

  public Trie() {
    this.root = new TrieNode();
  }

  public void push(String word) {
    TrieNode currNode = this.root;

    for (char character : word.toCharArray()) {
      int j = character - FIRST_ALPHABET;
      if (currNode.next[j] == null) currNode.next[j] = new TrieNode();
      currNode = currNode.next[j];
    }

    currNode.isWord = true;
  }

  public boolean contains(String word) {
    TrieNode currNode = this.root;

    for (char character : word.toCharArray()) {
      int j = character - FIRST_ALPHABET;
      if (currNode.next[j] == null) return false;
      currNode = currNode.next[j];
    }

    return currNode.isWord;
  }

  public void delete(String word) {
    if (word == null || word.length() == 0) return;

    TrieNode currNode = this.root;
    TrieNode prevNode = null;
    int prevIndex = 0;

    for (char character : word.toCharArray()) {
      int j = character - FIRST_ALPHABET;

      // If given word not in trie.
      if (currNode.next[j] == null) return;

      prevIndex = j;
      prevNode = currNode;
      currNode = currNode.next[j];
    }

    currNode.isWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++) if (currNode.next[i] != null) return;

    prevNode.next[prevIndex] = null;
  }

  public void clear() {
    this.root = this.clear(this.root);
    this.root = new TrieNode();
  }

  private TrieNode clear(TrieNode currNode) {
    for (int i = 0; i < ALPHABET_SIZE; i++)
      if (currNode.next[i] != null) currNode.next[i] = this.clear(currNode.next[i]);

    return null;
  }
}
